#Calculadora de polinomio
grau = int(input())
num = []
i = 0
j = 0
k_xizes = int(input())

while i <= grau:
    num.append(int(input()))
    i = i + 1

while j < k_xizes:
    xis = int(input())
    z = 0
    soma = 0
    while z <= grau:
        soma = soma + (num[z] * (xis**(z)))
        z = z + 1
    print(soma)
    j = j + 1