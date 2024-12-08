estudantes = int(input())
medias = ""
alunos = estudantes
aprovados = 0
reprovados = 0
notas_sala = 0

while estudantes > 0:
    nota1 = int(input())
    nota2 = int(input())
    nota3 = int(input())
    media = (nota1 + nota2 + nota3)/3
    medias = medias + str(media) + " "
    notas_sala = notas_sala + nota1 + nota2 + nota3
    if media >= 5:
        aprovados = aprovados + 1
    else:
        reprovados = reprovados + 1
    estudantes = estudantes - 1

medias_finais = notas_sala/(alunos*3)

print("Média de cada aluno: " + str(medias) + ".")
print("Média da turma: " + str(medias_finais) + ".")
print("Aprovados: " + str(aprovados) + ".")
print("Reprovados: " + str(reprovados) + ".")