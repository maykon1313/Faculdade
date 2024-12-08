def exp_rapida(base, exp, mod):
    resu = 1
    while exp > 0:
        if exp & 1:
            resu = (resu * base) % mod
        base = (base * base) % mod
        exp = exp // 2
    return resu

def main():
    casos = int(input())

    for _ in range(casos):
        a, b = map(int, input().split())

        if a == 0:
            print(0)
        elif b == 0:
            print(1)
        else:
            print(exp_rapida(a, b, 10))

if __name__ == "__main__":
    main()
