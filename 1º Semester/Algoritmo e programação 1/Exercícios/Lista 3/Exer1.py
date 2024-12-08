n = int(input())
i = 1
soma_tudo = 0

while i < n+1:
    soma_tudo = soma_tudo + i
    i = i + 1

print("A soma dos " + str(n) + " primeiros números deu " + str(soma_tudo) + ".")