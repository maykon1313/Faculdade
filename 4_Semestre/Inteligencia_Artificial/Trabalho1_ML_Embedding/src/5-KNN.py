from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, classification_report, f1_score
from sklearn.model_selection import cross_val_score
from sklearn.preprocessing import normalize
from base import load, get_sentence_transformer, interactive_menu

def train_knn_cross_validation(k_folds):
    k_values = list(range(1, 31, 2)) 
    metrics = ['euclidean', 'manhattan', 'cosine', 'minkowski', 'hamming']

    best_k = 1
    best_model = None
    best_metric = 'euclidean'
    best_f1_score = 0

    train_val_embeddings, train_val_label, test_embeddings, test_label = load()

    # Normalizar os embeddings com L2
    train_val_embeddings_normalized = normalize(train_val_embeddings, norm='l2')
    test_embeddings_normalized = normalize(test_embeddings, norm='l2')

    print(f"Usando validação cruzada com {k_folds} folds\n")

    # Criar e treinar o modelo KNN com validação cruzada
    for k in k_values:
        for metric in metrics:
            knn = KNeighborsClassifier(n_neighbors=k, metric=metric, weights='distance')
            
            # Cross-validation com f1-score
            cv_scores = cross_val_score(knn, train_val_embeddings_normalized, train_val_label, cv=k_folds, scoring='f1_weighted')
            
            mean_f1 = cv_scores.mean()
            std_f1 = cv_scores.std()

            print(f"K: {k}, Métrica: {metric}, F1-score médio: {mean_f1:.4f} (±{std_f1:.4f})")

            if mean_f1 > best_f1_score:
                best_k = k
                best_metric = metric
                best_f1_score = mean_f1

    # Treinar o modelo final com todos os dados de treino+validação
    best_model = KNeighborsClassifier(n_neighbors=best_k, metric=best_metric, weights='distance')
    best_model.fit(train_val_embeddings_normalized, train_val_label)

    # Testar no conjunto de teste
    test_predictions = best_model.predict(test_embeddings_normalized)
    test_accuracy = accuracy_score(test_label, test_predictions)
    test_f1 = f1_score(test_label, test_predictions, average='weighted')

    print(f"\nMelhor valor de K: {best_k}")
    print(f"Melhor métrica: {best_metric}")
    print(f"F1-score médio na validação cruzada: {best_f1_score:.4f}")
    print(f"Acurácia no teste: {test_accuracy:.4f}")
    print(f"F1-score no teste: {test_f1:.4f}")

    # Relatório de classificação detalhado
    print("\nRelatório de Classificação no Conjunto de Teste:")
    print(classification_report(test_label, test_predictions))

    return best_k, best_metric, best_model

def knn_cross_validation(k_folds):
    print("treinando com validação cruzada...")
    best_k, best_metric, best_model = train_knn_cross_validation(k_folds)

    if best_model is None:
        print("Erro ao carregar o modelo.")
        return

    transformer_model = get_sentence_transformer()

    info = f"Usando K = {best_k} e Metrica = {best_metric} (com validação cruzada)."
    
    interactive_menu(best_model, transformer_model, info)

if __name__ == "__main__":
    knn_cross_validation(5)
