n_array, pesquisas = map(int, input().split())
array = list(map(int, input().split()))

for i in range(pesquisas):
    numero = int(input())
    l = -1
    r = n_array - 1
    while (r > l + 1):
        m = (r+l)//2
        if array[m] >= numero:
            r = m
        else:   
            l = m
    
    if array[r] == numero:
        print(r)
    else:
        print(-1)