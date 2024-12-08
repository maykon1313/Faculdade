CASOS = int(input())

abc = "abcdefghijklmnopqrstuvwxyz"

def dfs(vertice, vertice_visitado, grafo, familia):
    stack = [vertice]
    while stack:
        vertice_atual = stack.pop()
        if not vertice_visitado[vertice_atual]:
            vertice_visitado[vertice_atual] = True
            familia.append(vertice_atual) #No fim, ele que se altera.
            for vizinhos in grafo[vertice_atual]:
                if not vertice_visitado[vizinhos]:
                    stack.append(vizinhos)

for caso in range(1, CASOS+1):
    vertices, relacoes = map(int, input().split())

    grafo = {j: [] for j in range(vertices)}

    for _ in range(relacoes):
        a, b = map(abc.index, input().split())
        grafo[a].append(b), grafo[b].append(a)

    vertice_visitado = [False] * vertices

    familias = []

    for vertice in range(vertices):
        if not vertice_visitado[vertice]:
            familia = []
            dfs(vertice, vertice_visitado, grafo, familia)
            familias.append(sorted(familia))

    print("Case #" + str(caso) + ":")

    for familia in familias:
        fami = [abc[i] for i in familia]
        resu = (",".join(fami) + ",")
        print(str(resu))

    print(str(len(familias)) + " connected components")

    print()