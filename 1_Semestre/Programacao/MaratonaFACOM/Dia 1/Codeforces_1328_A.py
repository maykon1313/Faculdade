t = int(input())
for x in range(t):
    a, b = input().split()
    a = int(a)
    b = int(b)

    if a%b != 0:
        print(b - a%b)
    else:
        print(0)