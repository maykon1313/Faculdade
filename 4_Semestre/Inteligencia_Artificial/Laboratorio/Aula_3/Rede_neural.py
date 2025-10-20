import matplotlib.pyplot as plt
import numpy as np

def exer1():
    x = np.arange(6, 10, 0.1)

    # f(x) = (x-7) * (x-9)
    # f(x) = x**2 - 16*x + 63
    def f(x):
        return x**2 - 16*x + 63

    def df(x):
        return 2*x - 16

    plt.plot(x,f(x))

    x = 10
    alpha = 0.1
    for epoch in range(100):
        x = x - alpha * df(x)
        print(x)

def exer2():
    def f1(x):
        return x**3 - x**2
    def df1(x):
        try:
            return 3*x**2 - 2*x
        except:
            return 0
        
    x = np.arange(0,1.2,0.01)
    plt.plot(x,f1(x))

    x = 2
    alpha = 0.4
    for i in range(100):
        x = x - alpha * df1(x)
        print(x)

def exer3():
    def f1(x):
        return x**3 - x**2
    def df1(x):
        try:
            return 3*x**2 - 2*x
        except:
            return 0
        
    x = np.arange(0,1.2,0.01)
    plt.plot(x,f1(x))

    x = 0.6
    alpha = 0.1
    for i in range(100):
        x = x + alpha * df1(x)
        print(x)

exer1()
exer2()
exer3()