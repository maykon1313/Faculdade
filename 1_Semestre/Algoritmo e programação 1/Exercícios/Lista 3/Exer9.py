n = int(input())
numeros = 0
i = 0
positivo = 0
n_positivo = 0

while i < n:
    numeros = int(input())
    if numeros > 0:
        positivo = positivo + 1
    else:
        n_positivo = n_positivo + 1
    i = i + 1

print("Foram " + str(positivo) + " positivos e " +  str(n_positivo) + " não positivos.")