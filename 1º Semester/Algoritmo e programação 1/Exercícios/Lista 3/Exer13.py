n = int(input())
i = 0
nao_deu = 0

while i < n:
    numeros = int(input())
    if i == 0:
        verificador = numeros
    elif verificador <= numeros:
        verificador = numeros
    else:
        nao_deu = 1
    i = i + 1

if nao_deu == 0:
    print("Está em ordem crescente.")
else:
    print("Não está em ordem crescente.")