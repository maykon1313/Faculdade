# Definindo as relações
relation = {
    "João": ["Lucas", "Maria"],
    "Lucas": ["João"],
    "Maria": ["Roberto", "Lucas"],
    "Roberto": ["Pedro"],
    "Pedro": [],
    "Carlos": []
}

# Função para inicializar o dicionário de visitados
def init_saw_it(relation):
    return {person: False for person in relation}

# BFS: João vai ser o início
def bfs(start, target, relation):
    saw_it = init_saw_it(relation)
    queue = [start]
    saw_it[start] = True
    
    while queue:
        nome = queue.pop(0)
        if nome == target:
            return True
        for neighbor in relation[nome]:
            if not saw_it[neighbor]:
                saw_it[neighbor] = True
                queue.append(neighbor)
    return False

# DFS: João vai ser o início
def dfs(start, target, relation):
    saw_it = init_saw_it(relation)
    stack = [start]
    
    while stack:
        nome = stack.pop()
        if nome == target:
            return True
        if not saw_it[nome]:
            saw_it[nome] = True
            stack += relation[nome]
    return False

# Verificando os caminhos
start = "João"
target = "Pedro"

if bfs(start, target, relation):
    print("There is a way (BFS).")
else:
    print("Do you know the way? (BFS)")

if dfs(start, target, relation):
    print("There is a way (DFS).")
else:
    print("Do you know the way? (DFS)")