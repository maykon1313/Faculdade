n = int(input())

def MDC(a,b):
    resto = a%b
    while resto != 0:
            a = b
            b = resto
            resto = a%b
    return b

for i in range(n):
    x, y = map(int, input().split())
    if 2*x <= y:
        print(x, 2*x)
    else:
        print(-1, -1)