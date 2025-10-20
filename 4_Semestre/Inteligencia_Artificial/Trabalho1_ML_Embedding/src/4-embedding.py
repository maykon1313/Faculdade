from sentence_transformers import SentenceTransformer
import numpy as np
import pandas as pd

def carregar_dados():
    train_df = pd.read_csv('data/separated/feiticos_train.csv')
    val_df = pd.read_csv('data/separated/feiticos_val.csv')
    test_df = pd.read_csv('data/separated/feiticos_test.csv')

    train_texts = train_df['descricao'].tolist()
    validation_texts = val_df['descricao'].tolist()
    test_texts = test_df['descricao'].tolist()

    train_label = train_df['escola'].tolist()
    validation_label = val_df['escola'].tolist()
    test_label = test_df['escola'].tolist()

    return train_texts, validation_texts, test_texts, train_label, validation_label, test_label

def gerar_embeddings(model, textos):
    return model.encode(textos, convert_to_numpy=True)

def salvar_embeddings(arquivo, train_embeddings, validation_embeddings, test_embeddings, train_label, validation_label, test_label):
    np.savez_compressed(
        arquivo,
        train_embeddings=train_embeddings,
        validation_embeddings=validation_embeddings,
        test_embeddings=test_embeddings,
        train_label=train_label,
        validation_label=validation_label,
        test_label=test_label
    )

def embeddings():
    # Carregar os dados
    train_texts, validation_texts, test_texts, train_label, validation_label, test_label = carregar_dados()

    # Carregar o modelo
    model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')

    # Gerar embeddings
    train_embeddings = gerar_embeddings(model, train_texts)
    validation_embeddings = gerar_embeddings(model, validation_texts)
    test_embeddings = gerar_embeddings(model, test_texts)

    print(f"\nNúmero de textos de treino: {len(train_texts)}")
    print(f"Formato dos embeddings de treino: {train_embeddings.shape}")

    print(f"\nNúmero de textos de validação: {len(validation_texts)}")
    print(f"Formato dos embeddings de validação: {validation_embeddings.shape}")

    print(f"\nNúmero de textos de teste: {len(test_texts)}")
    print(f"Formato dos embeddings de teste: {test_embeddings.shape}")

    # Salvar os embeddings e labels
    salvar_embeddings(
        'data/feiticos_embeddings.npz',
        train_embeddings, validation_embeddings, test_embeddings,
        train_label, validation_label, test_label
    )

if __name__ == "__main__":
    embeddings()