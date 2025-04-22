testes = int(input())

for _ in range(testes):
    n = int(input())
    texto = input()
    aux = []

    for letra in texto:
        aux.append((letra, 1))

    aux = dict(aux)
    
    if len(aux) == n or len(texto) == n:
        print("YES")
    else:
        print("NO")