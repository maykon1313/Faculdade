while (True):
    n, k, m = map(int, input().split())
    if (n, k, m) == (0, 0, 0):
        break

    numeros = [i for i in range(1, n+1)]

    saida = ""
    i, j = 0, n-1

    while (numeros):
        i = (i + k - 1) % len(numeros)
        j = (j - m + 1) % len(numeros)
        
        if (len(numeros) > 2):
            if i != j:
                if i < j:
                    saida += "  " + str(numeros[i])
                    saida += "  " + str(numeros[j]) + ","
                    numeros.pop(j)
                    numeros.pop(i)
                    i -= 1
                    j -= 2

                else:
                    saida += "  " + str(numeros[i])
                    saida += "  " + str(numeros[j]) + ","
                    numeros.pop(i)
                    numeros.pop(j)
                    i -= 2
                    j -= 1

            else:
                saida += "  " + str(numeros.pop(i)) + ","
                i -= 1
                j -= 1

        elif (len(numeros) == 1):
            saida += "  " + str(numeros.pop(i))

        else:
            if i < j:
                saida += "  " + str(numeros[i])
                saida += "  " + str(numeros[j])
                numeros.pop(j)
                numeros.pop(i)

            else:
                saida += "  " + str(numeros[i])
                saida += "  " + str(numeros[j])
                numeros.pop(i)
                numeros.pop(j)

    print(saida)
