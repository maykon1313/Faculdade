resposta = input().split()
alunos = int(input())

while alunos > 0:
    gab = input().split()
    nota = 0
    i = 0
    while i < 6:
        if gab[i] == resposta[i]:
            nota = nota + 1
        i = i + 1
    alunos -= 1
    print(nota)