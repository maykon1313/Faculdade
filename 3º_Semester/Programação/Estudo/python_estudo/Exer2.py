def menu():
    print("1 - Soma.")
    print("2 - Subtração.")
    print("3 - Multiplicação.")
    print("4 - Divisão.")
    print("5 - Sair.")

    escolha = input()

    return escolha
    
def soma(num1, num2):
    return num1 + num2

def subtracao(num1, num2):
    return num1 - num2

def multiplicacao(num1, num2):
    return num1 * num2

def divisao(num1, num2):
    return num1 / num2

continua = True
while continua:
    escolha = menu()

    if escolha == '5':
        continua = False 
    else:
        try:
            print("Digite o primeiro número:")
            num1 = float(input())
            print("Digite o Segundo número:")
            num2 = float(input())
        except:
            print("Número(s) inválido(s)")
            continue

        if escolha == '1':
            resultado = soma(num1, num2)
            print(f'{resultado=}')

        elif escolha == '2':
            resultado = subtracao(num1, num2)
            print(f'{resultado=}')

        elif escolha == '3':
            resultado = multiplicacao(num1, num2)
            print(f'{resultado=}')

        elif escolha == '4':
            resultado = divisao(num1, num2)
            print(f'{resultado=}')

