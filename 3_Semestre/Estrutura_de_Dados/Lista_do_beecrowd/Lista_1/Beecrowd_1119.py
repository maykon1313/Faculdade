while True:
    N, K, M = map(int, input().split())
    if (N, K, M) == (0, 0, 0):
        break

    v = [i + 1 for i in range(N)]
    
    i = 0
    j = N - 1
    
    cont = 0  # Quantidade de números já removidos
    resultado = []

    while cont < N:
        passos = K
        while passos > 0:
            if v[i] != 0:
                passos -= 1
                if passos == 0:
                    index1 = i  # Índice do número a ser eliminado pela contagem K
            i = (i + 1) % N

        passos = M
        while passos > 0:
            if v[j] != 0:
                passos -= 1
                if passos == 0:
                    index2 = j  # Índice do número a ser eliminado pela contagem M
            j = (j - 1 + N) % N  # Ajusta a posição de forma circular para trás

        # Se não for a primeira impressão, adiciona vírgula antes do par ou do único número
        if cont > 0:
            resultado.append(",")

        # Se os índices selecionados forem diferentes, elimina dois números
        if index1 != index2:
            resultado.append(f"{v[index1]:3d}{v[index2]:3d}")
            cont += 2
        else:
            resultado.append(f"{v[index1]:3d}")
            cont += 1

        # Marca os números eliminados com zero
        v[index1] = 0
        v[index2] = 0

    # Exibe a saída formatada conforme o esperado
    print("".join(resultado))
