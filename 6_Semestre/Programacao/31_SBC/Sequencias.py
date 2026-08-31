import sys
input = sys.stdin.readline

def main():
    n = int(input())

    inter = []
    esquerda = 0

    for i in range(n):
        l, r = map(int, input().strip().split())

        if i == 0:
            inter.append([l, r])
            esquerda = l
        else:
            inter.append([max(esquerda, l), r])

        esquerda = max(esquerda+1, l)

    print(contar_sequencias(inter))    

def contar_sequencias(intervalos):
    dp = {0: 1}

    for L, R in intervalos:
        proximo_dp = {}
        soma_acumulada = 0

        valores_anteriores = sorted(dp.keys())
        idx_ant = 0
        
        for v in range(L, R + 1):
            while idx_ant < len(valores_anteriores) and valores_anteriores[idx_ant] < v:
                soma_acumulada += dp[valores_anteriores[idx_ant]]
                idx_ant += 1
            
            if soma_acumulada > 0:
                proximo_dp[v] = soma_acumulada
        
        dp = proximo_dp

    return sum(dp.values())

if __name__ == "__main__":
    main()
