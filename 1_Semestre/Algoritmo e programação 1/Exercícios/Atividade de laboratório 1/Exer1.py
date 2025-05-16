print("Digite o nome do aluno:")
nome = str(input())
print("Digite a 1° nota:")
n1 = float(input())
print("Digite a 2° nota:")
n2 = float(input())
print("Digite a 3° nota:")
n3 = float(input())
print("Digite a nota da lista:")
ml = float(input())

media = (n1 + 2*n2 + 2*n3 + 2*ml)/7

if media >= 9:
    print("O aluno " + nome + " foi aprovado com o conceito A.")
elif 7.5 <= media:
    print("O aluno " + nome + " foi aprovado com o conceito B.")
elif 6 <= media:
    print("O aluno " + nome + " foi aprovado com o conceito C.")
elif 4 <= media:
    print("O aluno " + nome + " foi reprovado com o conceito D.")
else:
    print("O aluno " + nome + " foi reprovado com o conceito E.")

print("E a média foi: " + str(round(media, 2)))