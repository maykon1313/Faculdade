n = int(input())

def fatorial(n):
    i = 1
    soma_tudo = 1
    while i < n+1:
        soma_tudo = soma_tudo * i
        i = i + 1
    return soma_tudo

print("O fatorial de " + str(n) + " resultou em " + str(fatorial(n)) + ".")