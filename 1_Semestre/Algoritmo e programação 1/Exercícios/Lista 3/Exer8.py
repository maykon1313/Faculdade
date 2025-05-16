n = 7
numeros = 0
i = 0
dias_zero = 0

while i < n:
    numeros = int(input())
    if numeros < 0:
        dias_zero = dias_zero + 1
    i = i + 1

print("Fizeram " + str(dias_zero) + "dias com temperatura negativa.")