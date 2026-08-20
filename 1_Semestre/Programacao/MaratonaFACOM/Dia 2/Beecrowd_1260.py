n = int(input())
nada = input()

for i in range(n): 
    dic = {}
    semdup = []
    array = []
    while True:
        try:
            arvore = str(input())
            if arvore == "":
                break
            else:
                array.append(arvore)
                try:
                    dic[arvore] += 1
                except KeyError:
                    dic[arvore] = 1
                    semdup.append(arvore)
        except EOFError:
            break   
    
    semdup.sort()

    for arvores in semdup:
        DIV = ((dic[arvores]/len(array))*100)
        print(arvores, "{:.4f}".format(DIV))
    if i < n - 1:
        print()