z = int(input())
for j in range(z): #TESTE
    dicio = {}
    palavras, linhas = map(int, input().split())


    for i in range(palavras): #PALAVRAS
        x = str(input())
        y = str(input())
        dicio[x] = y

    for w in range(linhas): #FRASES
        vetor = input().split()
        for t in range(len(vetor)):
            try:
                vetor[t]=dicio[vetor[t]]
            except:
                pass
        print(*vetor, sep=" ") 
    print()