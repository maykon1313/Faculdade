n_linhas, m_colunas, passos = map(int, input().split())

if m_colunas != 2:
    matriz = []
    aux = 1
    for i in range(n_linhas):
        matriz.append([])
        for j in range(m_colunas):
            matriz[i].append(aux)
            aux += 1

    for _ in range(passos):
        movi, a, b = input().split()

        a = int(a)-1
        b = int(b)-1

        if movi == "L":
            matriz[a], matriz[b] = matriz[b], matriz[a]

        else:
            for linha in range(n_linhas):
                matriz[linha][a], matriz[linha][b] = matriz[linha][b], matriz[linha][a]

    for linha in range(n_linhas):
        resu_linha = ""
        for coluna in range(m_colunas):
            resu_linha += str(matriz[linha][coluna]) + " "
        print(resu_linha)

else:
    matriz = []
    aux1 = 1
    aux2 = 2
    for j in range(m_colunas):
        matriz.append([])
        for i in range(n_linhas):
            if j == 0:
                matriz[j].append(aux1)
                aux1 += 2
            else:
                matriz[j].append(aux2)
                aux2 += 2

    for _ in range(passos):
        movi, a, b = input().split()

        a = int(a)-1
        b = int(b)-1

        if movi == "C":
            matriz[a], matriz[b] = matriz[b], matriz[a]

        else:
            aux1 = matriz[0][a]
            aux2 = matriz[1][a]
            matriz[0][a], matriz[1][a] = matriz[0][b], matriz[1][b]
            matriz[0][b], matriz[1][b] = aux1, aux2

    for linha in range(n_linhas):
        resu_linha = str(matriz[0][linha]) + " " + str(matriz[1][linha])
        print(resu_linha)