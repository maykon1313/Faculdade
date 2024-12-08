def em_ordem_crescente(vetor):
    for i in range(numero_de_numeros - 1):
        if vetor[i] > vetor[i + 1]:
            return False
    return True
 
def soma_alternada_veri():
    for i in range(numero_de_numeros-3):
        vetor[i+2] = vetor[i+2] - (vetor[i+1] - vetor[i])
        vetor[i+1] = vetor[i]
    if vetor[numero_de_numeros-1] < vetor[numero_de_numeros-2]:
        return True #sinal invertido, true = não é possível
    else:
        return False
 
perguntas = int(input())
 
for x in range(perguntas):
    numero_de_numeros = int(input())
    vetor = list(map(int, input().split()))
    if em_ordem_crescente(vetor):
        print("YES")
    elif numero_de_numeros%2 == 0 and soma_alternada_veri():
        print("NO")
    else:
        print("YES")