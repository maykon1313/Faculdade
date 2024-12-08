max = 19
min = 0

vetor = []

i = 0
while i < 20:
    x = int(input())
    vetor.append(x)
    i += 1

while min < max:
    aux = vetor[min]
    vetor[min] = vetor[max]
    vetor[max] = aux
    min += 1
    max -= 1

z = 0
while z < 20:
    print("N[" + str(z) + "] = " +str(vetor[z]))
    z += 1