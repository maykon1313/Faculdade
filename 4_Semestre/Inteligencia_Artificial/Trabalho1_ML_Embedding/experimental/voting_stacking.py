import os
import sys
import csv

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SRC_DIR = os.path.join(ROOT_DIR, 'src')
if SRC_DIR not in sys.path:
    sys.path.insert(0, SRC_DIR)

import numpy as np

from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC

from sklearn.model_selection import StratifiedKFold

from sklearn.preprocessing import normalize
from sklearn.metrics import accuracy_score, classification_report
from sklearn.base import clone

from base import load, get_sentence_transformer

def knn():
    train_val_embeddings, train_val_label, _, _ = load()
    train_val_embeddings_normalized = normalize(train_val_embeddings, norm='l2')
    knn = KNeighborsClassifier(n_neighbors=1, metric='manhattan', weights='distance')
    knn.fit(train_val_embeddings_normalized, train_val_label)
    return knn

def logistic_regression():
    train_val_embeddings, train_val_label, _, _ = load()
    train_val_embeddings_normalized = normalize(train_val_embeddings, norm='l2')
    log_reg = LogisticRegression(max_iter=2000, C=10, solver='lbfgs', penalty="l2")
    log_reg.fit(train_val_embeddings_normalized, train_val_label)
    return log_reg

def svm():
    train_val_embeddings, train_val_label, _, _ = load()
    train_val_embeddings_normalized = normalize(train_val_embeddings, norm='l2')
    svm = SVC(C=10, gamma=1, kernel='rbf', probability=True)
    svm.fit(train_val_embeddings_normalized, train_val_label)
    return svm

def get_classifiers():
    knn_model = knn()
    log_reg_model = logistic_regression()
    svm_model = svm()
    return knn_model, log_reg_model, svm_model

def prediction(description, best_model, transform_model):
    sen_embed = transform_model.encode(description, convert_to_numpy=True)
    sen_embed_normalized = normalize([sen_embed], norm='l2')
    probs = best_model.predict_proba(sen_embed_normalized)[0]
    classes = best_model.classes_
    labeled = list(zip(classes, (probs * 100).round(2)))
    labeled_sorted = sorted(labeled, key=lambda x: x[1], reverse=True)
    return labeled_sorted

def format(pred_list):
    return ", ".join([f"{label}: {pct}%" for label, pct in pred_list])

def voting():
    knn_model, log_reg_model, svm_model = get_classifiers()

    transformer_model = get_sentence_transformer()

    with open('data/separated/feiticos_test.csv', encoding='utf-8') as csvfile:
        i = 1
        reader = csv.DictReader(csvfile)
        for row in reader:
            school = row['escola']
            description = row['descricao']

            print(f"PREDIÇÃO {i}:")
            print("KNN: " + format(prediction(description, knn_model, transformer_model)))
            print("LR: " + format(prediction(description, log_reg_model, transformer_model)))
            print("SVM: " + format(prediction(description, svm_model, transformer_model)))
            print("ESCOLA: " + school)
            print()

            i += 1

