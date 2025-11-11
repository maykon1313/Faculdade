import pickle
import torch
import torch.nn as nn
import pandas as pd
from torch.utils.data import DataLoader, TensorDataset
from sklearn.metrics import classification_report, accuracy_score
from transformers import BertModel
import numpy as np
import sys
import os

print("Avaliação será salva em: data/new/avaliacao.txt")

sys.stdout = open(os.path.join(os.path.dirname(__file__), '..', 'data', 'new', 'avaliacao.txt'), 'w', encoding='utf-8')

class BertClassifier(nn.Module):
    def __init__(self, num_classes, num_categories, dropout):
        super(BertClassifier, self).__init__()
        self.bert = BertModel.from_pretrained('neuralmind/bert-base-portuguese-cased')
        self.dropout = nn.Dropout(dropout)

        # Criar 3 classificadores, um para cada categoria
        self.classifiers = nn.ModuleList([
            nn.Linear(self.bert.config.hidden_size, num_classes) 
            for _ in range(num_categories)
        ])
    
    def forward(self, input_ids, attention_mask):
        outputs = self.bert(input_ids=input_ids, attention_mask=attention_mask)

        cls_output = outputs.last_hidden_state[:, 0, :]  # Token [CLS]
        cls_output = self.dropout(cls_output)
        
        # Gerar logits para cada categoria
        logits = [classifier(cls_output) for classifier in self.classifiers]
        return logits

print("Carregando modelo treinado.", flush=True)
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
checkpoint = torch.load('./model/trained_model.pth', map_location=device)

model = BertClassifier(
    num_classes=checkpoint['num_classes'],
    num_categories=checkpoint['num_categories'],
    dropout=checkpoint['dropout']
)

model.load_state_dict(checkpoint['model_state_dict'])
model.to(device)
model.eval()

print("Carregando dados de teste.", flush=True)
with open('data/new/extra_tokenized.pkl', 'rb') as f: test_data = pickle.load(f)

test_dataset = TensorDataset(
    test_data['input_ids'],
    test_data['attention_mask'],
    torch.tensor(test_data['labels'], dtype=torch.long)
)

test_loader = DataLoader(test_dataset, batch_size=16)

print("Realizando predições.", flush=True)
all_preds = [[] for _ in range(checkpoint['num_categories'])]
all_labels = [[] for _ in range(checkpoint['num_categories'])]

with torch.no_grad():
    for batch in test_loader:
        input_ids, attention_mask, labels = [b.to(device) for b in batch]
        logits_list = model(input_ids, attention_mask=attention_mask)
        
        for cat_idx in range(checkpoint['num_categories']):
            preds = torch.argmax(logits_list[cat_idx], dim=1)
            all_preds[cat_idx].extend(preds.cpu().numpy())
            all_labels[cat_idx].extend(labels[:, cat_idx].cpu().numpy())

all_preds = [np.array(preds) for preds in all_preds]
all_labels = [np.array(labels) for labels in all_labels]

category_names = ['Onça', 'Caseiro', 'Notícia']
class_labels = ['Negativo', 'Neutro', 'Positivo']

print("\nResultado do teste:")
print()

for cat_idx, cat_name in enumerate(category_names):
    print(f"Categoria: {cat_name.upper()}")
    
    acc = accuracy_score(all_labels[cat_idx], all_preds[cat_idx])
    print(f"Acurácia: {acc:.4f}\n")
    
    print(classification_report(
        all_labels[cat_idx], 
        all_preds[cat_idx], 
        labels=list(range(checkpoint['num_classes'])),
        target_names=class_labels,
        digits=4,
        zero_division=0
    ))

df_test = pd.read_csv('data/new/extra.csv')

total_correct = sum([(all_labels[cat_idx] == all_preds[cat_idx]).sum() for cat_idx in range(len(category_names))])
total_predictions = sum([len(all_labels[cat_idx]) for cat_idx in range(len(category_names))])

overall_acc = total_correct / total_predictions

print(f"Acurácia (todas as categorias): {overall_acc:.4f}")
print()

print("\nErros:")
errors_found = 0
for idx in range(len(all_labels[0])):
    text = df_test.iloc[idx]['comment_text']

    print(f"\nExemplo {errors_found + 1}:")
    print(f"Texto: {text}")
    print()
    
    print("Status  | Categoria | Real     | Predito")
    print("-" * 40)
    for cat_idx, cat_name in enumerate(category_names):
        real_label = class_labels[all_labels[cat_idx][idx]]
        pred_label = class_labels[all_preds[cat_idx][idx]]
        status = "Correto" if all_labels[cat_idx][idx] == all_preds[cat_idx][idx] else "Erro"
        print(f"{status:7s} | {cat_name:9s} | {real_label:8s} | {pred_label:8s}")
    errors_found += 1

print("\nAvaliação concluída!")

# Close the file
sys.stdout.close()  