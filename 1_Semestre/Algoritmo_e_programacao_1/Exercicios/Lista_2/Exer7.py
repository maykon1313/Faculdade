print("Digite um número:")
x = float(input())

if x%10 == 0:
    print("Divisível por 10.")
if x%5 == 0:
    print("Divisível por 5.")
if x%2 == 0:
    print("Divisível por 2.")
if x%10 and x%5 and x%2 != 0:
    print("Não é divisível por 10, por 5 e por 2.")