def weighted_vote(weights=(1.0, 1.0, 1.0), show_individual=True):
    knn_model, log_reg_model, svm_model = get_classifiers()
    transformer_model = get_sentence_transformer()

    w_knn, w_lr, w_svm = weights

    correct = 0
    total = 0
    predictions = []
    true_labels = []

    with open('data/separated/feiticos_test.csv', encoding='utf-8') as csvfile:
        i = 1
        reader = csv.DictReader(csvfile)
        for row in reader:
            school = row['escola']
            description = row['descricao']

            sen_embed = transformer_model.encode(description, convert_to_numpy=True)
            sen_embed_normalized = normalize([sen_embed], norm='l2')

            probs_knn = knn_model.predict_proba(sen_embed_normalized)[0]
            classes_knn = knn_model.classes_
            probs_lr = log_reg_model.predict_proba(sen_embed_normalized)[0]
            classes_lr = log_reg_model.classes_
            probs_svm = svm_model.predict_proba(sen_embed_normalized)[0]
            classes_svm = svm_model.classes_

            all_classes = list(dict.fromkeys(list(classes_knn) + list(classes_lr) + list(classes_svm)))

            def map_probs(classes, probs):
                m = {c: 0.0 for c in all_classes}
                for c, p in zip(classes, probs):
                    m[c] = p
                return np.array([m[c] for c in all_classes])

            p_knn = map_probs(classes_knn, probs_knn)
            p_lr = map_probs(classes_lr, probs_lr)
            p_svm = map_probs(classes_svm, probs_svm)

            combined = (w_knn * p_knn) + (w_lr * p_lr) + (w_svm * p_svm)

            if combined.sum() > 0:
                combined /= combined.sum()

            labeled = list(zip(all_classes, (combined * 100).round(2)))
            labeled_sorted = sorted(labeled, key=lambda x: x[1], reverse=True)

            print(f"PREDIÇÃO PONDERADA {i}:")
            if show_individual:
                print("KNN: " + format(list(zip(classes_knn, (probs_knn * 100).round(2)))))
                print("LR: " + format(list(zip(classes_lr, (probs_lr * 100).round(2)))))
                print("SVM: " + format(list(zip(classes_svm, (probs_svm * 100).round(2)))))
                print()

            top_label, top_pct = labeled_sorted[0]
            print(f"PONDERADA: {top_label}: {top_pct}%")
            print("ESCOLA: " + school)
            print()

            predictions.append(top_label)
            true_labels.append(school)

            if str(top_label).strip().lower() == str(school).strip().lower():
                correct += 1
            total += 1

            i += 1

    # resumo
    if total > 0:
        pct = correct / total * 100
    else:
        pct = 0.0
    print(f"ACERTOS PONDERADA: {correct}/{total} ({pct:.2f}%)")

    print(classification_report(true_labels, predictions, zero_division=0))

