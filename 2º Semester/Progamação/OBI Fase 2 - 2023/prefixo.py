n1 = int(input())
palavra1 = input()
n2 = int(input())
palavra2 = input()

if n1 > n2:
    menor = n2
else:
    menor = n1

i = 0
prefixos = 0
while i < menor:
    if palavra1[i] == palavra2[i]:
        prefixos += 1
    else:
        break
    i += 1

print(prefixos)