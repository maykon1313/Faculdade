dinheiro = int(input())
conta1 = int(input())
conta2 = int(input())
conta3 = int(input())
pagas = 0

if conta2 < conta1 and conta2 < conta3:
    conta1, conta2 = conta2, conta1
elif conta3 < conta1 and conta3 < conta2:
    conta1, conta3 = conta3, conta1
if conta3 < conta2:
    conta2, conta3 = conta3, conta2

if dinheiro >= conta1:
    dinheiro = dinheiro - conta1
    pagas = 1
    if dinheiro >= conta2:
        dinheiro = dinheiro - conta2
        pagas = 2
        if dinheiro >= conta3:
            pagas = 3

print(pagas)