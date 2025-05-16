alfabeto = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

indice_letra = {letra: indice for indice, letra in enumerate(alfabeto)}

testes = int(input())

for _ in range(testes):
    frase = list(input())
    deslocada = int(input())
    
    alfabeto_deslocado = [alfabeto[(indice - deslocada) % 26] for indice in range(26)]

    for letra in frase:
        if letra in indice_letra:
            print(alfabeto_deslocado[indice_letra[letra]], end="")
        else:
            print(letra, end="")
    print()
