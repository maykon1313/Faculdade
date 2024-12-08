largu_array, largu_consu = map(int, input().split())
array = list(map(int, (input().split())))
consultas = list(map(int, (input().split())))

for i in range(len(consultas)):
    l = -1
    r = largu_array - 1
    while (r > l+1):
        m = int((r+l)/2)
        if array[m] >= consultas[i]:
            r = m
        else:
            l = m

    if consultas[i] == array[r]:
        print("YES")
    else:
        print("NO")