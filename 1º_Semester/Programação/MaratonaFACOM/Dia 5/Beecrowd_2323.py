from collections import defaultdict

conexoes = int(input())
grafo = defaultdict(list)

def count_pieces(node, memo):
    if node in memo:
        return memo[node]
    
    sizes = []
    for child in grafo[node]:
        size = count_pieces(child, memo)
        if size == -1:
            memo[node] = -1
            return -1
        sizes.append(size)
    
    if len(set(sizes)) > 1:
        memo[node] = -1
        return -1
    
    total_size = 1 + sum(sizes)
    memo[node] = total_size
    return total_size

for _ in range(conexoes):
    a, b = map(int, input().split())
    grafo[b].append(a)

memo = {}
if count_pieces(0, memo) != -1:
    print("bem")
else:
    print("mal")