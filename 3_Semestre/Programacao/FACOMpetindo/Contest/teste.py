import math

testes = int(input())

for _ in range(testes):
    tamanho = int(input())
    array = list(map(int, input().split()))
    achou = True

    array.sort()

    x = math.gcd(array[0], array[1])

    for i in range(tamanho):
        if array[i] % x != 0:
            achou = False
            break

    if achou:
        print("Yes")
    else:
        print("No")
