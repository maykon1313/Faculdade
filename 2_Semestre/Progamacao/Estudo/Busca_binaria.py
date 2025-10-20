vetor = [34, 24, 4, 43, 87, 12, 13, 4, 3, 6, 54, 76, 6, 51, 67]

#Bublee sort:
i = 0 
while i < len(vetor) -1:
    j = 0
    while j < len(vetor) -1:
        if vetor[j] > vetor[j+1]:
            vetor[j], vetor[j+1] = vetor[j+1], vetor[j]
        j += 1
    i += 1

#Busca binária:
print("Qual valor procurar no vetor?")
busca = int(input())

l = -1
r = len(vetor)
n_achou = True

while (l < (r - 1)) and n_achou:
    m = (l+r)//2
    if vetor[m] > busca:
        r = m
    elif vetor[m] < busca:
        l = m
    elif vetor[m] == busca:
        r = m
        n_achou = False

if n_achou:
        r = -1

print(vetor)
print(r)
if r != -1:
    print(vetor[r])

#Nova busca binária:
print("Qual valor procurar no vetor?")
busca = int(input())

l = -1
r = len(vetor) -1
n_achou = True

while (l < r) and n_achou:
    m = (l+r)//2
    if vetor[m] == busca:
        r = m
        n_achou = False
    elif vetor[m] > busca:
        r = m - 1
    elif vetor[m] < busca:
        l = m + 1

if n_achou:
        r = -1

print(vetor)
print(r)
if r != -1:
    print(vetor[r])