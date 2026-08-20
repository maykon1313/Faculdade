import torch

def exemplo1():
    x = torch.randn(3, requires_grad = True)

    y = x + 2
    z = y * y * 2

    print(x)
    print(y)

    #z = z.mean()

    print(z)

    v = torch.tensor([0.1, 1.0, 0.001], dtype=torch.float32)

    z.backward(v) # dz/dx
    print(x.grad)

    # Esse código mostra como calcular derivadas automaticamente usando PyTorch.
    # Ele faz algumas operações matemáticas com um vetor aleatório, 
    # calcula a média do resultado, 
    # e depois mostra como cada valor de entrada (x) influencia
    # o resultado final (z) usando o gradiente.
    # O vetor v serve como ponderador dos valores do gradiente de z em ralação a x.

####################################################################

def exemplo2():
    x = torch.randn(3, requires_grad = True)
    print(x)

    def _opecao1(x):
        x.requires_grad_(False)
        return x

    def _opecao2(x):
        y = x.detach()
        return y
    
    def _opecao3(x):
        with torch.no_grad():
            #y = x + 2
            y = x
            return y

    print(_opecao1(x))
    print(_opecao2(x))
    print(_opecao3(x))

####################################################################

####################################################################

####################################################################

####################################################################

####################################################################

####################################################################

####################################################################

####################################################################

exemplo1()
exemplo2()
