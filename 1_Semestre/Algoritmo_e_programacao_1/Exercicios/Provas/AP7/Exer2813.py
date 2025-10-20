#sol sol        0 0
#sol chuva      0 1
#chuva sol      1 0
#chuva chuva    1 0

idas = int(input())
casa = 0
casa_compra = 0
escri = 0
escri_compra = 0

i = 0
while i < idas:
    a, b = input().split()
    if (a == "sol") and (b == "chuva"):
        if escri == 0:
            casa += 1
            escri_compra += 1
        else:
            escri -= 1
            casa += 1
    if (a == "chuva") and (b == "sol"):
        if casa == 0:
            escri += 1
            casa_compra += 1
        else:
            casa -= 1
            escri += 1
    if (a == "chuva") and (b == "chuva"):
        if casa == 0:
            casa += 1
            casa_compra += 1
    i += 1

print(str(casa_compra) + " " + str(escri_compra))