print("Digite a altura:")
h = float(input())
print("Digite o peso:")
p = float(input())

imc = p/(h*h)

if imc < 20:
    print("Esqueleto.")
elif 20 <= imc < 25:
    print("Ordinário.")
elif 25 <= imc < 30:
    print("Fofinho.")
elif 30 <= imc < 40:
    print("Gordinho.")
else:
    print("Novo planeta.")