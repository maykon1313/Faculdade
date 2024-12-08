print("Valor do produto:")
x = float(input())

if x < 50:
    x = x * 1.05
elif 50 <= x <= 100:
    x = x * 1.1
else:
    x = x * 1.15

print("Valor reajustado: " + str(x))

if x < 80:
    print("Balato né.")
elif 80 <= x <= 120:
    print("Tudo normar.")
elif 120 < x <= 200:
    print("Tá calo né.")
else:
    print("Um rim e meio.")