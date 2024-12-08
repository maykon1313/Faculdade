movimentos = int(input())
copo = input()

i = 0
while i < movimentos:
    movi = int(input())
    if movi == 1 and (copo == "A"):
        copo = "B"
    elif movi == 1 and (copo == "B"):
        copo = "A"
    if movi == 2 and (copo == "B"):
        copo = "C"
    elif movi == 2 and (copo == "C"):
        copo = "B"
    if movi == 3 and (copo == "A"):
        copo = "C"
    elif movi == 3 and (copo == "C"):
        copo = "A"
    i += 1

print(copo)