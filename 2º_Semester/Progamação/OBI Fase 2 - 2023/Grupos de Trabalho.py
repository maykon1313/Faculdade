Estudantes, pares, odios = map(int, input().split())
pares_ruins = []
conflitos = 0

for i in range(pares):
    x, y = map(int, input().split())

for i in range(odios):
    x, y = map(int, input().split())
    pares_ruins.append((x, y))

for i in range(Estudantes//3):
    a, b, c = map(int, input().split())
    if (a, b) in pares_ruins or (b, a) in pares_ruins:
        conflitos += 1
    if (a, c) in pares_ruins or (c, a) in pares_ruins:
        conflitos += 1
    if (b, c) in pares_ruins or (c, b) in pares_ruins:
        conflitos += 1


print(conflitos)