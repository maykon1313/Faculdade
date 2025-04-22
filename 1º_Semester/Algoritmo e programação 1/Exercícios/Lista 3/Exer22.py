#a)
n = int(input())

def comprimento(n):
    contador = 1
    resposta = str(n) + " "
    while n > 1:
        if n%2 == 0:
            n = n/2
        else:
            n = (n*3) + 1
        resposta = resposta + str(int(n)) + " "
        contador += 1
    print(resposta)
    return contador

contador = comprimento(n)
print("Comprimento: " + str(contador))

#b)
k = int(input())
i = 0

while i < k:
    z = int(input())
    contador = comprimento(z)
    print("Comprimento: " + str(contador))
    i = i + 1