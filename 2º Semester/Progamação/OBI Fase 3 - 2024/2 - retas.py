n, x1, x2 = map(int, input().split())
cont = 0
aux1 = False
aux2 = False

v1 = []

for _ in range(n):
    a, b = map(int, input().split())
    resu1 = a * x1 + b
    resu2 = a * x2 + b

    aux1 = False
    aux2 = False
    for i in range(len(v1)):
        if resu1 == v1[i]:
            cont += 1
            aux1 = True

    for i in range(len(v1)):
        if resu2 == v1[i]:
            cont += 1
            aux2 = True

    if not aux1:
        v1.append(resu1)
    if not aux2:
        v1.append(resu2)

print(cont)