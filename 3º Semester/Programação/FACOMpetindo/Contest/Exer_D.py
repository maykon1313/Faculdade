alfabeto = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

t = int(input())

for _ in range(t):
    n, a, b = map(int, input().split())

    saida = ""

    for x in range(n):
        if x == 0 or x+1%a == 0 or aux == b:
            aux = 0
        
        saida += alfabeto[aux].lower()

        if aux+1 <= b:
            aux += 1

    print(saida)