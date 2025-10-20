import numpy as np
import matplotlib.pyplot as plt

n = 100
start = 0
end   = 10
x = np.ones((n,2))

# preenche a coluna 1 com valores entre 0 e 1
x[:,1] = np.arange(start,end,(end-start)/n)

# vetor de pesos    b   a  = theta_0 e theta_1
theta = np.matrix([1.0,1.0])

#shuffle
sindex = np.arange(x.shape[0])
np.random.shuffle(sindex)
#x=x[sindex]


# atributo classe
y = theta@x.T + np.random.randn(n).T
plt.scatter(x[:,1],y.tolist())

# teste com theta arbitrário
theta_hat = np.matrix([30,-10])
y_hat = theta_hat@x.T

plt.scatter(x[:,1], y.tolist())
plt.scatter(x[:,1], y_hat.tolist())

y[0,0]

alpha = 0.1
theta_hat = np.matrix([30.0,-2.0])

x[0,0]

x.shape

# x[linha,coluna] = x[i,j]
x[3,0]

i=10
#theta_hat[0,0] * x[i,0] + theta[0,1] * x[i,1]

theta_xt = theta_hat[0,0] * x[i,0] + theta[0,1] * x[i,1]

y[0,0]

y[0,i]

#theta_xt - y[0,i]

j=0

#alpha*2*(theta_xt - y[0,i])*x[i,j]

theta_hat[0,j]

alpha = 0.001
theta_hat = np.array([20.0,-1.0])
vloss_estocastico = []
stochasticv1 = []
for epoch in range(2000):
    for i in range(x.shape[0]):
        #theta_hat = theta.copy()
        for j in range(x.shape[1]):
            loss = np.power(y[0,i] - theta_hat@x[i].T,2)
            vloss_estocastico.append(loss)
            theta_hat[j] = theta_hat[j] - alpha*2*(theta_hat@x[i] - y[0,i])*x[i,j]
        #theta = theta_hat.copy()
        stochasticv1.append(theta_hat.tolist().copy())
print(theta_hat)
y_hat = theta_hat@x.T
plt.scatter(x[:,1], y.tolist())
plt.scatter(x[:,1], y_hat.tolist())

plt.plot(range(len(vloss_estocastico)),vloss_estocastico)

#theta_hat

x.T

theta_hat = np.array([20.0,-1.0])

#theta_hat

y.shape

#(theta_hat@x.T - y)@x/100

#(theta_hat@x.T - y)*x

alpha = 0.01
theta_hat = np.array([20.0,-1.0])
vloss_lote = []
vlote = []
n = x.shape[0]
for epoch in range(2000):
        theta_hat = theta_hat - alpha*2*(theta_hat@x.T - y)*x/n
        loss = np.power(y- theta_hat@x.T,2)
        vloss_lote.append([epoch,np.mean(loss)])
        vlote.append(theta_hat.tolist().copy())
        #print(theta_hat)

print(theta_hat)
y_hat = theta_hat@x.T
plt.scatter(x[:,1], y.tolist())
plt.scatter(x[:,1], y_hat.tolist())
vloss = np.matrix(vloss_lote)

plt.plot(vloss[:1000],vloss[:,1][:1000])

alpha = 0.01
theta_hat = np.matrix([20.0,-1.0])
mbatch = []
mini_batch_size = int(n/10)
print(y.shape)
for epoch in range(2000):
    for i in range(0,n,mini_batch_size):
        x_mini_batch = x[i:(i+mini_batch_size)]
        y_mini_batch = y[0,i:(i+mini_batch_size)]
        #theta_hat = theta_hat - alpha*2*(theta_hat@x.T - y)*x/n
        theta_hat = theta_hat - ((alpha*(theta_hat@x_mini_batch.T - y_mini_batch))@x_mini_batch)/mini_batch_size
        mbatch.append(theta_hat.tolist().copy())
print(theta_hat)
y_hat = theta_hat@x.T
plt.scatter(x[:,1], y.tolist())
plt.scatter(x[:,1], y_hat.tolist())

mbatch = np.array(mbatch)
batch = np.array(vlote)
stochasticv1 = np.array(stochasticv1)


fig,ax = plt.subplots(1,3,figsize=(15,4))
ax[0].plot(mbatch[:,0,0],mbatch[:,0,1],label='mini_batch')
ax[0].set_title('mini_batch')

ax[1].plot(batch[:,0,0],batch[:,0,1],label='batch')
ax[1].set_title('batch')

ax[2].plot(stochasticv1[:,0],stochasticv1[:,1],label='stochastic')
ax[2].set_title('stochasticv1')

