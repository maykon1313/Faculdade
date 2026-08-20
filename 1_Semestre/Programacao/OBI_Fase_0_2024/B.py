def temporal_bfs(graph, start, cities_to_visit, total_cities, total_edges):
    pq = [(0, start)]
    visited = {i: float('inf') for i in range(1, total_cities + 1)}
    visited[start] = 0
    visited_count = 0

    while pq:
        current_time, node = min(pq, key=lambda x: x[0])
        pq.remove((current_time, node))

        if visited[node] == current_time:
            visited_count += 1
            if visited_count == cities_to_visit:
                return current_time

        for neighbor, time in graph[node]:
            if current_time <= time < visited[neighbor]:
                visited[neighbor] = time
                pq.append((time, neighbor))

    return -1

def main():
    total_cities, total_edges, cities_to_visit = map(int, input().split())
    graph = {}

    for _ in range(total_edges):
        u, v, t = map(int, input().split())
        if u not in graph:
            graph[u] = []
        if v not in graph:
            graph[v] = []
        graph[u].append((v, t))
        graph[v].append((u, t))

    start_city = 1

    result = temporal_bfs(graph, start_city, cities_to_visit, total_cities, total_edges)
    print(result)

if __name__ == "__main__":
    main()
