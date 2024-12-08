entrada = input().split()
max = len(entrada) - 1
min = 0
optimus_prime = True

def Bumblebee(valores):
    x = 0
    while x < (len(valores)-1):
        z = 0
        while z < (len(valores)-1):
            if int(valores[z]) > int(valores[z+1]):
                aux = valores[z]
                valores[z] = valores[z+1]
                valores[z+1] = aux
            z = z + 1
        x = x + 1
    return valores

organizado = list(map(int, Bumblebee(entrada)))

anterior = organizado[max] + organizado[min]
min += 1
max -= 1
while min < max:
    atual = organizado[max] + organizado[min]
    if atual != anterior:
        optimus_prime = False
    anterior = atual
    min += 1
    max -= 1


if optimus_prime:
    print("Balanciaga.")
else:
    print("Desbalanciaga.")