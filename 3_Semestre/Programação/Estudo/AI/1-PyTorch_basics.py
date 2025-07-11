# All test were made using only the CPU

import torch
import numpy as np

def exemplo1():
    print("Exemplo 1:")
    # Exemplos de criação de tensores
    x = torch.empty(3, 3, 3)
    print("empty:", x)
    x = torch.rand(3, 3, 3)
    print("rand:", x)
    x = torch.zeros(3, 3, 3)
    print("zeros:", x)
    x = torch.ones(3, 3, 3)
    print("ones:", x)

####################################################################

def exemplo2():
    print("Exemplo 2:")
    # Exemplos de tipos e tamanhos
    x = torch.ones(3, 3, dtype=torch.int)
    print("int:", x)
    x = torch.ones(3, 3, dtype=torch.double)
    print("double:", x)
    x = torch.ones(3, 3, dtype=torch.float16)
    print("float16:", x)
    print("dtype:", x.dtype)
    print("size:", x.size())

####################################################################

def exemplo3():
    print("Exemplo 3:")
    # Tensor a partir de lista
    x = torch.tensor([12.2, 13.5])
    print(x)
    print(x.dtype)
    print(x.size())

####################################################################

def exemplo4():
    print("Exemplo 4:")
    # Operações aritméticas
    x = torch.rand(2, 2, dtype=torch.double)
    y = torch.rand(2, 2, dtype=torch.double)
    print("x:", x)
    print("y:", y)
    print("add:", x + y)
    print("sub:", x - y)
    print("mul:", x * y)
    print("div:", x / y)

####################################################################

def exemplo5():
    print("Exemplo 5:")
    # Indexação
    x = torch.rand(5, 3)
    print("x:", x)
    print("x[0, :]:", x[0, :])
    print("x[:, 0]:", x[:, 0])
    print("x[1, 1].item():", x[1, 1].item())

####################################################################

def exemplo6():
    print("Exemplo 6:")
    # Mudança de shape
    x = torch.rand(4, 4)
    print("x:", x)
    y = x.view(2, 8)
    print("view(2,8):", y)
    y = x.view(-1, 8)
    print("view(-1,8):", y)
    y = x.view(-1, 2)
    print("view(-1,2):", y)
    print("y.size():", y.size())

####################################################################

def exemplo7():
    print("Exemplo 7:")
    # Interoperabilidade com numpy
    a = torch.ones(5, dtype=torch.int)
    b = a.numpy()
    print("torch -> numpy:", b)
    a.add_(1)
    print("a após add_:", a)
    print("b após add_:", b)
    a = np.ones(5)
    b = torch.from_numpy(a)
    print("numpy -> torch:", b)
    a += 1
    print("a após +=1:", a)
    print("b após +=1:", b)

    # Cópia para não compartilhar memória
    a = torch.ones(5, dtype=torch.int)
    b = a.numpy().copy()
    print("torch -> numpy (copy):", b)
    a.add_(1)
    print("a após add_:", a)
    print("b após add_:", b)
    a = np.ones(5)
    b = torch.from_numpy(a.copy())
    print("numpy -> torch (copy):", b)
    a += 1
    print("a após +=1:", a)
    print("b após +=1:", b)

####################################################################

def exemplo8():
    print("Exemplo 8:")
    # Exemplo para GPU
    if torch.cuda.is_available():
        device = torch.device('cuda')
        x = torch.ones(5, device=device)
        y = torch.ones(5)
        y = y.to(device)
        z = x * y
        print("z (cuda):", z)
        z = z.to('cpu')
        print("z (cpu):", z)
        print("z.pin_memory():", z.pin_memory())
    else:
        print("CUDA is not available. Running on CPU only.")

####################################################################

exemplo1()
exemplo2()
exemplo3()
exemplo4()
exemplo5()
exemplo6()
exemplo7()
exemplo8()
