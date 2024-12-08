def dfs(heroi, matriz, visto, soma, i, j):
    visto[i][j] = True
    soma += heroi
    
    if i > 0:
        if matriz[i-1][j] <= soma and visto[i-1][j] == False:
                soma = dfs(matriz[i-1][j], matriz, visto, soma, i-1, j)
    

    if i < len(matriz)-1:
        if matriz[i+1][j] <= soma and visto[i+1][j] == False:
                soma = dfs(matriz[i+1][j], matriz, visto, soma, i+1, j)
    

    if j < len(matriz[0])-1:
        if matriz[i][j+1] <= soma and visto[i][j+1] == False:
            soma = dfs(matriz[i][j+1], matriz, visto, soma, i, j+1)
    

    if j > 0:
        if matriz[i][j-1] <= soma and visto[i][j-1] == False:
            soma = dfs(matriz[i][j-1], matriz, visto, soma, i, j-1)

    return soma

n_linhas, m_colunas = map(int, input().split())

matriz = []
ajuda = []
visto = []
resu = []

for _ in range(n_linhas):
    nums = list(map(int, input().split()))
    matriz.append(nums)
    visto.append([False]*m_colunas)
    resu.append([0]*m_colunas)
    ajuda.append([False]*m_colunas)

for linha in range(n_linhas):
    for coluna in range(m_colunas):
        soma = 0
        heroi = matriz[linha][coluna]
        visto[linha][coluna] = True
        for linhaaa in range(len(visto)):
             for colunaaa in range(len(visto[0])):
                ajuda[linhaaa][colunaaa] = visto[linhaaa][colunaaa]
        resu[linha][coluna] = (dfs(heroi, matriz, ajuda, soma, linha, coluna))
        visto[linha][coluna] = False

for linha in range(n_linhas):
    resu_linha = ""
    for coluna in range(m_colunas):
        resu_linha += str(resu[linha][coluna]) + " "
    print(resu_linha)