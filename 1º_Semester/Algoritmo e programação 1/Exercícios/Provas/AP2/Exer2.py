print("Digite a 1° nota:")
n1 = float(input())
print("Digite a 2° nota:")
n2 = float(input())
print("Digite a 3° nota:")
n3 = float(input())
print("Digite a 4° nota:")
n4 = float(input())

media = (n1*2 + n2*4 + n3*3 + n4*1)/10

print("A media foi de " + str(media))

if media >= 7:
    print("Aluno aprovado.")
elif media < 5:
    print("Aluno reprovado.")
else:
    print("Aluno em exame.")
    print("Digite a nota da prova de exame:")
    ne = float(input())
    media = (media + ne)/2
    if media >= 5:
        print("Aluno aprovado.")
    else:
        print("Aluno reprovado.")
    print("A nova média foi de " + str(media))