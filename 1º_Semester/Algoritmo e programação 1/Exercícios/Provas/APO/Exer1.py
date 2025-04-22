gabarito = input().split()
alunos = int(input())

i = 0
while i < alunos:
    marcacoes = input().split()
    j = 0
    acertos = 0
    while j < len(marcacoes):
        if gabarito[j] == marcacoes[j]:
            acertos += 1
        j += 1
    i += 1
    print(acertos)