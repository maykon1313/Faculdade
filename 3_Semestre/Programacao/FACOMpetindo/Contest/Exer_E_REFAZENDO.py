testes = int(input())

for _ in range(testes):
    tamanho = int(input())
    array = list(map(int, input().split()))
    
    array.sort()

    x = array[0]
    y = None
    
    for num in array:
        if num%x != 0:
            y = num
            break

    if y is None:
        print("Yes")
        continue

    achou = True
    for num in array:
        if num%x != 0 and num%y != 0:
            achou = False
            break

    if achou:
        print("Yes")
    else:
         print("No")
