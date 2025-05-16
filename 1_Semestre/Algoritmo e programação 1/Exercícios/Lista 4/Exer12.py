#-5 -1 0 2 3 5
#a)Vetor novo:
numeros = input().split()
repete = []

def n_presente(num,repete):
    j = 0
    while j < len(repete):
        if num == repete[j]:
            return False
        j += 1
    return True

i = 0
while i < len(numeros):
    num = numeros[i]
    if n_presente(num, repete):
        z = 0
        contador = 0
        while z < len(numeros):
            if numeros[z] == num:
                contador += 1
            z += 1
        if contador != 1:
            print("O número " + str(num) + " apareceu " + str(contador) + " vezes.")
        else:
            print("O número " + str(num) + " apareceu " + str(contador) + " vez.")
        repete.append(num)
    i += 1

#b)Index:
numeros = input().split()

def n_antes(i, num, numeros):
    j = 0
    while j < i:
        if num == numeros[j]:
            return False
    return True



i = 0
while i < len(numeros):
    num = numeros[i]
    if n_antes(i, num, numeros):
        z = 0
        contador = 0
        while z < len(numeros):
            if numeros[z] == num:
                contador += 1
            z += 1
        if contador != 1:
            print("O número " + str(num) + " apareceu " + str(contador) + " vezes.")
        else:
            print("O número " + str(num) + " apareceu " + str(contador) + " vez.")
    i += 1


#c)Dicionário:
numeros = input().split()
dic = {}

i = 0
while i < len(numeros):
    num = numeros[i]
    dic[num] = 0
    i += 1

j = 0
while j < len(numeros):
    dic[numeros[j]] += 1
    j += 1

chaves = dic.keys()

z = 0
while z < len(dic):
    chave = chaves[z]