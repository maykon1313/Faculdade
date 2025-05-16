print("Qual a área?")
area = float(input())

import math

latas1 = math.ceil(area/54)
valor1 = latas1 * 80

print("Latas de apenas 18L: " + str(latas1))
print("Valor: " + str(valor1))

latas2 = math.ceil(area/10.8)
valor2 = latas2 * 25

print("Latas de apenas 3,6L: " + str(latas2))
print("Valor: " + str(valor2))

latas18 = int(area/54)
latas36 = math.ceil(math.ceil((area/3) - int(area/3))/3.6)
valor3 = (latas18 * 80) + (latas36 * 25)

print("Latas mistas de 18L: " + str(latas18))
print("Latas mistas de 3.6L: " + str(latas36))
print("Valor: " + str(valor3))