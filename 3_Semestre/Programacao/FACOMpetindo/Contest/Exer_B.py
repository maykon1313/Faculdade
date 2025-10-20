ent1 = input()
ent2 = input()

saida = ""

for i in range(len(ent1)):
    if ent1[i] == "1" and ent2[i] == "1":
        saida += "0"
    elif ent1[i] == "1" or ent2[i] == "1":
        saida += "1"
    else:
        saida += "0"

print(saida)