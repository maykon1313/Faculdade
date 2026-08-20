testes = int(input())
tracos = 0

def dfs(vertice, tracos, vertice_visto):
    vertice_visto[vertice] = True
    for vizinhos in grafo[vertice]:
        if not vertice_visto[vizinhos]:
            vertice_visto[vizinhos] = True
            tracos += 1
            tracos = dfs(vizinhos, tracos, vertice_visto)
            tracos += 1
    return tracos


for _ in range(testes):
    primeiro_vertice = int(input())

    V, A = map(int, input().split())

    grafo = [[] for _ in range(V)]

    for _ in range(A):
        a, b = map(int, input().split())
        grafo[a].append(b)
        grafo[b].append(a)
    
    vertice_visto = [False] * V

    print(dfs(primeiro_vertice, tracos, vertice_visto))