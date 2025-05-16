print("Digite um número:")
x = float(input())

if x == 5:
    print("É igual a 5.")
elif x == 200:
    print("É igual a 200.")
elif x == 400:
    print("É igual a 400.")
elif 500 <= x <= 1000:
    print("Está no intervalo 500 a 1000.")
else:
    print("Número inválido.")