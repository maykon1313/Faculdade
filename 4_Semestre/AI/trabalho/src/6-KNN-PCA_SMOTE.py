import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
from sentence_transformers import SentenceTransformer

def load():
    # Carregar os embeddings e labels salvos
    data = np.load('data/feiticos_embeddings.npz')

    train_embeddings = data['train_embeddings']
    validation_embeddings = data['validation_embeddings']
    test_embeddings = data['test_embeddings']

    train_label = data['train_label']
    validation_label = data['validation_label']
    test_label = data['test_label']

    # Codificar labels para numéricos (PCA - SMOTE)
    label_encoder = LabelEncoder()
    train_label_encoded = label_encoder.fit_transform(train_label)
    validation_label_encoded = label_encoder.transform(validation_label)
    test_label_encoded = label_encoder.transform(test_label)

    # Normalizar os dados
    scaler = StandardScaler()
    train_embeddings_scaled = scaler.fit_transform(train_embeddings)
    validation_embeddings_scaled = scaler.transform(validation_embeddings)
    test_embeddings_scaled = scaler.transform(test_embeddings)

    # Aplicar SMOTE para balancear as classes no conjunto de treino
    smote = SMOTE(random_state=42)
    smote_result = smote.fit_resample(train_embeddings_scaled, train_label_encoded)
    if len(smote_result) == 2:
        train_embeddings_balanced, train_label_balanced = smote_result
    else:
        train_embeddings_balanced, train_label_balanced, _ = smote_result

    # Aplicar PCA para redução de dimensionalidade (manter 95% da variância)
    pca = PCA(n_components=0.95, random_state=42)
    train_embeddings_balanced = np.asarray(train_embeddings_balanced)
    train_embeddings_pca = pca.fit_transform(train_embeddings_balanced)
    validation_embeddings_pca = pca.transform(validation_embeddings_scaled)
    test_embeddings_pca = pca.transform(test_embeddings_scaled)

    return train_label_balanced, validation_label_encoded, test_label_encoded, train_embeddings_pca, validation_embeddings_pca, test_embeddings_pca, scaler, pca, label_encoder

def train():
    # Valores de K e métricas de distância
    k_values = list(range(1, 31)) 
    metrics = ['euclidean', 'manhattan', 'cosine', 'minkowski', 'hamming']

    best_k = 1
    best_model = None
    best_metric = 'euclidean'
    best_accuracy = 0

    train_label, validation_label, test_label, train_embeddings_scaled, validation_embeddings_scaled, test_embeddings_scaled, scaler, pca, label_encoder = load()

    # Criar e treinar o modelo KNN
    for k in k_values:
        # Testar diferentes métricas de distância
        for metric in metrics:
            knn = KNeighborsClassifier(n_neighbors=k, metric=metric, weights='distance')
            knn.fit(train_embeddings_scaled, train_label)

            # Fazer previsões no conjunto de validação
            val_predictions = knn.predict(validation_embeddings_scaled)
            val_accuracy = accuracy_score(validation_label, val_predictions)
            print(f"K: {k}, Métrica: {metric}, Acurácia: {val_accuracy:.4f}")
            
            if val_accuracy > best_accuracy:
                best_k = k
                best_model = knn
                best_metric = metric
                best_accuracy = val_accuracy

    if best_model is not None:
        # Fazer previsões no conjunto de teste
        test_predictions = best_model.predict(test_embeddings_scaled)
        test_accuracy = accuracy_score(test_label, test_predictions)
        print(f"\nMelhor valor de K: {best_k}")
        print(f"Melhor métrica: {best_metric}")
        print(f"Acurácia de validação: {best_accuracy:.4f}")
        print(f"Acurácia no teste: {test_accuracy:.4f}")

        # Relatório de classificação detalhado
        print("\nRelatório de Classificação no Conjunto de Teste:")
        print(classification_report(test_label, test_predictions))
    else:
        print("Erro: Nenhum modelo foi treinado com sucesso.")

    return best_k, best_model, best_metric, scaler, pca, label_encoder

def main():
    print("treinando...")
    best_k, best_model, best_metric, scaler, pca, label_encoder = train()
    
    while True:
        print("Deseja testar para um input personalizado? (s/n)")
        resp = input()

        if resp == "n":
            print("Saindo.")
            return

        elif resp == "s" and best_model != None:
            print("Digite a escola: ")
            school = input()

            print("Digite a descrição do feitiço: ")
            sentence = input()

            model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')

            sen_embed = model.encode(sentence, convert_to_numpy=True)

            sen_embed_scaled = scaler.transform([sen_embed])

            sen_embed_pca = pca.transform(sen_embed_scaled)

            prediction = best_model.predict(sen_embed_pca)

            prediction_decoded = label_encoder.inverse_transform(prediction)

            print(f"Usando K = {best_k} e Metrica = {best_metric}.")

            if prediction_decoded[0] == school:
                print(f"O modelo corretamente acertou a escola: {prediction_decoded[0]}.")
            
            else:
                print(f"O modelo não acertou a escola: {prediction_decoded[0]}.")

        else:
            print("Erro ao carregar o modelo ou input.")

if __name__ == "__main__":
    main()