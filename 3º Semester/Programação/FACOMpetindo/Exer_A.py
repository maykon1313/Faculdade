entrada = input()

coluna = entrada[0]
linha = entrada[1]

saida = 8

if coluna == "a" or coluna == "h":
    saida -= 3

if linha == "1" or linha == "8":
    saida -= 3

if coluna == "a" and linha == "1":
    saida += 1

if coluna == "h" and linha == "1":
    saida += 1

if coluna == "a" and linha == "8":
    saida += 1

if coluna == "h" and linha == "8":
    saida += 1

print(saida)