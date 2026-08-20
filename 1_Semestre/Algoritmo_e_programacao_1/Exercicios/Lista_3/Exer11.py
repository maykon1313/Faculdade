n = 7
numeros = 0
i = 0
maior = 0

while i < n:
    numeros = int(input())
    if int(maior) < numeros:
        maior = numeros
        dia = i+1
    i = i + 1

print("O dia que houve a maior venda foi o " + str(dia) + "º dia e a quantidade de venda foi de " + str(maior) + " unidades.")