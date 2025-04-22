#a)Index:
entrada = input().split()
resposta = entrada[0]

def procurar_antes(num, i, entrada):
    j = 0
    while j < i:
        if entrada[j] == num:
            return False #Repetido
        j += 1
    return True #Número não repetido

i = 1
while i < len(entrada):
    num = entrada[i]
    if procurar_antes(num, i, entrada):
        resposta = resposta + " " + num
    i += 1

print(resposta)

#b)Vetor novo:
entrada = input().split()
resposta = entrada[0]
repetido = [entrada[0]]

i = 1
while i < len(entrada):
    num = entrada[i]
    if num not in repetido:
        repetido.append(num)
        resposta = resposta + " " + num
    i += 1

print(resposta)

#c)Dicionário:
entrada = input().split()
dic = {}

j = 0
while j < len(entrada):
    num = entrada[j]
    dic[num] = 0
    j += 1

chaves = list(dic.keys())
resposta = chaves[0]

i = 1
while i < len(chaves):
    num = chaves[i]
    resposta = resposta + " " + num
    i += 1

print(resposta)