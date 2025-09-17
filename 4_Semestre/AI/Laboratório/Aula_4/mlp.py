import pickle, gzip, math, torch, matplotlib as mpl
import matplotlib.pyplot as plt
from torch import tensor
import numpy as np
import pandas as pd

def near(a,b): return torch.allclose(a, b, rtol=1e-3, atol=1e-5)

# !pwd  # Linha específica do Colab, pode ser removida/comentada

pd_train = pd.read_csv('sample_data/mnist_train_small.csv')
pd_valid = pd.read_csv('sample_data/mnist_test.csv')

# pd_train  # Apenas exibe o DataFrame no Colab, pode ser removida/comentada

x=pd_train.to_numpy()
ytrain=x[:,0]
xtrain=x[:,1:]

x=pd_valid.to_numpy()
yvalid=x[:,0]
xvalid=x[:,1:]

# xvalid.shape  # Apenas exibe a forma, pode ser removida/comentada



# ytrain  # Apenas exibe o vetor no Colab, pode ser removida/comentada

# xtrain.shape  # Apenas exibe a forma, pode ser removida/comentada

# m = xtrain[0].reshape((28,28))  # Apenas exibe matriz no Colab
# for linha in m:
#     print(linha)

for i in range(10):
    img = xtrain[i].reshape((28,28))
    plt.imshow(img,cmap='Greys')
    plt.title(ytrain[i])
    plt.show()
# O bloco acima exibe imagens, pode ser mantido se desejar visualizar localmente

def normalize(x,mean,stddev): return (x-mean)/stddev

print(xtrain.mean(), xtrain.std())

xtrain_norm = normalize(xtrain,xtrain.mean(),xtrain.std())
xvalid_norm   = normalize(xvalid,xvalid.mean(),xvalid.std())

print(xtrain.mean(),xtrain.std(),xtrain_norm.mean(),xtrain_norm.std())

# O bloco acima exibe imagens normalizadas, pode ser mantido se desejar visualizar localmente

"""# Estrutura básica

## Função linear
"""
# Comentário de markdown do Colab, pode ser removido ou mantido como comentário comum

print(xtrain_norm.shape,xtrain_norm.mean(),xtrain_norm.std())

# xtrain.shape  # Apenas exibe a forma, pode ser removida/comentada

#numero neuronios
num_n = 50
n,m = xtrain.shape

# Inicializando com Xavier
w1 = np.random.randn(m,num_n)/np.sqrt(m)
w2 = np.random.randn(num_n,1)/np.sqrt(num_n)

def lin(x,w): return x@w

res = lin(xvalid_norm,w1)

# res.mean(),res.std()  # Apenas exibe valores, pode ser removida/comentada

def relu(x): return np.maximum(x,0) -0.6

def reglog(x): return 1/(1+np.exp(-x))

res = relu(lin(xvalid_norm,w1))

# res.mean(),res.std()  # Apenas exibe valores, pode ser removida/comentada

# Inicializando com Kaiming

w1 = np.random.randn(m,num_n)*np.sqrt(2/m)

res = relu(lin(xtrain_norm,w1))



# res.mean(),res.std()  # Apenas exibe valores, pode ser removida/comentada

res = reglog(lin(xvalid_norm,w1))

def model(x):
    l1 = lin(x,w1) # x@w1
    l2 = reglog(l1)
    l3 = lin(l2,w2)
    return l3

r = model(xtrain_norm)

# %timeit -n 10 _ = model(xtrain_norm)  # Linha mágica do Colab, pode ser removida/comentada



"""## Definindo a Loss"""

def mse(x,y): return np.mean(np.power(x.squeeze(-1)-y,2))

pred = model(xtrain_norm)

# pred.shape  # Apenas exibe a forma, pode ser removida/comentada

ytrain = ytrain.astype(float)

ytrain.shape

# pred.squeeze(-1).shape  # Apenas exibe a forma, pode ser removida/comentada

x  = np.array([1,1])
y  = np.array([3,4])
print(x-y)

# pred.shape  # Apenas exibe a forma, pode ser removida/comentada

r = mse(pred,ytrain)

# r  # Apenas exibe o valor, pode ser removida/comentada

