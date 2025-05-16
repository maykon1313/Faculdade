print("Quantos dias?")
d = int(input())
print("Quantos dias no mês?")
m = int(input())

maior = d + m -(d%m)

print("O número de dias maior que " + str(d) + " e multiplo de " + str(m) + "é" + str(maior))