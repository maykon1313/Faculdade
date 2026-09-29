import sys
input = sys.stdin.readline

def main():
    n = int(input())

    pecas = list(map(int, input().strip().split()))
    metas = list(map(int, input().strip().split()))

    soma = 0
    menor = pecas[0] - metas[0]

    for i in range(n):
        if pecas[i] < metas[i]:
            print("-1")
            return

        soma += pecas[i]

        aux = pecas[i] - metas[i]
        if aux < menor:
            menor = aux

    print(soma - menor)
        

if __name__ == "__main__":
    main()
