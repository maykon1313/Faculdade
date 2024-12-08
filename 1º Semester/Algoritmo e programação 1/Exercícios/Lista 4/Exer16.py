entrada = input().split()

def uns(contadores):
    numero_anterior = int(entrada[0])
    uns = True
    cheia = True

    if numero_anterior == 1:
        posicao = 1
        while posicao < len(entrada):
            if entrada[posicao] != "1":
                uns = False
            posicao +=1
    else:
        uns = False
    
    todas_diferencas = []
    posicao = 1
    while posicao < len(entrada):
        diferenca = numero_anterior - int(entrada[posicao])
        if diferenca < 0:
            diferenca = -diferenca
        todas_diferencas.append(diferenca)
        if diferenca > (len(entrada)-1):
            cheia = False
        numero_anterior = int(entrada[posicao])
        posicao += 1
    
    return uns, cheia

def cheia_de_diferenca(todas_difencas):
    num = 0
    while num < len(todas_difencas):
        posicao = 0
        tem = False
        while posicao < len(todas_difencas):
            





unszinhos, cheia = uns(entrada)
if unszinhos == True:
    print("Todos os números são uns.")
else:
    print("Todos os números não formados por uns.")

if cheia == True:
    print("Sequência cheia.")
else:
    print("Sequência não cheia.")