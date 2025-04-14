t = int(input())
 
for x in range(t):
    a, b = map(int, input().split())
    if b > a:
        aux = a
        a = b
        b = aux
    if (a+b)%3 == 0 and 2*b >= a:
        print("YES")
    else:
        print("NO")