def prioridade(caracter):
    if caracter == "+" or caracter == "-":
        return 1
    elif caracter == "*" or caracter == "/":
        return 2
    elif caracter == "^":
        return 3
    else:
        return 0    

casos = int(input())

for _ in range(casos):
    expressao = input()

    pilha = []
    saida = ""

    for caracter in expressao:
        if caracter.isalpha() or caracter.isalnum():
            saida += caracter
        
        elif caracter == "(":
            pilha.append(caracter)

        elif caracter == ")":
            while pilha and pilha[-1] != "(":
                saida += pilha.pop()
            pilha.pop()
        
        else:
            while pilha and prioridade(pilha[-1]) >= prioridade(caracter):
                saida += pilha.pop()
            pilha.append(caracter)
                
    while (pilha):
        saida += pilha.pop()
    
    print(saida)