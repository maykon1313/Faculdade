#Diferente da prova
frase = input()
i = 0
nao_deu = False

while i < len(frase):
    if frase[i] != frase[len(frase) - 1 - i]:
        nao_deu = True
    i = i + 1

if nao_deu == False:
    print("A frase é um palíndromo.")
else:
    print("A frase não é um palíndromo.")