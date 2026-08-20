def subs_menor(notas):
    menor = notas[0]
    posi = 0
    for i in range(len(notas)):
        if notas[i] < menor:
            menor = notas[i]
            posi = i
    
    notas[posi] = 5

provas = int(input())
notas = list(map(int, input().split()))

media = sum(notas)/provas

necessario = 4.5 - media

if necessario <= 0:
    print("0")
else:
    aux = 0
    while necessario > 0:
        aux += 1
        subs_menor(notas)
        media = sum(notas)/provas

        necessario = 4.5 - media
    
    print(aux)