testes = int(input())

def prioridade(array, final):
    ...

for _ in range(testes):
    n, s = map(int, input().split())
    array = list(map(int, input().split()))
    passos = 0
    
    soma = sum(array)
    while soma > s:
        passos += 1
        if array[n - passos] == 1:
            array.pop()
        else:
            array.pop(0)

        soma = sum(array)

    if soma < s:
        print("-1")
    else:
        print(passos)