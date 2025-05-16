n = int(input())
vetor = []
i = n

while n > 0 or i > 0:
    if n != 0:
        x = int(input())
        vetor.append(x)
        n = n - 1
    else:
        i = i - 1
        print(vetor[i])
#L








#B