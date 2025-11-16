import os
import sys
import glob
import pickle
import torch
import torch.nn as nn
import numpy as np
import pandas as pd
from torch.utils.data import DataLoader, TensorDataset
from sklearn.metrics import classification_report, accuracy_score
from transformers import BertModel

OUT_DIR = os.path.join(os.path.dirname(__file__), '..', 'trained_models')

os.makedirs(OUT_DIR, exist_ok=True)

out_file = os.path.join(OUT_DIR, 'avaliacao.txt')

print(f"Avaliação será salva em: {out_file}")
sys.stdout = open(out_file, 'w', encoding='utf-8')

class BertClassifier(nn.Module):
    def __init__(self, num_classes, dropout=0.3, hidden_dim=256, use_hidden=False):
        super(BertClassifier, self).__init__()
        self.bert = BertModel.from_pretrained('neuralmind/bert-base-portuguese-cased')
        self.dropout = nn.Dropout(dropout)
        self.use_hidden = use_hidden

        if self.use_hidden:
            self.classifier = nn.Sequential(
                nn.Linear(self.bert.config.hidden_size, hidden_dim),
                nn.ReLU(),
                nn.Dropout(dropout),
                nn.Linear(hidden_dim, num_classes)
            )
        else:
            self.classifier = nn.Linear(self.bert.config.hidden_size, num_classes)
        

    def forward(self, input_ids, attention_mask):
        outputs = self.bert(input_ids=input_ids, attention_mask=attention_mask)
        cls_output = outputs.last_hidden_state[:, 0, :]
        cls_output = self.dropout(cls_output)
        logits = self.classifier(cls_output)
        return logits

def find_best_checkpoint(model_dir):
    best_candidates = glob.glob(os.path.join(model_dir, 'best_model_fold*.pth'))
    best_path = None
    best_score = -float('inf')

    for p in best_candidates:
        ck = torch.load(p, map_location='cpu')
        score = float(ck.get('best_macro_f1', -float('inf')))
        if score > best_score:
            best_score = score
            best_path = p

    if best_path: return best_path

    fold_candidates = glob.glob(os.path.join(model_dir, 'fold_*', 'trained_model.pth'))
    if fold_candidates: return sorted(fold_candidates)[0]

    return None

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f"Usando dispositivo: {device}", flush=True)

print("Carregando dados tokenizados de teste.", flush=True)
with open('data/dataset_token/test_tokenized.pkl', 'rb') as f: test_data = pickle.load(f)

test_dataset = TensorDataset(
    test_data['input_ids'],
    test_data['attention_mask'],
    torch.tensor(test_data['labels'], dtype=torch.long)
)

test_loader = DataLoader(test_dataset, batch_size=32)

num_categories = 3
num_classes = 3
category_names = ['Onça', 'Caseiro', 'Notícia']
class_labels = ['Negativo', 'Neutro', 'Positivo']

all_preds = [[] for _ in range(num_categories)]
all_labels = [[] for _ in range(num_categories)]

print("Carregando checkpoints por categoria e realizando predições.", flush=True)

for cat_idx in range(num_categories):
    model_dir = os.path.join('.', 'trained_models', f'{cat_idx+1}-model')
    ckpt_path = find_best_checkpoint(model_dir)

    if ckpt_path is None:
        print(f"Aviso: nenhum checkpoint encontrado para categoria {cat_idx+1} em {model_dir}. Pulando.", flush=True)
        continue

    print(f"Categoria {cat_idx+1}: usando checkpoint {ckpt_path}", flush=True)
    ck = torch.load(ckpt_path, map_location=device)

    dropout = float(ck.get('dropout', 0.3))
    model = BertClassifier(num_classes=num_classes, dropout=dropout, hidden_dim=256, use_hidden=True)
    model.load_state_dict(ck['model_state_dict'])

    model.to(device)
    model.eval()

    with torch.no_grad():
        for batch in test_loader:
            input_ids, attention_mask, labels = [b.to(device) for b in batch]
            logits = model(input_ids, attention_mask)
            preds = torch.argmax(logits, dim=1)
            all_preds[cat_idx].extend(preds.cpu().numpy())
            all_labels[cat_idx].extend(labels[:, cat_idx].cpu().numpy())

    all_preds[cat_idx] = np.array(all_preds[cat_idx])
    all_labels[cat_idx] = np.array(all_labels[cat_idx])

    acc = accuracy_score(all_labels[cat_idx], all_preds[cat_idx])
    print(f"\nCategoria: {category_names[cat_idx].upper()} (indice {cat_idx})", flush=True)
    print(f"Acurácia: {acc:.4f}\n", flush=True)
    print(classification_report(all_labels[cat_idx], all_preds[cat_idx], target_names=class_labels, digits=4, zero_division=0), flush=True)

if any(len(arr) == 0 for arr in all_labels):
    print("Aviso: algumas categorias não foram avaliadas (falta de checkpoints ou dados).", flush=True)
else:
    total_correct = sum((all_labels[i] == all_preds[i]).sum() for i in range(num_categories))
    total_predictions = sum(len(all_labels[i]) for i in range(num_categories))
    overall_acc = total_correct / total_predictions if total_predictions > 0 else 0.0
    print(f"\nAcurácia (todas as categorias): {overall_acc:.4f}", flush=True)

df_test = pd.read_csv('data/dataset/test.csv')

print("\nErros (exemplos):", flush=True)

for i in range(num_categories):
    all_preds[i] = np.array(all_preds[i])
    all_labels[i] = np.array(all_labels[i])

errors_found = 0
if num_categories > 0:
    n_items = min(len(arr) for arr in all_labels)
else:
    n_items = 0

for idx in range(n_items):
    if not any(all_labels[cat_idx][idx] != all_preds[cat_idx][idx] for cat_idx in range(num_categories)):
        continue

    text = df_test.iloc[idx].get('comment_text') or df_test.iloc[idx].get('text', '')
    print(f"\nExemplo {errors_found + 1}:")
    print(f"Texto: {text}")
    print()
    print("Status  | Categoria | Real     | Predito")
    print("-" * 50)
    for cat_idx, cat_name in enumerate(category_names):
        real_label = class_labels[int(all_labels[cat_idx][idx])]
        pred_label = class_labels[int(all_preds[cat_idx][idx])]
        status = "Correto" if all_labels[cat_idx][idx] == all_preds[cat_idx][idx] else "Erro"
        print(f"{status:7s} | {cat_name:9s} | {real_label:8s} | {pred_label:8s}")
    errors_found += 1

if errors_found == 0:
    print("Nenhum erro encontrado nos exemplos (todas predições corretas).", flush=True)


print("\nAvaliação concluída!", flush=True)

sys.stdout.close()