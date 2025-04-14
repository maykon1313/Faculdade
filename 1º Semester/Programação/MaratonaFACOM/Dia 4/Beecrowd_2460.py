pessoas = int(input())
fila = list(map(int, input().split()))
pessoas_desistiram = int(input())
numeros_desistiram = list(map(int, input().split()))

for numero in numeros_desistiram:
    fila.remove(numero)

for numero in fila:
    if numero == fila[0]:
        texto = str(numero)
    else:
        texto = texto + " " + str(numero)

print(texto)