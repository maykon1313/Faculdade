sequencia = int(input())
resposta = ""

while sequencia > 0:
    entrada = 1
    soma = 0
    while entrada != 0:
        entrada = int(input())
        if entrada%2 == 0:
            soma = soma + entrada
    resposta = resposta + str(soma) + " "
    sequencia = sequencia - 1

print(resposta)