print("Diária:")
d = float(input())
print("Quartos:")
q = float(input())

promo = d * 0.75
ocu100 = promo * q
ocu70 = promo * (q * 0.7)
deixa = d * q - promo * q

print("Valor promocional da diária: " + str(promo))
print("Valor total 100%: " + str(ocu100))
print("Valor 70%: " + str(ocu70))
print('"Deixará" de arrecadar: ' + str(deixa))