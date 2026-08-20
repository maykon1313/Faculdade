n = int(input())
i = int(input())
j = int(input())
z = 0
resultado = ""
numeros = 0

while numeros != n:
    if z%i == 0 or z%j == 0:
        resultado = resultado + str(z) + " "
        numeros = numeros + 1
    z = z + 1

print(resultado)