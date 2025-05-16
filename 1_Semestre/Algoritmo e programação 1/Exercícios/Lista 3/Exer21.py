#A)
def conta_digitos(digito, n):
    repe = 0
    i = 0
    n = str(n)
    while i < len(n):
        if int(n[i]) == digito:
            repe = repe + 1
        i = i + 1
    return repe

n = input()
digito = int(input())
repeticoes = conta_digitos(digito, n)

print("O digito " + str(digito) + " aparece " + str(repeticoes) + " vezes no número " + str(n) + ".")



#B)
entrada1 = int(input())
entrada2 = int(input())

def compara_eles(x, y):
    q = x
    while q != 0:
        ult = q%10
        if conta_digitos(ult, x) != conta_digitos(ult, y):
            return False
        q = q//10
    return True


if compara_eles(entrada1, entrada2):
    print("São permutação.")
else:
    print("Não são permutação.")