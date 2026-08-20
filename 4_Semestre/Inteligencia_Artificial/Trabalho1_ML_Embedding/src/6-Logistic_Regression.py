from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report, f1_score
from sklearn.model_selection import cross_val_score
from sklearn.preprocessing import normalize
from base import load, get_sentence_transformer, interactive_menu

def train_lr_cross_validation(k_folds):
    c_values = [0.001, 0.01, 0.1, 1, 10, 100, 1000]

    best_c = 0.01
    best_model = None
    best_f1_score = 0

    train_val_embeddings, train_val_label, test_embeddings, test_label = load()

    # Normalizar os embeddings com L2
    train_val_embeddings_normalized = normalize(train_val_embeddings, norm='l2')
    test_embeddings_normalized = normalize(test_embeddings, norm='l2')

    print(f"Usando validação cruzada com {k_folds} folds\n")

    for c in c_values:
        lr = LogisticRegression(C=c)
        
        # Cross-validation com f1-score
        cv_scores = cross_val_score(lr, train_val_embeddings_normalized, train_val_label, cv=k_folds, scoring='f1_weighted')
        
        mean_f1 = cv_scores.mean()
        std_f1 = cv_scores.std()

        print(f"C: {c}, F1-score médio: {mean_f1:.4f} (±{std_f1:.4f})")

        if mean_f1 > best_f1_score:
            best_c = c
            best_f1_score = mean_f1

    # Treinar o modelo final com todos os dados de treino+validação
    best_model = LogisticRegression(C=best_c, max_iter=2000)
    best_model.fit(train_val_embeddings_normalized, train_val_label)

    # Testar no conjunto de teste
    test_predictions = best_model.predict(test_embeddings_normalized)
    test_accuracy = accuracy_score(test_label, test_predictions)
    test_f1 = f1_score(test_label, test_predictions, average='weighted')

    print(f"\nMelhor valor de C: {best_c}")
    print(f"F1-score médio na validação cruzada: {best_f1_score:.4f}")
    print(f"Acurácia no teste: {test_accuracy:.4f}")
    print(f"F1-score no teste: {test_f1:.4f}")

    # Relatório de classificação detalhado
    print("\nRelatório de Classificação no Conjunto de Teste:")
    print(classification_report(test_label, test_predictions))

    return best_c, best_model

def lr_cross_validation(k_folds):
    print("treinando com validação cruzada...")
    best_c, best_model = train_lr_cross_validation(k_folds)

    if best_model is None:
        print("Erro ao carregar o modelo.")
        return

    transformer_model = get_sentence_transformer()

    info = f"Usando C = {best_c} (com validação cruzada)."

    interactive_menu(best_model, transformer_model, info)

if __name__ == "__main__":
    lr_cross_validation(5)
