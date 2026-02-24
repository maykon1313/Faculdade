import math

def primo(n):
    if n <= 1: return False
    if n == 2: return True
    if n % 2 == 0: return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0: return False
    return True

with open("primo.py", 'w', encoding='utf-8') as f:
    f.write("print('Digite o número que deseja saber se é primo:')\n")
    f.write("n = int(input())\n\n")

    for i in range(10000001):
        if i == 0:
            f.write("if n == " + str(i) + ":\n")
        else:
            f.write("elif n == " + str(i) + ":\n")

        if primo(i):
            f.write("   print('" + str(i) + " é um número primo.')\n")
        else:
            f.write("   print('" + str(i) + " não é um número primo.')\n")
