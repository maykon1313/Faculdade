#Números de jogadores do time 1
#Números de jogadores do time 2
#Cartões máximos de cada jogador do time 1
#Cartões máximos de cada jogador do time 2
#Cartões totais da partida

n1 = int(input())
n2 = int(input())
c1 = int(input())
c2 = int(input())
ct = int(input())

#Expulções mínimas:
cartoes_maximo_1 = (n1*c1) - n1
cartoes_maximo_2 = (n2*c2) - n2
cartoes_maximo = cartoes_maximo_1 + cartoes_maximo_2

if ct <= cartoes_maximo:
    resposta = "0"
else:
    resposta = str(ct - cartoes_maximo)

#Expulções máximas:
expulcoes_maximo_1 = (n1*c1)
expulcoes_maximo_2 = (n2*c2)
expulcao = 0

if c1 < c2:
    while ct > c1:
        ct = ct - expulcoes_maximo_1
        expulcao = expulcao + 1
    while ct > c2:
        ct = ct - expulcoes_maximo_2
        expulcao = expulcao + 1
else:
    while ct > c2:
        ct = ct - expulcoes_maximo_2
        expulcao = expulcao + 1
    while ct > c1:
        ct = ct - expulcoes_maximo_1
        expulcao = expulcao + 1

resposta = resposta + " " + str(expulcao)
print(resposta)