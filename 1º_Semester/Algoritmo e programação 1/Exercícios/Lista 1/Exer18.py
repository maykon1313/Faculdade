print("Qual a área?")
area = float(input())

import math

latas = math.ceil(area/54)
valor = latas * 80

print("Latas de 18L: " + str(latas))
print("Valor: " + str(valor))