caixa_principal = ["nada", [["brinquedo"], "arma", "limosine"], ["lápis", "arroz", ["geogebra", "chave", "gengibre"]], ["ratoeira", "rato", ["queijo", "faca", ["porta", "porteiro"]]]]
achei = False
queue = []

for itens in caixa_principal:
    queue.append(itens)

while queue and not achei:
    caixa = queue.pop(0)
    if type(caixa) == str:
        if caixa == "chave":
            achei = True
            break
    else:
        for item in caixa:
            if type(item) == list:
                queue.append(item)
            else:
                if item == "chave":
                    achei = True
                    break
            

if achei:
    print("Chave encontrada!")
else:
    print("Chave não encontrada.")