def stacking():
    train_embeddings, train_labels, _, _ = load()
    X = normalize(train_embeddings, norm='l2')
    y = np.array(train_labels)

    all_classes = np.unique(y)
    n_classes = len(all_classes)

    base_models = [
        KNeighborsClassifier(n_neighbors=1, metric='manhattan', weights='distance'),
        LogisticRegression(max_iter=2000, C=10, solver='lbfgs', penalty="l2"),
        SVC(C=10, gamma=1, kernel='rbf', probability=True)
    ]

    # out-of-fold predictions: (n_samples, n_models * n_classes)
    n_models = len(base_models)
    oof_preds = np.zeros((X.shape[0], n_models * n_classes))

    skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)

    def map_probs_to_all(classes_pred, probs_pred):
        m = {c: 0.0 for c in all_classes}
        for c, p in zip(classes_pred, probs_pred):
            m[c] = p
        return np.array([m[c] for c in all_classes])

    # gerar previsões out-of-fold
    for fold_idx, (tr_idx, val_idx) in enumerate(skf.split(X, y)):
        X_tr, X_val = X[tr_idx], X[val_idx]
        y_tr = y[tr_idx]
        for m_idx, model in enumerate(base_models):
            clf = clone(model)
            clf.fit(X_tr, y_tr)
            probs = clf.predict_proba(X_val)
            # para cada linha de probs (val), mapear para order de all_classes e armazenar
            for i_row, p_row in enumerate(probs):
                mapped = map_probs_to_all(clf.classes_, p_row)
                oof_preds[val_idx[i_row], m_idx * n_classes:(m_idx + 1) * n_classes] = mapped

    # treinar modelos base finais em todo o conjunto
    fitted_base = []
    for model in base_models:
        clf = clone(model)
        clf.fit(X, y)
        fitted_base.append(clf)

    # treinar meta-classificador sobre as previsões out-of-fold
    meta_clf = LogisticRegression(max_iter=2000)
    meta_clf.fit(oof_preds, y)

    # usar na inferência (arquivo de teste) — produzir saída similar às outras funções
    transformer_model = get_sentence_transformer()
    correct = 0
    total = 0
    predictions = []
    true_labels = []

    with open('data/separated/feiticos_test.csv', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile)
        i = 1
        for row in reader:
            school = row['escola']
            description = row['descricao']

            sen_embed = transformer_model.encode(description, convert_to_numpy=True)
            sen_embed_normalized = normalize([sen_embed], norm='l2')[0]

            # obter probabilidades de cada base model e concatenar em ordem fixa
            features = []
            for clf in fitted_base:
                probs = clf.predict_proba([sen_embed_normalized])[0]
                mapped = map_probs_to_all(clf.classes_, probs)
                features.append(mapped)
            meta_features = np.hstack(features).reshape(1, -1)

            meta_probs = meta_clf.predict_proba(meta_features)[0]
            meta_classes = meta_clf.classes_
            labeled = list(zip(meta_classes, (meta_probs * 100).round(2)))
            labeled_sorted = sorted(labeled, key=lambda x: x[1], reverse=True)

            print(f"PREDIÇÃO STACKING {i}:")
            print("STACKING: " + format(labeled_sorted))
            print("ESCOLA: " + school)
            print()

            top_label = labeled_sorted[0][0]
            predictions.append(top_label)
            true_labels.append(school)
            
            if str(top_label).strip().lower() == str(school).strip().lower():
                correct += 1
            total += 1

            i += 1

    if total > 0:
        pct = correct / total * 100
    else:
        pct = 0.0
    print(f"ACERTOS STACKING: {correct}/{total} ({pct:.2f}%)")

    print(classification_report(true_labels, predictions, zero_division=0))

