import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn.linear_model import Perceptron
from sklearn.neural_network import MLPClassifier

# --- Dados XOR ---
X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([0, 1, 1, 0]) # 0=Vermelho, 1=Azul

def plot_boundary_with_jitter(model, X, y, title, is_transformed=False, manual_weights=None, manual_line=None):
    x_min, x_max = -0.5, 2.5
    y_min, y_max = -0.5, 2.5
    h = .02
    
    # Se tivermos um modelo treinado (casos 1 e 2)
    if model:
        xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
        if manual_weights:
            model.coef_ = np.array([manual_weights[0]])
            model.intercept_ = np.array([manual_weights[1]])
        Z = model.predict(np.c_[xx.ravel(), yy.ravel()])
        Z = Z.reshape(xx.shape)
        plt.contourf(xx, yy, Z, cmap=plt.cm.RdBu, alpha=0.5)

    # Adiciona tremor (jitter) para visualizar pontos sobrepostos
    X_visual = X.copy()
    # Pequeno ajuste visual para separar pontos que caem na mesma coordenada
    if is_transformed: 
        # No caso NAND/OR, os pontos (0,1) e (1,0) caem ambos em (1,1). Vamos separá-los visualmente.
        X_visual[1, 0] -= 0.05 
        X_visual[2, 0] += 0.05 

    # Plota os pontos
    plt.scatter(X_visual[:, 0], X_visual[:, 1], c=y, cmap=ListedColormap(['#FF0000', '#0000FF']), edgecolors='k', s=100)
    
    # Se tivermos uma reta manual para desenhar (caso 3)
    if manual_line:
        plt.plot(manual_line[0], manual_line[1], 'k--', linewidth=2, label="Separador Linear")
        plt.legend()

    plt.title(title, fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.3)
    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

plt.figure(figsize=(16, 5))

# --- 1. Perceptron (Erro Clássico) ---
plt.subplot(1, 3, 1)
clf_p = Perceptron()
clf_p.fit(X, y)
plot_boundary_with_jitter(clf_p, X, y, "1. Perceptron (Espaço Original)\n(Impossível separar com uma reta)", manual_weights=([1, 1], -0.9))

# --- 2. MLP (Solução Não-Linear) ---
plt.subplot(1, 3, 2)
clf_mlp = MLPClassifier(hidden_layer_sizes=(10,), activation='tanh', solver='lbfgs', random_state=42)
clf_mlp.fit(X, y)
plot_boundary_with_jitter(clf_mlp, X, y, "2. MLP (Espaço Original)\n(Fronteira complexa isola os azuis)")

# --- 3. Espaço Transformado (NAND e OR) - O CORRETO ---
plt.subplot(1, 3, 3)
# Simulação manual de dois neurônios na camada oculta:
# Neurônio 1: Comporta-se como NAND (Só é 0 se x1=1 e x2=1)
# Neurônio 2: Comporta-se como OR (Só é 0 se x1=0 e x2=0)
X_trans = []
for x1, x2 in X:
    feat_nand = 0 if (x1==1 and x2==1) else 1
    feat_or   = 0 if (x1==0 and x2==0) else 1
    X_trans.append([feat_nand, feat_or])
X_trans = np.array(X_trans)

# A reta diagonal corta o canto superior direito
plot_boundary_with_jitter(None, X_trans, y, "3. MLP (Espaço Transformado NAND/OR)\n(Agora é Linearmente Separável!)", is_transformed=True, manual_line=([0, 2.0], [1.5, -0.5]))

plt.tight_layout()
plt.show()