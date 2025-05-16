n = int(input())
repet = [0] * 6

i = 0
while i < n:
    x = int(input())
    repet[x-1] += 1
    i += 1

resu = str(repet[0])
z = 1
while z < len(repet):
    resu = resu + "," + str(repet[z])
    z += 1

print(resu)