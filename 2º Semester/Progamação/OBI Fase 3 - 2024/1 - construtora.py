n = int(input())
predios = list(map(int, input().split()))
fase = 0
sequecia = False

maior = predios[0]

for i in range(n):
    if predios[i] > maior:
        maior = predios[i]

while (maior*n != sum(predios)):
    for i in range(n):
        if i != n-1 and predios[i] == predios[i+1] and predios[i] != maior:
            predios[i] += 1
            sequecia = True
        elif sequecia:
            predios[i] += 1
            fase += 1
            sequecia = False
        elif i == n-1 and predios[i] < maior:
            predios[i] += 1
            fase += 1
            

print(fase)