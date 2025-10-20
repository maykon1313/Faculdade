def picolinos(vetor):
    picos = 0
    i = 0
    while i < n:
        if i == 0:
            if (vetor[-1] < vetor[i] > vetor[i+1]) or (vetor[-1] > vetor[i] < vetor[i+1]):
                picos = picos + 1
        elif i == n-1:
            if (vetor[i-1] < vetor[i] > vetor[0]) or (vetor[i-1] > vetor[i] < vetor[0]):
                picos = picos + 1
        else:
            if (vetor[i-1] < vetor[i] > vetor[i+1]) or (vetor[i-1] > vetor[i] < vetor[i+1]):
                picos = picos + 1
        i = i + 1
    
    return picos


while True:
    try:
        n = int(input())
        if n == 0:
            break
        vetor = list(map(int, input().split(" ")))
        print(picolinos(vetor))
    except EOFError:
        break