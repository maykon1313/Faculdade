n_nobres = int(input())
relacoes = list(map(int, input().split()))

operacoes= int(input())

grafo = [1]
for i in range(n_nobres-1):
    grafo.append(-1)

for i in range(len(relacoes)):
    grafo[i+1] = relacoes[i]

for i in range(operacoes):
    aux = list(map(int, input().split()))
    acao = aux[0]
    num_do_nobre = aux[1] 
    if len(aux) == 3:
        posicoes_acima = aux[2]

    if acao == 1: #Qual o nobre superior?
        fila = []

        fila.append(grafo[num_do_nobre-1])

        while (posicoes_acima != 0):
            verti = fila.pop(0)
            posicoes_acima -= 1
            if (posicoes_acima == 0):
                break
            fila.insert(0, grafo[verti-1])

        print(verti)
        
    

    else: #reestruturação
        fila = []
        visto = [False]*n_nobres
        visto[num_do_nobre-1] = True

        for nobre in range(n_nobres):
            if grafo[nobre] == num_do_nobre:
                fila.append(nobre+1)

        while (len(fila) != 0):
            nobre = fila.pop(0)
            visto[nobre - 1] = True

            for nobres in range(n_nobres):
                if grafo[nobres] == nobre and visto[nobres] == False:
                    fila.append(grafo[nobres])
                    visto[nobres] = True
                    grafo[nobres] = num_do_nobre
            
            