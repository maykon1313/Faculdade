def dijkstra(graph, start, goal):
    # Inicializa a distância de todos os vértices como infinito e a distância do início como 0
    min_dist = {vertex: float('infinity') for vertex in graph}
    min_dist[start] = 0

    # Inicializa a lista de prioridades com o vértice inicial
    priority_queue = [(0, start)]
    # Para rastrear o caminho
    previous = {vertex: None for vertex in graph}

    while priority_queue:
        # Encontra o vértice com a menor distância
        current_distance, current_vertex = min(priority_queue, key=lambda x: x[0])
        priority_queue.remove((current_distance, current_vertex))

        # Se chegarmos ao vértice objetivo, reconstruir o caminho
        if current_vertex == goal:
            path = []
            while previous[current_vertex] is not None:
                path.insert(0, current_vertex)
                current_vertex = previous[current_vertex]
            path.insert(0, start)
            return min_dist[goal], path

        # Verifica os vizinhos do vértice atual
        for neighbor, weight in graph[current_vertex]:
            distance = current_distance + weight

            # Se encontrar um caminho mais curto para o vizinho
            if distance < min_dist[neighbor]:
                min_dist[neighbor] = distance
                previous[neighbor] = current_vertex
                priority_queue.append((distance, neighbor))

    return float('infinity'), []

# Exemplo de uso
graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('A', 1), ('C', 2), ('D', 5)],
    'C': [('A', 4), ('B', 2), ('D', 1)],
    'D': [('B', 5), ('C', 1)]
}

start = 'A'
goal = 'D'
cost, path = dijkstra(graph, start, goal)

if path:
    print(f"Menor caminho de {start} para {goal} é {path} com custo {cost}")
else:
    print(f"Não há caminho de {start} para {goal}")
