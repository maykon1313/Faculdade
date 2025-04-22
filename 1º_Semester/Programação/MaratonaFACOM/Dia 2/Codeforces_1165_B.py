banco_de_questoes = int(input())
questoes_por_banca = list(map(int, input().split()))
dias = 0

questoes_por_banca.sort()

for i in range(banco_de_questoes):
    if questoes_por_banca[i] >= dias+1 or (devendo <= questoes_por_banca[i]) and devendo != 0:
        dias = dias + 1
        devendo = 0
    elif devendo == 0:
        devendo = i + 1

print(dias)