def stacking_improved():
    from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
    from sklearn.naive_bayes import GaussianNB

    train_embeddings, train_labels, _, _ = load()
    X = normalize(train_embeddings, norm='l2')
    y = np.array(train_labels)

    all_classes = np.unique(y)
    n_classes = len(all_classes)

    # Conjunto mais diverso de modelos base
    base_models = [
        # Modelos originais otimizados
        KNeighborsClassifier(n_neighbors=1, metric='manhattan', weights='distance'),
        LogisticRegression(max_iter=3000, C=10, solver='lbfgs', penalty="l2"),
        SVC(C=10, gamma=1, kernel='rbf', probability=True),
        
        # Novos modelos para aumentar diversidade
        RandomForestClassifier(n_estimators=100, max_depth=10, random_state=42),
        GradientBoostingClassifier(n_estimators=100, learning_rate=0.1, max_depth=5, random_state=42),
        GaussianNB(),
        
        # Variações dos modelos existentes
        KNeighborsClassifier(n_neighbors=3, metric='cosine', weights='distance'),
        SVC(C=1, gamma='scale', kernel='linear', probability=True),
    ]

    n_models = len(base_models)
    
    # Usar mais folds para melhor estimativa
    skf = StratifiedKFold(n_splits=7, shuffle=True, random_state=42)
    
    # Armazenar tanto probabilidades quanto predições
    oof_probs = np.zeros((X.shape[0], n_models * n_classes))
    oof_preds = np.zeros((X.shape[0], n_models))

    def map_probs_to_all(classes_pred, probs_pred):
        m = {c: 0.0 for c in all_classes}
        for c, p in zip(classes_pred, probs_pred):
            m[c] = p
        return np.array([m[c] for c in all_classes])

    print("Gerando predições out-of-fold...")
    # Gerar previsões out-of-fold
    for fold_idx, (tr_idx, val_idx) in enumerate(skf.split(X, y)):
        print(f"Processando fold {fold_idx + 1}/{skf.n_splits}")
        X_tr, X_val = X[tr_idx], X[val_idx]
        y_tr = y[tr_idx]
        
        for m_idx, model in enumerate(base_models):
            clf = clone(model)
            try:
                clf.fit(X_tr, y_tr)
                probs = clf.predict_proba(X_val)
                preds = clf.predict(X_val)
                
                # Armazenar probabilidades
                for i_row, p_row in enumerate(probs):
                    mapped = map_probs_to_all(clf.classes_, p_row)
                    oof_probs[val_idx[i_row], m_idx * n_classes:(m_idx + 1) * n_classes] = mapped
                
                # Armazenar predições
                for i_row, pred in enumerate(preds):
                    oof_preds[val_idx[i_row], m_idx] = list(all_classes).index(pred)
                    
            except Exception as e:
                print(f"Erro no modelo {m_idx}: {e}")
                # Preencher com valores padrão em caso de erro
                for i_row in range(len(val_idx)):
                    oof_probs[val_idx[i_row], m_idx * n_classes:(m_idx + 1) * n_classes] = 1.0 / n_classes
                    oof_preds[val_idx[i_row], m_idx] = 0

    # Combinar features de probabilidades e predições
    meta_features = np.hstack([oof_probs, oof_preds])

    # Treinar modelos base finais
    print("Treinando modelos base finais...")
    fitted_base = []
    for i, model in enumerate(base_models):
        try:
            clf = clone(model)
            clf.fit(X, y)
            fitted_base.append(clf)
        except Exception as e:
            print(f"Erro ao treinar modelo {i}: {e}")
            fitted_base.append(None)

    # Testar diferentes meta-classificadores
    meta_models = [
        LogisticRegression(max_iter=3000, C=1, solver='lbfgs'),
        RandomForestClassifier(n_estimators=50, max_depth=7, random_state=42),
        GradientBoostingClassifier(n_estimators=50, learning_rate=0.1, random_state=42)
    ]
    
    best_meta_score = 0
    best_meta_clf = None
    
    print("Selecionando melhor meta-classificador...")
    for meta_model in meta_models:
        # Validação cruzada para selecionar o melhor meta-classificador
        cv_scores = []
        for tr_idx, val_idx in skf.split(meta_features, y):
            meta_clf = clone(meta_model)
            meta_clf.fit(meta_features[tr_idx], y[tr_idx])
            score = accuracy_score(y[val_idx], meta_clf.predict(meta_features[val_idx]))
            cv_scores.append(score)
        
        avg_score = np.mean(cv_scores)
        print(f"{meta_model.__class__.__name__}: {avg_score:.4f}")
        
        if avg_score > best_meta_score:
            best_meta_score = avg_score
            best_meta_clf = clone(meta_model)

    # Treinar o melhor meta-classificador
    best_meta_clf.fit(meta_features, y)
    print(f"Melhor meta-classificador: {best_meta_clf.__class__.__name__} (Score: {best_meta_score:.4f})")

    # Avaliação no conjunto de teste
    transformer_model = get_sentence_transformer()
    correct = 0
    total = 0
    predictions = []
    true_labels = []

    print("\nAvaliando no conjunto de teste...")
    with open('data/separated/feiticos_test.csv', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile)
        i = 1
        for row in reader:
            school = row['escola']
            description = row['descricao']

            sen_embed = transformer_model.encode(description, convert_to_numpy=True)
            sen_embed_normalized = normalize([sen_embed], norm='l2')[0]

            # Obter features para o meta-classificador
            prob_features = []
            pred_features = []
            
            for clf in fitted_base:
                if clf is not None:
                    try:
                        probs = clf.predict_proba([sen_embed_normalized])[0]
                        pred = clf.predict([sen_embed_normalized])[0]
                        
                        mapped_probs = map_probs_to_all(clf.classes_, probs)
                        prob_features.append(mapped_probs)
                        pred_features.append(list(all_classes).index(pred))
                    except:
                        # Fallback em caso de erro
                        prob_features.append(np.ones(n_classes) / n_classes)
                        pred_features.append(0)
                else:
                    prob_features.append(np.ones(n_classes) / n_classes)
                    pred_features.append(0)
            
            test_meta_features = np.hstack([
                np.hstack(prob_features),
                np.array(pred_features)
            ]).reshape(1, -1)

            # Predição final
            meta_probs = best_meta_clf.predict_proba(test_meta_features)[0]
            meta_pred = best_meta_clf.predict(test_meta_features)[0]
            meta_classes = best_meta_clf.classes_
            
            labeled = list(zip(meta_classes, (meta_probs * 100).round(2)))
            labeled_sorted = sorted(labeled, key=lambda x: x[1], reverse=True)

            print(f"PREDIÇÃO STACKING MELHORADO {i}:")
            print("STACKING: " + format(labeled_sorted))
            print("ESCOLA: " + school)
            print()

            predictions.append(meta_pred)
            true_labels.append(school)
            
            if str(meta_pred).strip().lower() == str(school).strip().lower():
                correct += 1
            total += 1
            i += 1

    # Resultados detalhados
    if total > 0:
        pct = correct / total * 100
    else:
        pct = 0.0
    
    print(f"ACERTOS STACKING MELHORADO: {correct}/{total} ({pct:.2f}%)")
    print("\nRelatório detalhado:")
    print(classification_report(true_labels, predictions, zero_division=0))
    
    return best_meta_clf, fitted_base

