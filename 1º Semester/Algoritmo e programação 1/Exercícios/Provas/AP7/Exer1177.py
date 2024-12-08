max = int(input())
aux = 0

x = 0
while x < 1000:
    if aux == max:
        aux = 0
    print("N[" + str(x) + "] = " +str(aux))
    aux += 1
    x += 1