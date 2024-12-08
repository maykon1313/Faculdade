N, K = map(int, input().split())
matriz = []

for i in range(N):
    linha = input()
    matriz.append([int(num) for num in linha])

print(matriz)