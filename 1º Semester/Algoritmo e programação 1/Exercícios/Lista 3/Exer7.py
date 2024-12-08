n = int(input())
numeros = 0
i = 0
soma_pares = 0
soma_impares = 0

while i < n:
    numeros = int(input())
    if numeros%2 == 0:
        soma_pares = numeros + soma_pares
    else:
        soma_impares = numeros + soma_impares
    i = i + 1

print("A soma dos pares é " + str(soma_pares) + " e a soma dos ímpares é " +  str(soma_impares) + ".")