"""##Calculando os gradientes

### Forward

$MLP(x) = sigma(xtimes w_1) times w_2$

onde $sigma(z) = frac{1}{1+e^{-z}}$ é a função de ativação logística


Ao aplicamos a MSE como função loss obtemos

$Loss(x,y) = (sigma(xtimes w_1) times w_2 - y)^2$

Assim temos

$f_1 = xtimes w_1$

$f_2 = sigma(f_1)$

$f_3 = f_2 times w_2$

$f_4 = f_3 - y$

$f_5 = f_4^2$

Observe que $f_3$ é equivalente a $MLP(x)$

### Backward

Calculando as derivadas

$frac{partial f_1}{partial  w_1} = x$

$frac{partial f_2}{partial f_1} = sigma(f_1) times (1-sigma(f_1)) = f_2(1-f_2)$

$frac{partial f_3}{partial f_2} = w_2$


$frac{partial f_3}{partial w_2} = f_2$


$frac{partial f_4}{partial f_3} = 1$


$frac{partial f_5}{partial f_4} = 2 f_4$

Assim


$frac{partial Loss}{partial w_2} = frac{partial f_5}{partial f_4} frac{partial f_4}{partial f_3} frac{partial f_3}{partial w_2} =  2 f_4 times 1times f_2$

$frac{partial Loss}{partial w_1} = frac{partial f_5}{partial f_4} frac{partial f_4}{partial f_3} frac{partial f_3}{partial f_2} frac{partial f_2}{partial f_1} frac{partial f_1}{partial w_1}= 2 f_4 times 1times w_2 times f_2(1-f_2) times x$
"""

#Exercício
#Implementar a MLP
def train1(x, y):
    #numero neuronios
    num_n = 50
    n,m = x.shape
    # Inicializando com Kaiming
    w1 = np.random.randn(m,num_n)*np.sqrt(2/m)
    w2 = np.random.randn(num_n,1)*np.sqrt(2/num_n)
    alpha = 0.001
    y=y.reshape(-1,1)
    for epoch in range(10000):
        f1 = x@w1                  #(100, 50)
        f2 = 1/(1+np.exp(-f1))     #(100, 50)
        f3 = f2@w2                 #(100, 1)
        f4 = f3 - y                #(100, 1)
        f5 = np.square(f4).sum()   # scalar
        #print(f1.shape,f2.shape,f3.shape,f4.shape,f5.shape)
        #(100, 50) (100, 50) (100, 1) (100, 1)

        if epoch%100==0: print(epoch,f5)

        # gradiente mse (100,1)
        df5 = 2.0*(f4)

        df4 = df5

        # gradiente w2 (50,100)x(100,1) = (50,1)
        g_w2     = f2.T.dot(df4)

        #          (100,1) (1,50) = (100,50)
        df3      = df4.dot(w2.T)

        # gradiente da sigmoid (100,50)*(100,50)*(1-(100,50)) = (100,50)
        df2      = df3*f2*(1-f2)

        # gradiente w1 (784,100)x(100,50) = (784,50)
        g_w1     = x.T.dot(df2)

        # atualizacao de pesos
        w1 = w1 - alpha*g_w1
        w2 = w2 - alpha*g_w2
    return (w1,w2)

"""
Assim colocando código temos que

g_w2 = $frac{dLoss}{dw_2}$  

g_w1 = $frac{dLoss}{dw_1}$

Que representam os gradientes para a atualização"""

r=train1(xtrain_norm[:100], ytrain[:100])

# O bloco acima exibe imagens, pode ser mantido se desejar visualizar localmente

(wr1,wr2)=r

print(reglog(xvalid_norm[:10]@wr1)@wr2)

# Mesmo código mas com representação mais compacta

def train(x, y):
    #numero neuronios
    num_n = 50
    n,m = x.shape
    # Inicializando com Kaiming
    w1 = np.random.randn(m,num_n)*np.sqrt(2/m)
    w2 = np.random.randn(num_n,1)*np.sqrt(2/num_n)
    alpha = 0.001

    print(type(x))
    y=y.reshape(-1,1)
    for epoch in range(100000):
        h = 1/(1+np.exp(-x.dot(w1)))
        y_pred = h.dot(w2)
        loss   = np.square(y_pred - y).sum()
        if epoch%1000==0: print(epoch,loss)
        g_y_pred = 2.0*(y_pred -y)
        g_w2     = h.T.dot(g_y_pred)
        g_h      = g_y_pred.dot(w2.T)
        g_w1     = x.T.dot(g_h*h*(1-h))
        w1 -= alpha*g_w1
        w2 -= alpha*g_w2

