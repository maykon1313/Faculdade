import os
import json
import random
import pickle
import numpy as np
import torch
import torch.nn as nn
from torch.utils.data import DataLoader, TensorDataset, Subset
from torch.optim import AdamW
import matplotlib.pyplot as plt
from transformers import BertModel, AutoTokenizer
from sklearn.model_selection import KFold

num_classes = 3  # 3 classes por categoria (positivo, neutro, negativo)
num_categories = 3  # 3 categorias (onça, caseiro, notícia)
DROP = 0.3
LR = 2e-5
WD = 0
BATCH = 128
EPOCHS = 10
PATIENCE = 5
SEED = 42
CLIP_NORM = 1.0

FREEZE_EPOCHS = 1      # número de épocas para treinar apenas a cabeça (BERT congelado)
HIDDEN_DIM = 256       # dimensão da camada oculta na cabeça de classificação
USE_HIDDEN = True      # usar camada oculta (Linear -> ReLU -> Dropout -> Linear)
N_FOLDS = 5            # número de folds para validação cruzada

class BertClassifier(nn.Module):
    def __init__(self, num_classes, hidden_dim=HIDDEN_DIM, use_hidden=USE_HIDDEN):
        super(BertClassifier, self).__init__()

        self.bert = BertModel.from_pretrained('neuralmind/bert-base-portuguese-cased')
        self.dropout = nn.Dropout(DROP)
        self.use_hidden = use_hidden
        if self.use_hidden:
            # camada oculta seguida de ativação e dropout antes da saída
            self.classifier = nn.Sequential(
                nn.Linear(self.bert.config.hidden_size, hidden_dim),
                nn.ReLU(),
                nn.Dropout(DROP),
                nn.Linear(hidden_dim, num_classes)
            )
        else:
            self.classifier = nn.Linear(self.bert.config.hidden_size, num_classes)

    def forward(self, input_ids, attention_mask):
        outputs = self.bert(input_ids=input_ids, attention_mask=attention_mask)
        cls_output = outputs.last_hidden_state[:, 0, :]  # Token [CLS]
        cls_output = self.dropout(cls_output)
        logits = self.classifier(cls_output)
        return logits

    def freeze_bert(self):
        for p in self.bert.parameters():
            p.requires_grad = False

    def unfreeze_bert(self):
        for p in self.bert.parameters():
            p.requires_grad = True


random.seed(SEED)
np.random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
torch.backends.cudnn.deterministic = True
torch.backends.cudnn.benchmark = False


def f1_score(preds, targets, num_classes):
    f1s = []
    for c in range(num_classes):
        tp = int(((preds == c) & (targets == c)).sum())
        fp = int(((preds == c) & (targets != c)).sum())
        fn = int(((preds != c) & (targets == c)).sum())

        precision = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        recall = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        f1 = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0.0
        f1s.append(f1)
    return np.array(f1s)

# carrego tokenizer para poder salvá-lo junto com o modelo (útil na inferência)
tokenizer = AutoTokenizer.from_pretrained('neuralmind/bert-base-portuguese-cased')

with open('data/dataset_token/train_tokenized.pkl', 'rb') as f: train_data = pickle.load(f)
with open('data/dataset_token/valid_tokenized.pkl', 'rb') as f: valid_data = pickle.load(f)

train_dataset = TensorDataset(
    train_data['input_ids'],
    train_data['attention_mask'],
    torch.tensor(train_data['labels'], dtype=torch.long)
)

valid_dataset = TensorDataset(
    valid_data['input_ids'],
    valid_data['attention_mask'],
    torch.tensor(valid_data['labels'], dtype=torch.long)
)

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f"Usando dispositivo: {device}", flush=True)

loss_fn = nn.CrossEntropyLoss()

kf = KFold(n_splits=N_FOLDS, shuffle=True, random_state=SEED)

