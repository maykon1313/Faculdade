print("Digite um número:")
x = float(input())
print("Digite outro número:")
y = float(input())
print("Digite outro número:")
z = float(input())

if x > y:
    a = x
    x = y
    y = a

if y > z:
    a = y
    y = z
    z = a

if x > y:
    a = x
    x = y
    y = a

print("Menor: " + str(x) + ", Médio: " + str(y) + ", Maior: " + str(z)) 