N, K = map(int, input().split())

notas = list(map(int, input().split()))

def aprovador(maior, notas):
    contador = 0
    for i in range(N):
        if maior <= notas[i]:
            contador += 1
    return contador

notas.sort()

aprovados = 1
x = N-1
maior = notas[x]

while aprovados < K:
    maior = notas[x]
    x = x - 1
    aprovados = aprovador(maior, notas)

print(maior)