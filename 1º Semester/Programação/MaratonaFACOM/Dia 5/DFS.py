# Inputs: Vertices e arestas
N, M = map(int, input().split())
relacoes = []  

for _ in range(M):  
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    relacoes.append((a, b))

grafo = [[] for _ in range(N)]  
for a, b in relacoes:  
    grafo[a].append(b)  
    grafo[b].append(a)  

familias = 0  

def dfs(vertices, vertice_visto):  
    stack = [vertices]  # Cria uma pilha com o vértice inicial
    while stack:  # Enquanto houver vértices na pilha
        vertice = stack.pop()  # Remove o vértice do topo da pilha
        if not vertice_visto[vertice]:  # Se o vértice não foi visitado
            vertice_visto[vertice] = True  # Marca o vértice como visitado
            for vizinho in grafo[vertice]:  # Para cada vizinho do vértice
                if not vertice_visto[vizinho]:  # Se o vizinho não foi visitado
                    stack.append(vizinho)  # Adiciona o vizinho à pilha
    return True  # Retorna True para indicar que a busca foi concluída

vertice_visto = [False] * N  
for vertices in range(N):  
    if not vertice_visto[vertices]:  
        familias += 1  
        dfs(vertices, vertice_visto)  

print(familias)