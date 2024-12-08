valores = int(input())
gasto = 0
verba = 0

i = 0
while i < valores:
    Letra, valor = input().split()
    if Letra == "G":
        gasto = gasto + int(valor)
    if Letra == "V":
        verba = verba + int(valor)
    i += 1

if gasto > verba:
    print("NAO VAI TER CORTE, VAI TER LUTA!")
else:
    print("A greve vai parar.")