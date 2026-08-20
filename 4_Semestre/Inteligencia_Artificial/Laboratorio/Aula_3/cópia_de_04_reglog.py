import matplotlib.pyplot as plt
import numpy as np

def g(z):
    return 1/(1+np.exp(-z))

g(1)              # (Colab mostrava o valor; em script use print(g(1)))
g(2)              # (Colab mostrava o valor; em script use print(g(2)))
g(-2)             # (Colab mostrava o valor; em script use print(g(-2)))
g(-1)             # (Colab mostrava o valor; em script use print(g(-1)))
g(6)              # (Colab mostrava o valor; em script use print(g(6)))

x = np.arange(-5,5,0.1)

plt.plot(x,g(x))   # gera o gráfico (saída visual)

# Vamos inicialmente gerar duas nuvens de pontos
n = 100
cov  = [[1,0],[0,1]]

mean = [0,0]
x1= np.random.multivariate_normal(mean,cov,n).T

mean = [2,2]
x2= np.random.multivariate_normal(mean,cov,n).T


x = np.concatenate((x1,x2),axis=1)

x = np.concatenate((np.ones((1,2*n)),x),axis=0)

x = x.T
y = np.concatenate((np.ones(n),np.zeros(n)))

plt.scatter(x1[0],x1[1])
plt.scatter(x2[0],x2[1])

"""# Gradiente Estocástico"""

theta = np.array([[-4.0,2.0,2.0]])

def f_reduzida(theta,x):
  c1 = theta[1]/theta[2]
  c0 = theta[0]/theta[2]
  return -c1*x-c0

def plot_theta(theta):
    print(theta)   # imprime os parâmetros atuais (mostra valor da variável theta)
    xmin = np.min(x)
    xmax = np.max(x)
    tx= np.arange(xmin,xmax,(xmax-xmin)/n)
    ty = f_reduzida(theta[0],tx)
    plt.plot(tx,ty)
    plt.scatter(x1[0],x1[1])
    plt.scatter(x2[0],x2[1])
    plt.show()

plot_theta(theta)

#theta@np.matrix([1,0,0]).T

#y

#x[0]

#theta

#theta@x[0].T

i=0

gx = g(theta@x[i].T)

#gx

i=0
j=0
#(gx-y[i])*gx*(1-gx)*x[i][j]

#theta[0,j]

#x.shape

#alpha = 0.1
#theta[0,j] = theta[0,j] - alpha*2*(gx-y[i])*gx*(1-gx)*x[i][j]

#theta[0,j]

theta = np.array([[-4.0,2.0,-2.0]])
plot_theta(theta)

alpha = 0.5
for epoch in range(200):
    gx = g(theta @ x.T)
    # Calculate the gradient using matrix operations
    gradient = 2 * ((gx - y) * gx * (1 - gx)) @ x / n
    theta = theta - alpha * gradient
    if epoch % 2 == 0:
        plot_theta(theta)

theta.shape       # (Colab mostrava a forma de theta; em script use print(theta.shape))

x.T.shape         # (Colab mostrava a forma de x.T; em script use print(x.T.shape))

(theta@x.T).shape # (Colab mostrava a forma do produto; em script use print((theta@x.T).shape))

(theta@x.T).shape # (Repetido para inspeção no Colab)

g(theta@x.T).shape            # (Forma do vetor de probabilidades; use print(g(theta@x.T).shape))

y.shape          # (Forma do vetor de rótulos; use print(y.shape))

(g(theta@x.T) - y).shape      # (Forma do erro; use print((g(theta@x.T)-y).shape))

gx=g(theta@x.T)  # (Vetor de probabilidades previsto)

n=x.shape[0]     # (Número de amostras; em Colab poderia ser exibido com uma célula isolada)

theta.shape       # (Checando novamente a forma de theta)

#(((gx-y)*gx*(1-gx))@x)/n

#((((gx-y)*(gx)*(1-gx))@x)/n).shape

theta = np.array([[-4.0,0.0,0.0]])

alpha = 0.1
for epoch in range(20):
    gx=g(theta@x.T)
    theta = theta - alpha*2*(((gx-y)*(gx)*(1-gx))@x)/n
    #theta = theta - alpha*2*((gx-y)@x)/n
    if epoch % 2 == 0:
        plot_theta(theta)

