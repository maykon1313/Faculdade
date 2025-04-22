n = int(input())
alunos = 0
i = 0
maior = 0
menor = 0

while i < n:
    alunos = int(input())
    if i == 0:
        maior = alunos
        menor = alunos
    elif int(maior) < alunos:
        maior = alunos
    elif (int(menor) > alunos):
        menor = alunos
    i = i + 1

print("A maior nota da turma foi " + str(maior) + " e a menor foi " + str(menor) + ".")