if __name__ == "__main__":
    #voting()

    #weighted_vote((0.87, 0.81, 0.84), False)
    #weighted_vote((0.7730, 0.7349, 0.8016), False)
    """
    KNN: mean=0.7730 std=0.0428
    LR: mean=0.7349 std=0.0249
    SVM: mean=0.8016 std=0.0194

    ---------------------------------------------------
    
    ACERTOS STACKING: 62/70 (88.57%)

                precision    recall  f1-score   support

    abjuration       0.78      0.78      0.78         9
    conjuration      0.91      0.91      0.91        11
    divination       1.00      1.00      1.00         6
    enchantment      1.00      0.83      0.91         6
    evocation        0.86      0.92      0.89        13
    illusion         1.00      1.00      1.00         6
    necromancy       1.00      1.00      1.00         5
    transmutation    0.79      0.79      0.79        14

    accuracy                             0.89        70
    macro avg        0.92      0.90      0.91        70
    weighted avg     0.89      0.89      0.89        70
    """

    #stacking()
    """
    ACERTOS STACKING: 62/70 (88.57%)
                precision    recall  f1-score   support

    abjuration       0.70      0.78      0.74         9
    conjuration      1.00      0.91      0.95        11
    divination       1.00      1.00      1.00         6
    enchantment      1.00      0.83      0.91         6
    evocation        0.86      0.92      0.89        13
    illusion         1.00      1.00      1.00         6
    necromancy       0.80      0.80      0.80         5
    transmutation    0.86      0.86      0.86        14

    accuracy                             0.89        70
    macro avg        0.90      0.89      0.89        70
    weighted avg     0.89      0.89      0.89        70
    """

    #stacking_improved()
    """
    ACERTOS STACKING: 62/70 (88.57%)

                precision    recall  f1-score   support

    abjuration       0.78      0.78      0.78         9
    conjuration      1.00      1.00      1.00        11
    divination       1.00      1.00      1.00         6
    enchantment      1.00      0.83      0.91         6
    evocation        0.80      0.92      0.86        13
    illusion         1.00      1.00      1.00         6
    necromancy       0.80      0.80      0.80         5
    transmutation    0.85      0.79      0.81        14

    accuracy                             0.89        70
    macro avg        0.90      0.89      0.89        70
    weighted avg     0.89      0.89      0.89        70
    """
