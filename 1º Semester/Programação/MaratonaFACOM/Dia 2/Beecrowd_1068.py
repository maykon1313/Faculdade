while True:
    try: 
        expressao = input()
        abre = 0
        confirmacao = True

        for caracter in expressao:
            if caracter == "(":
                abre = abre + 1
            elif caracter == ")":
                if abre > 0:
                    abre = abre - 1
                else:
                    confirmacao = False
                    break

        if abre == 0 and confirmacao == True:
            print("correct")
        else:
            print("incorrect")
    except EOFError:
        break