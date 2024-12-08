t = int(input())
for x in range(t):
    h, m = input().split()
    h = int(h)
    m = int(m)

    hora = 24 - h
    if m == 0:
        minuto = (hora * 60)
        print(minuto)
    else:
        minuto = (60 - m) + ((hora - 1) * 60)
        print(minuto)