while True:
    n, d = map(int, input().split())
    if n == 0 and d == 0:
        break
    matriz = []
    for jantas in range(d):
        vetor = input().split()
        matriz.append(vetor)
    
    j = 0
    tem = False
    nao_deu = False
    
    for num in matriz[0]:
        i = 0
        nao_deu = False
        while i < d:
            if int(matriz[i][j]) == 0:
                nao_deu = True
            if nao_deu == False and i == d-1:
                tem = True
            i = i + 1
        j = j + 1
    
    if tem == True:
        print("yes")
    else:
        print("no")