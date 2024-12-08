#"Selection sort"(Pega o menor valor e adiciona em uma nova lista, e remove-o da lista antiga)
valores = input().split()
ordem = []

def menor(valores):
    i = 1
    menor = valores[0]
    while i < len(valores):
        if int(valores[i]) < int(menor):
            menor = valores[i]
        i = i + 1
    return menor

j = 0
while j < len(valores):
    num = menor(valores)
    ordem.append(num)
    valores.remove(num)

print(ordem)

#Bubble sort (Pega um número e vai levando ele para a direita o mais longe possível, depois troca o valor e repete, ao fim da lista ele recomeça do primeiro valor)
valores = input().split()

x = 0
while x < (len(valores)-1):
    z = 0
    while z < (len(valores)-1):
        if int(valores[z]) > int(valores[z+1]):
            aux = valores[z]
            valores[z] = valores[z+1]
            valores[z+1] = aux
        z = z + 1
    x = x + 1

print(valores)