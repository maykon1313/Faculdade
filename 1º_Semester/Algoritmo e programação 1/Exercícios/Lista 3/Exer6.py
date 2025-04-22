n = int(input())
numero = 0
i = 0
soma = 0

while i < n:
    numero = int(input())
    if numero > 0:
        soma = numero + soma
    i = i + 1

print("A soma dos positivos é " + str(soma) + ".")