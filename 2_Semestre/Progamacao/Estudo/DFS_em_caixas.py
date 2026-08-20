caixa_principal = [[["brinquedo"],"arma","limosine"], ["lápis", "arroz", ["geogebra", "chave", "gengibre"]], ["ratoeira", "rato", ["queijo", "faca", ["porta", "porteiro"]]]]
achei = False
stack = []

for itens in caixa_principal:
    if achei:
        break
    stack.append(itens)
    while stack:
        caixa = stack.pop()
        for item in caixa:
            if type(item) == list:
                stack.append(item)
            else:
                if item == "chave":
                    achei = True
                    break

if achei:
    print("Achei a chave!")
else:
    print("Não achei...")