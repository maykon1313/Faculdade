n = int(input())
i = 0
num_ele = str()

print("Os " + str(n) + " primeiros números elevados a 2 são:")
while i < n:
    numeros_elevados = 2**i
    if i == 0:
        num_ele = str(numeros_elevados)
    elif i+1 < n: 
        num_ele = num_ele + ", " + str(numeros_elevados)
    else:
        num_ele = num_ele + ", " + str(numeros_elevados) + "."
    i = i + 1

print(num_ele)