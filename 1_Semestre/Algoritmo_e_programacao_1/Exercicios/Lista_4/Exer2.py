n = int(input())
dias = []
soma = 0
i = n
j = 0

while i > 0:
    temperatura = int(input())
    dias.append(temperatura)
    soma = soma + temperatura
    i = i - 1

media =  soma/n

while j < n:
    if dias[j] > media:
        print("Dia " + str(j+1))
    j = j + 1