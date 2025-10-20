print("Custo de fábrica:")
c = float(input())
print("Percentagem do distribuidor:")
d = float(input())
print("Impostos:")
i = float(input())

impos = c * i
percen = d * impos
precofinal = c + percen + impos

print("O preço será: " + str(precofinal))