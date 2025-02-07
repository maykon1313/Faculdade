frase = "Eu tava comendo um gerimum, dai, veio um disco voador do nada e levou meu cão, i o pior é que ele nem havia terminado de pagar o IPVA do meu fusca, que vencia na sexta que caiu em um domingo."

contador_letra = 0
contador_letra_mais = 0
letra_mais = ''

i = 0
while i < len(frase):
    letra = frase[i]
    
    if letra == ' ':
        i += 1
        continue

    contador_letra = frase.lower().count(letra.lower())

    if contador_letra > contador_letra_mais:
        contador_letra_mais = contador_letra
        letra_mais = letra.lower()

    i += 1

print("A letra que mais apareceu foi: " + str(letra_mais) + ", com " +str(contador_letra_mais) + " aparições.")
