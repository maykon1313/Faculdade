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

from sklearn.model_selection import cross_val_score, StratifiedKFold
from sklearn.preprocessing import normalize

from base import load

train_embeddings, train_labels, _, _ = load()
X = normalize(train_embeddings, norm='l2')
y = np.array(train_labels)

skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
for name, model in [("KNN", KNeighborsClassifier(n_neighbors=1, metric='manhattan', weights='distance')),
                    ("LR", LogisticRegression(max_iter=2000, C=10, solver='lbfgs')),
                    ("SVM", SVC(C=10, gamma=1, kernel='rbf', probability=True))]:
    scores = cross_val_score(model, X, y, cv=skf, scoring='accuracy', n_jobs=-1)
    print(f"{name}: mean={scores.mean():.4f} std={scores.std():.4f}")