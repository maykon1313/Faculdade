from sentence_transformers import SentenceTransformer
import numpy as np
import pandas as pd

# Carregar os datasets separados
train_df = pd.read_csv('data/separated/feiticos_train.csv')
val_df = pd.read_csv('data/separated/feiticos_val.csv')
test_df = pd.read_csv('data/separated/feiticos_test.csv')

# Extrair textos e labels
train_texts = train_df['descricao'].tolist()
validation_texts = val_df['descricao'].tolist()
test_texts = test_df['descricao'].tolist()

train_label = train_df['escola'].tolist()
validation_label = val_df['escola'].tolist()
test_label = test_df['escola'].tolist()

# Carregar o modelo
model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')

# Gerar embeddings
train_embeddings = model.encode(train_texts, convert_to_numpy=True)
validation_embeddings = model.encode(validation_texts, convert_to_numpy=True)
test_embeddings = model.encode(test_texts, convert_to_numpy=True)

print(f"\nNúmero de textos de treino: {len(train_texts)}")
print(f"Formato dos embeddings de treino: {train_embeddings.shape}")

print(f"\nNúmero de textos de validação: {len(validation_embeddings)}")
print(f"Formato dos embeddings de validação: {validation_embeddings.shape}")

print(f"\nNúmero de textos de teste: {len(test_embeddings)}")
print(f"Formato dos embeddings de teste: {test_embeddings.shape}")

# Salvar os embeddings e labels
np.savez_compressed(
    'data/feiticos_embeddings.npz',
    train_embeddings=train_embeddings,
    validation_embeddings=validation_embeddings,
    test_embeddings=test_embeddings,
    train_label=train_label,
    validation_label=validation_label,
    test_label=test_label
)