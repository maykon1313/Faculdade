n = int(input())
numeros = 0
i = 0
par = 0
impar = 0

while i < n:
    numeros = int(input())
    if numeros%2 == 0:
        par = par + 1
    else:
        impar = impar + 1
    i = i + 1

print("Foram " + str(par) + " pares e " +  str(impar) + " ímpares.")