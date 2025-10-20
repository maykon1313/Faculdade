n = int(input())

def mdc(a,b):
        resto = a%b
        while resto != 0:
                a = b
                b = resto
                resto = a%b
        return b

for i in range(n):
    a, b = map(int, input().split())

    print(mdc(a, b))