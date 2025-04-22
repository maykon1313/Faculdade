#Faixa de premiação(N) ; Ogros(M);
#Força limite para cada premiação(N-1);
#Cada valor da faixa de premiação;
#Força que cada ogro fez.

def calcular_premiacao(n, forca_por_premiacao, valor_da_fp, forca_dos_ogros):
    premiacao_para_cada_ogro = []

    for forca in forca_dos_ogros:
        for i in range(n-1):
            if forca < forca_por_premiacao[i] and i != n-1:
                premiacao_para_cada_ogro.append(valor_da_fp[i])
                break
            elif i == n-2:
                premiacao_para_cada_ogro.append(valor_da_fp[n-1])
    return premiacao_para_cada_ogro




n, m = map(int, input().split())

forca_por_premiacao = list(map(int, input().split()))

valor_da_fp = list(map(int, input().split()))

forca_dos_ogros = list(map(int, input().split()))

resultado = calcular_premiacao(n, forca_por_premiacao,valor_da_fp, forca_dos_ogros)

for _ in resultado:
    print(_, end=" ")