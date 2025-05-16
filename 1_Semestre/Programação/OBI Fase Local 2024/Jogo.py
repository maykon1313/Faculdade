N, jogadas = map(int, input().split())

matriz_velha = []
matriz = []
matriz_nova = []
for _ in range(N):
    matriz_velha.append(input())


for n in range(N):
    matriz.append([])
    matriz_nova.append([])
    for p in range(N):
        matriz[n].append(int(matriz_velha[n][p]))
        matriz_nova[n].append(int(matriz_velha[n][p]))

def viva_redor(i, j, a, estado):
    aux_i = i
    aux_j = j
    if i > 0:
        i -= 1
    contador = 0
    while i < N and abs(aux_i-i) < 2:
        j = aux_j
        if j > 0:
            j -= 1
        while j < N and abs(aux_j-j) < 2: 
            if a[i][j] == 1 and (aux_i != i or aux_j != j):
                contador += 1
            j += 1
        i += 1


    if estado == 0 and contador == 3:
        return 1
    elif estado == 0 and contador != 3:
        return 0
    elif estado == 1 and contador == 2 or contador == 3:
        return 1
    elif estado == 1 and contador < 2:
        return 0
    elif estado == 1 and contador > 3:
        return 0



for _ in range(jogadas):
    for i in range(N):
        for j in range(N):
            matriz_nova[i][j] = viva_redor(i, j, matriz, matriz[i][j])
    for n in range(N):
        for p in range(N):
            matriz[n][p] = matriz_nova[n][p]

resu = ""
for linhas in range(N):
    for num in range(N):
        if num == 0:
            resu = str(matriz[linhas][0]) + " "
        else:
            resu = resu + str(matriz[linhas][num]) + " " 
    print(resu)

