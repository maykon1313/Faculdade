posicoes = int(input())
vetor = input().split()

menor = vetor[0]
i = 1
while i < posicoes:
    if int(vetor[i]) < int(menor):
        menor = vetor[i]
        posicao = i
    i += 1

print("Menor valor: " + str(menor))
print("Posicao: " + str(posicao))