#a)
n = int(input())

def quebra(n):
    primerio = 0
    vezes = 0
    q = n
    while q != 0:
        primerio = q
        vezes = vezes + 1
        q = q//10

    ultimo = n%10   

    if n > 9:
        meio = ((n)-(primerio*(10**(vezes-1)))-(ultimo))//10
    else:
        meio = 0
    
    return primerio, ultimo, meio

primerio, ultimo, meio = quebra(n)
print(str(n) + " " + str(primerio) + " " + str(ultimo) + " " + str(meio))

#b)
n = int(input())
palindromo = True
primerio, ultimo, meio = quebra(n)

while meio != 0:
    if primerio != ultimo:
        palindromo = False
        break
    primerio, ultimo, meio = quebra(meio)

if palindromo:
    print("É um palíndromo.")
else:
    print("Não é um palíndromo.")