for cat_idx in range(num_categories):
    print(f"\nTreinando modelo para categoria {cat_idx+1}/{num_categories} com {N_FOLDS}-fold CV ===", flush=True)
    out_dir_base = f'./trained_models/{cat_idx+1}-model'
    os.makedirs(out_dir_base, exist_ok=True)

    fold_results = []
    for fold_idx, (train_idx, val_idx) in enumerate(kf.split(range(len(train_dataset)))):
        print(f"\n-> Fold {fold_idx+1}/{N_FOLDS}", flush=True)

        # Subsets e loaders para este fold
        train_sub = Subset(train_dataset, train_idx)
        val_sub = Subset(train_dataset, val_idx)
        # mostrar distribuição de classes para este fold (diagnóstico)
        try:
            train_counts = [0] * num_classes
            val_counts = [0] * num_classes
            for ii in train_idx:
                lab = int(train_dataset[ii][2][cat_idx].item())
                train_counts[lab] += 1
            for ii in val_idx:
                lab = int(train_dataset[ii][2][cat_idx].item())
                val_counts[lab] += 1
            print(f"Distribuição de classes - Treino: {train_counts} | Validação: {val_counts}", flush=True)
        except Exception as _e:
            # se algo inesperado ocorrer (formato diferente), apenas ignore o diagnóstico
            print(f"Aviso: não foi possível computar distribuição de classes para o fold: {_e}", flush=True)

        train_loader = DataLoader(train_sub, batch_size=BATCH, shuffle=True)
        valid_loader = DataLoader(val_sub, batch_size=BATCH)

        model = BertClassifier(num_classes)
        model.to(device)

        # congelar BERT nas primeiras épocas se desejado
        if FREEZE_EPOCHS > 0:
            model.freeze_bert()

        optimizer = AdamW([p for p in model.parameters() if p.requires_grad], lr=LR, weight_decay=WD)

        train_losses = []
        valid_losses = []
        train_accuracies = []
        valid_accuracies = []

        best_valid_loss = float('inf')
        patience = PATIENCE
        epochs_without_improvement = 0
        best_macro_f1 = -1.0

        for epoch in range(EPOCHS):
            print(f"\nÉpoca {epoch+1}/{EPOCHS} (Categoria {cat_idx+1} - Fold {fold_idx+1}):", flush=True)

            # se chegou à época para descongelar, reativa BERT e recria optimizer
            if epoch == FREEZE_EPOCHS:
                print("-> Descongelando BERT e atualizando otimizador", flush=True)
                model.unfreeze_bert()
                optimizer = AdamW(model.parameters(), lr=LR, weight_decay=WD)

            model.train()

            total_train_loss = 0.0
            train_correct = 0
            train_total = 0

            for i, batch in enumerate(train_loader):
                input_ids, attention_mask, labels = [b.to(device) for b in batch]
                targets = labels[:, cat_idx]

                optimizer.zero_grad()
                logits = model(input_ids, attention_mask)
                loss = loss_fn(logits, targets)
                loss.backward()

                torch.nn.utils.clip_grad_norm_(model.parameters(), CLIP_NORM)
                optimizer.step()

                total_train_loss += loss.item()

                preds = torch.argmax(logits, dim=1)
                train_correct += (preds == targets).sum().item()
                train_total += targets.size(0)

                if (i + 1) % 5 == 0:
                    print(f"->Batch {i+1}/{len(train_loader)} (Loss: {loss.item():.4f})", flush=True)

            train_loss = total_train_loss / len(train_loader)
            train_acc = train_correct / train_total if train_total > 0 else 0.0

            train_losses.append(train_loss)
            train_accuracies.append(train_acc)
            # calcular acurácia de treino em modo eval (sem dropout) para comparação justa com validação
            eval_train_acc = None
            try:
                model.eval()
                eval_train_correct = 0
                eval_train_total = 0
                with torch.no_grad():
                    for batch in DataLoader(train_sub, batch_size=BATCH):
                        input_ids_t, attention_mask_t, labels_t = [b.to(device) for b in batch]
                        targets_t = labels_t[:, cat_idx]
                        logits_t = model(input_ids_t, attention_mask_t)
                        preds_t = torch.argmax(logits_t, dim=1)
                        eval_train_correct += (preds_t == targets_t).sum().item()
                        eval_train_total += targets_t.size(0)
                eval_train_acc = eval_train_correct / eval_train_total if eval_train_total > 0 else 0.0
            except Exception as _e:
                print(f"Aviso: falha ao computar acurácia de treino em modo eval: {_e}", flush=True)

            print(f"\nIniciando validação da época {epoch+1}/{EPOCHS} (Categoria {cat_idx+1} - Fold {fold_idx+1}):", flush=True)
            model.eval()

            total_valid_loss = 0.0
            valid_correct = 0
            valid_total = 0

            preds_list = None
            targets_list = None
            with torch.no_grad():
                for i, batch in enumerate(valid_loader):
                    input_ids, attention_mask, labels = [b.to(device) for b in batch]
                    targets = labels[:, cat_idx]

                    logits = model(input_ids, attention_mask)
                    loss = loss_fn(logits, targets)

                    total_valid_loss += loss.item()

                    preds = torch.argmax(logits, dim=1)
                    valid_correct += (preds == targets).sum().item()
                    valid_total += targets.size(0)

                    if preds_list is None:
                        preds_list = preds.detach().cpu()
                        targets_list = targets.detach().cpu()
                    else:
                        preds_list = torch.cat((preds_list, preds.detach().cpu()), dim=0)
                        targets_list = torch.cat((targets_list, targets.detach().cpu()), dim=0)

                    if (i + 1) % 10 == 0 or i == len(valid_loader) - 1:
                        print(f"->Validação: Batch {i+1}/{len(valid_loader)} processado", flush=True)

            valid_loss = total_valid_loss / len(valid_loader)
            valid_acc = valid_correct / valid_total if valid_total > 0 else 0.0

            valid_losses.append(valid_loss)
            valid_accuracies.append(valid_acc)

            preds_np = preds_list.numpy() if 'preds_list' in locals() else np.array([])
            targets_np = targets_list.numpy() if 'targets_list' in locals() else np.array([])
            if preds_np.size > 0:
                f1s = f1_score(preds_np, targets_np, num_classes)
                macro_f1 = float(np.mean(f1s))
            else:
                f1s = np.zeros(num_classes)
                macro_f1 = 0.0

            valid_f1s_str = ', '.join([f"class{i}:{f1s[i]:.4f}" for i in range(len(f1s))])
            print(f'F1 por classe -> {valid_f1s_str} | Macro F1: {macro_f1:.4f}', flush=True)

            print(f'Loss -> Treino: {train_loss:.4f} | Validação: {valid_loss:.4f}', flush=True)
            print(f'Acurácia -> Treino: {train_acc:.4f} | Validação: {valid_acc:.4f}', flush=True)

            improved = False
            if macro_f1 > best_macro_f1:
                best_macro_f1 = macro_f1
                best_valid_loss = valid_loss
                epochs_without_improvement = 0
                improved = True
                best_fold_path = os.path.join(out_dir_base, f'best_model_fold{fold_idx+1}.pth')
                os.makedirs(out_dir_base, exist_ok=True)
                torch.save({'model_state_dict': model.state_dict(),
                            'num_classes': num_classes,
                            'category_index': cat_idx,
                            'dropout': DROP,
                            'best_macro_f1': best_macro_f1,
                            'seed': SEED,
                            'fold': fold_idx+1},
                           best_fold_path)
            else:
                epochs_without_improvement += 1
                if epochs_without_improvement >= patience:
                    print(f"Early stopping na época {epoch+1} (Categoria {cat_idx+1} - Fold {fold_idx+1})", flush=True)
                    break

        # salvar modelo final do fold
        out_dir = os.path.join(out_dir_base, f'fold_{fold_idx+1}')
        os.makedirs(out_dir, exist_ok=True)
        torch.save({
            'model_state_dict': model.state_dict(),
            'num_classes': num_classes,
            'category_index': cat_idx,
            'dropout': DROP,
            'fold': fold_idx+1
        }, os.path.join(out_dir, 'trained_model.pth'))

        params = {
            'num_classes': num_classes,
            'category_index': cat_idx,
            'dropout': DROP,
            'lr': LR,
            'weight_decay': WD,
            'batch_size': BATCH,
            'epochs_ran': len(train_losses),
            'seed': SEED,
            'best_valid_loss': float(best_valid_loss) if best_valid_loss != float('inf') else None,
            'best_macro_f1': float(best_macro_f1) if best_macro_f1 >= 0 else None,
            'fold': fold_idx+1
        }
        with open(os.path.join(out_dir, 'params.json'), 'w', encoding='utf-8') as fh:
            json.dump(params, fh, ensure_ascii=False, indent=2)

        try:
            tokenizer.save_pretrained(out_dir)
        except Exception as e:
            print(f"Aviso: não foi possível salvar o tokenizer: {e}", flush=True)

        plt.figure(figsize=(12, 5))
        plt.subplot(1, 2, 1)
        plt.plot(train_losses, label='Treino', marker='o')
        plt.plot(valid_losses, label='Validação', marker='s')
        plt.xlabel('Épocas')
        plt.ylabel('Loss')
        plt.title(f'Evolução do Loss - Categoria {cat_idx+1} Fold {fold_idx+1}')
        plt.legend()
        plt.grid(True)

        plt.subplot(1, 2, 2)
        plt.plot(train_accuracies, label='Treino', marker='o')
        plt.plot(valid_accuracies, label='Validação', marker='s')
        plt.xlabel('Épocas')
        plt.ylabel('Acurácia')
        plt.title(f'Evolução da Acurácia - Categoria {cat_idx+1} Fold {fold_idx+1}')
        plt.legend()
        plt.grid(True)

        plt.tight_layout()
        plot_path = os.path.join(out_dir, 'training_metrics.png')
        plt.savefig(plot_path)
        plt.close()

        print(f"Modelo e gráfico salvos em '{out_dir}'", flush=True)

        fold_results.append({
            'fold': fold_idx+1,
            'best_macro_f1': float(best_macro_f1) if best_macro_f1 >= 0 else None,
            'best_valid_loss': float(best_valid_loss) if best_valid_loss != float('inf') else None
        })

    # resumo por categoria
    print(f"\nResumo por categoria {cat_idx+1}:")
    for r in fold_results:
        print(f" Fold {r['fold']}: best_macro_f1={r['best_macro_f1']}, best_valid_loss={r['best_valid_loss']}")
