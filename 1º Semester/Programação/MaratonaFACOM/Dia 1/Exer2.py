diametro = int(input())
l = input().split()
l1 = int(l[0])
l2 = int(l[1])
l3 = int(l[2])

if diametro <= l1 and diametro <= l2 and diametro <= l3:
    print("S")
else:
    print("N")