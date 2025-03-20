def primo(num):
    for i in range(num):
        if i == 0:
            continue
        if i == 2:
            return 0
        if num%i == 0 and i != 1:
            return 0
    return 1

testes = int(input())

for _ in range(testes):
    tamanho = int(input())
    array = list(map(int, input().split()))
    achou = False
    primos = 0

    for num in array:
        if num == 1:
            achou = True
            break

        primos += primo(num)

    if not achou and primos < 2:
        for i in range(tamanho):
            aux1 = array[i]
            for j in range(tamanho):
                k = 0

                if i == j:
                    continue
                
                aux2 = array[j]

                while k < tamanho:
                    if array[k]%aux1 != 0 and array[k]%aux2!= 0:
                        break
                    k += 1
                
                if k == tamanho:
                    achou = True
                    break

            if k == tamanho:
                    achou = True
                    break
    
    if achou:
        print("Yes")
    else:
         print("No")
