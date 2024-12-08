perguntas = int(input())
pontos = input().split()

#Valor de um dado: 21
#Valores para os dados de baixo: 14, 14, 14.
#Valores para o dado de cima: 20, 19, 18, 17, 16, 15.

for x in pontos:
    x = int(x)
    if x >= 15 and x%14 <= 6 and x%14 >= 1:
        print("YES")
    else:
        print("NO")