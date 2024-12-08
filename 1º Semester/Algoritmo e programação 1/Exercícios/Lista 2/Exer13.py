print("Digite o lado A:")
a = float(input())
print("Digite o lado B:")
b = float(input())
print("Digite o lado C:")
c = float(input())

if a > b and a > c:
    a = a
elif b > a and b > c:
    aux = a
    a = b
    b = aux
else:
    aux = a
    a = c
    c = aux

if a >= b + c:
    print("Triângulo não formado.")
elif a*a == b*b + c*c:
    print("Triângulo retângulo.")
elif a*a > b*b + c*c:
    print("Triângulo obtusângulo.")
elif a*a < b*b + c*c:
    print("Triângulo acutângulo.")

if a == b and a == c:
    print("Triângulo equilátero.")
elif (a == b and a != c) or (b == c and b != a) or (a == c and a != b):
    print("Triângulo isósceles.")
else:
    print("Triângulo escaleno.")