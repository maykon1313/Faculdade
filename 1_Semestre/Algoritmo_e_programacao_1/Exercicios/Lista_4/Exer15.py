entrada1 = input().split()
entrada2 = input().split()

def int_dela(entrada):
    q = 0
    while q < len(entrada):
        entrada[q] = int(entrada[q])
        q += 1
    return entrada

entrada1 = int_dela(entrada1)
entrada2 = int_dela(entrada2)

def procurar_no_vetor(num, vetor):
    p = 0
    while p < len(vetor):
        if num == vetor[p]:
            return True
        p +=1
    return False

def interseccao(entrada, outra_entrada):
    interseccao = []
    i = 0
    while i < len(entrada):
        num = entrada[i]
        j = 0
        while j < len(outra_entrada) and (not procurar_no_vetor(num, interseccao)):
            if num == outra_entrada[j]:
                interseccao.append(num)
            j += 1
        i += 1
    return interseccao

if len(entrada1) > len(entrada2):
    interseccao = interseccao(entrada1, entrada2)
else:
    interseccao = interseccao(entrada2, entrada1)

#SELECTION SORT:
repetido = []

def menor(interseccao, repetido):
    e = 0
    while procurar_no_vetor(interseccao[e], repetido):
        e += 1
    
    menor = interseccao[e]
    t = 0
    while t < len(interseccao):
        if interseccao[t] < menor and (not procurar_no_vetor(interseccao[t], repetido)):
            menor = interseccao[t]
        t += 1
    return menor

resu = ""
w = 0
while w < len(interseccao):
    menorzinho = menor(interseccao, repetido)
    repetido.append(menorzinho)
    if w == 0:
        resu = str(menorzinho)
    else:
        resu = resu + " " + str(menorzinho)
    w += 1

print(resu)