V, E = map(int, input().split())

matriz = [[0 for q in range(V+1)] for _ in range(V+1)]

for i in range(E):
    a, b = map(int, input().split())
    matriz[a][b] = 1
    matriz[b][a] = 1

caminhos = int(input())
contador = 0


for j in range(caminhos):
    deu = True
    caminho = list(map(int, input().split()))
    z = 1
    while z < (len(caminho) - 1):
        if matriz[caminho[z]][caminho[z+1]] != 1:
            deu = False
            break
        z += 1
    if deu:
        contador += 1

print(contador)