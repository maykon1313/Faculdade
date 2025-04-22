valores = input().split()

menor = valores[0]

i = 1

while i < len(valores):
    if int(valores[i]) < int(menor):
        menor = valores[i]
    i = i + 1

print(str(menor))