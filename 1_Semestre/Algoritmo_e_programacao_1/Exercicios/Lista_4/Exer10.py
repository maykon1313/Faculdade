entrada = input().split()
primeiro = True

def procurar_antes(num, i, entrada):
    j = 0
    while j < i:
        if entrada[j] == num:
            return True #Repetido
        j += 1
    return False #Número não repetido

i = 1
while i < len(entrada):
    num = entrada[i]
    if procurar_antes(num, i, entrada):
        if primeiro:
            resposta = str(num)
            primeiro = False
        else:
            resposta = resposta + " " + num
    i += 1

print(resposta)