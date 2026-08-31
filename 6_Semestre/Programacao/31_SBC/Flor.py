import sys
input = sys.stdin.readline

def main():
    n = int(input())

    if n == 1:
        return 2
    if n == 2:
        return 3
    
    f = {1: 2, 2: 3}
    f_inv = {2: 1, 3: 2}  # Mapeia valores para seus pré-images
    next_available = 4  # Otimização: rastrear próximo candidato
    
    for m in range(3, n + 1):
        if m in f_inv:
            # m é imagem de f_inv[m], então f(m) = 3 * f_inv[m]
            k = f_inv[m]
            f[m] = 3 * k
            f_inv[3 * k] = m
        else:
            # m é um novo ponto, encontre o menor não-usado > f[m-1]
            last_f = f[m - 1]
            while next_available <= last_f or next_available in f_inv:
                next_available += 1
            f[m] = next_available
            f_inv[next_available] = m
            next_available += 1
    
    print(f[n])

if __name__ == "__main__":
    main()
