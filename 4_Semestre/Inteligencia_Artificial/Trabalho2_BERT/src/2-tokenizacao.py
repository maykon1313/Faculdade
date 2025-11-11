import pickle
import pandas as pd
from transformers import BertTokenizer

tokenizer = BertTokenizer.from_pretrained('neuralmind/bert-base-portuguese-cased')

def tokenize_texts(texts, max_length=128):
        encodings = tokenizer(
            texts.tolist(),
            truncation=True,
            padding=True,
            max_length=max_length,
            return_tensors='pt'
        )
        return encodings['input_ids'], encodings['attention_mask']

def token(entrada, saida):
    df = pd.read_csv(entrada)

    labels = df[['onca', 'caseiro', 'notícia']].values

    input_ids, attention_mask = tokenize_texts(df['comment_text'])

    with open(saida, 'wb') as f:
        pickle.dump({'input_ids': input_ids, 'attention_mask': attention_mask, 'labels': labels}, f)

meio = ['train','valid','test']

base_entrada = 'data/dataset/'
ponto_entrada = '.csv'

base_saida = 'data/dataset_token/'
ponto_saida = '_tokenized.pkl'

extra_path = "data/new/extra.csv"
extra_token_path = "data/new/extra_tokenized.pkl"

for i in range(3):
    token(base_entrada+meio[i]+ponto_entrada, base_saida+meio[i]+ponto_saida)

token(extra_path, extra_token_path)
