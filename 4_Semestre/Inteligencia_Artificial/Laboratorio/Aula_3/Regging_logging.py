"""Regressão Logística 2D simples (a partir de rascunho do Colab).

Este script gera dois grupos de pontos em 2D, treina um modelo de regressão
logística binária usando Gradiente Descendente (loss = entropia cruzada) e
plota a fronteira de decisão final. Também salva a figura em
"decision_boundary.png" (útil em ambiente sem display).

Requisitos: numpy, matplotlib.
Execute: python Regging_logging.py
"""

import numpy as np
import matplotlib.pyplot as plt


def sigmoid(z: np.ndarray) -> np.ndarray:
    """Função sigmoide vetorizada."""
    return 1.0 / (1.0 + np.exp(-z))


def gerar_dados(n: int = 100, seed: int | None = 42):
    """Gera dois grupos gaussianos em 2D e retorna X (n_total,3) com bias e y.

    - Primeiro grupo (classe 1) centrado em (0,0)
    - Segundo grupo (classe 0) centrado em (2,2)
    - Adiciona coluna de bias: 1
    """
    if seed is not None:
        np.random.seed(seed)
    cov = [[1, 0], [0, 1]]
    mean1 = [0, 0]
    mean2 = [2, 2]
    x1 = np.random.multivariate_normal(mean1, cov, n).T  # shape (2,n)
    x2 = np.random.multivariate_normal(mean2, cov, n).T  # shape (2,n)
    X2d = np.hstack((x1, x2))  # (2,2n)
    y = np.concatenate((np.ones(n), np.zeros(n)))  # shape (2n,)
    bias = np.ones((1, 2 * n))
    X = np.vstack((bias, X2d)).T  # (2n,3)
    return X, y, x1, x2


def plot_dados(x1: np.ndarray, x2: np.ndarray):
    plt.scatter(x1[0], x1[1], label="Classe 1", alpha=0.7)
    plt.scatter(x2[0], x2[1], label="Classe 0", alpha=0.7)
    plt.legend()


def plot_fronteira(theta: np.ndarray, x1: np.ndarray, x2: np.ndarray, titulo: str = ""):
    """Plota dados e linha theta0 + theta1*x + theta2*y = 0."""
    if theta[2] == 0:
        return
    xmin = min(x1[0].min(), x2[0].min()) - 0.5
    xmax = max(x1[0].max(), x2[0].max()) + 0.5
    xs = np.linspace(xmin, xmax, 200)
    # theta0 + theta1*x + theta2*y = 0 => y = -(theta0 + theta1*x)/theta2
    ys = -(theta[0] + theta[1] * xs) / theta[2]
    plot_dados(x1, x2)
    plt.plot(xs, ys, 'k-', label="Fronteira")
    if titulo:
        plt.title(titulo)
    plt.xlabel("x1")
    plt.ylabel("x2")
    plt.legend()


def loss_cross_entropy(h: np.ndarray, y: np.ndarray) -> float:
    eps = 1e-9
    return float(-np.mean(y * np.log(h + eps) + (1 - y) * np.log(1 - h + eps)))


def treinar(X: np.ndarray, y: np.ndarray, alpha: float = 0.1, epochs: int = 1000, verbose: bool = True):
    """Treina regressão logística (cross-entropy) via GD vetorizado.

    Retorna theta (3,), histórico de losses.
    """
    n_samples = X.shape[0]
    theta = np.zeros(X.shape[1])  # (3,)
    losses = []
    for epoch in range(epochs):
        z = X @ theta  # (n,)
        h = sigmoid(z)
        grad = (X.T @ (h - y)) / n_samples
        theta -= alpha * grad
        if (epoch % max(1, epochs // 20) == 0) or epoch == epochs - 1:
            l = loss_cross_entropy(h, y)
            losses.append(l)
            if verbose:
                print(f"Epoch {epoch:5d} | Loss {l:.4f}")
    return theta, losses


def avaliar(X: np.ndarray, y: np.ndarray, theta: np.ndarray) -> float:
    probs = sigmoid(X @ theta)
    preds = (probs >= 0.5).astype(int)
    return float(np.mean(preds == y))


def main():
    X, y, x1, x2 = gerar_dados(n=100, seed=42)
    theta, losses = treinar(X, y, alpha=0.2, epochs=2000, verbose=True)
    acc = avaliar(X, y, theta)
    print(f"Acurácia final: {acc*100:.2f}%")

    plt.figure(figsize=(6, 5))
    plot_fronteira(theta, x1, x2, titulo="Regressão Logística - Fronteira")
    out_file = "decision_boundary.png"
    plt.tight_layout()
    plt.savefig(out_file, dpi=120)
    # Tenta mostrar se houver display
    print(f"Figura salva em: {out_file}")

if __name__ == "__main__":
    main()
