n = int(input())
i = 0
num_imp = str()

print("Os " + str(n) + " primeiros números ímpares são:")
while i < n:
    numeros_impares = 1 + 2*i
    if i == 0:
        num_imp = str(numeros_impares)
    elif i+1 < n: 
        num_imp = num_imp + ", " + str(numeros_impares)
    else:
        num_imp = num_imp + ", " + str(numeros_impares) + "."
    i = i + 1

print(num_imp)