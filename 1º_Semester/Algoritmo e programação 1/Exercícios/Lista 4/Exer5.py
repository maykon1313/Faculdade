n = int(input())
repet = [0] * 37

numeros = input().split()

i = 0
while i < n:
    x = int(numeros[i])
    repet[x] += 1
    i += 1

resu = str(repet[0])
z = 1
while z < len(repet):
    if z < len(repet)-1:
        resu += ", " + str(repet[z])
    else:
        resu += ", " + str(repet[z]) + "."
    z += 1

print(resu)