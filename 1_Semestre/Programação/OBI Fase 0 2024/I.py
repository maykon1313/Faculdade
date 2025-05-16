N, M = map(int, input().split())

colar = input()
grupos = []
soma = 0

colar = list(zip(*[iter(colar)]*M))

for gru in colar:
    soma = 0
    for num in gru:
        soma = soma + int(num)
    grupos.append(soma)

novo = set(grupos)
if len(novo) != len(grupos):
    print("N")
else:
    print("S")