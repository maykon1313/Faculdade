#Inputs: Vertices e arestas
N, M = map(int, input().split())
relacoes = [] #Relações entre os vetores

for _ in range(M): #Receve as relações entre os vertices e adiciona no vetor "relacoes"
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    relacoes.append((a, b))

grafo = [[] for _ in range(N)] #Cria um vetor com a quantidade vertices do grafo
for a, b in relacoes: #Define quais vetores possuem relações e adiciona em suas respectivas posições
    grafo[a].append(b)#o vertice que possui relação(vizinho)
    grafo[b].append(a)#"Vai e vem"

vertice_visto = [False] * N #Cria um vetor para dizer que nenhum vertice foi visto, ainda.
familias = 0 #Contador

def dfs(vertices, vertice_visto): #Algoritmo de busca, qual o vertice, o grafo e se já foi visto
    stack = [vertices] #Pilha que vai receber os vertices vizinhos
    while stack: #Enquanto houver números na pilha
        vertices = stack.pop() #Adiciona o valor do topo da pilha para o verticque que queremos olhar
        if not vertice_visto[vertices]:
            vertice_visto[vertices] = True #Diz que ele já foi visto
            for vizinhos in grafo[vertices]: #No grafo ele olha os vertices que possui relação
                if not vertice_visto[vizinhos]: #Se ele ainda não foi visto
                    stack.append(vizinhos) #Adiciona a pilha o número vizinho sem chamar um novo dfs
    return True #DFS concluído

for vertices in range(N): #Para cada vertice do grafo:
    if not vertice_visto[vertices]: #Se não foi visto
        familias += 1 #Contador +1
        dfs(vertices, vertice_visto) #Qual o vertice, o grafo e se já foi visto

print(familias)

# 0(1): [2, 4]   [1, 3]
# 1(2): [1, 3]   [0, 2]
# 2(3): [2, 4]   [1, 3]
# 3(4): [3, 1]   [2, 1]