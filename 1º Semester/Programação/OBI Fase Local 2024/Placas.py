placa = input()

numeros = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

if (len(placa) == 8) and (placa[0] not in numeros) and (placa[1] not in numeros) and (placa[2] not in numeros) and (placa[3] == "-") and (placa[4] in numeros) and (placa[5] in numeros) and (placa[6] in numeros) and (placa[7] in numeros):
    print(1)
elif (len(placa) == 7) and (placa[0] not in numeros) and (placa[1] not in numeros) and (placa[2] not in numeros) and (placa[3] in numeros) and (placa[4] not in numeros) and (placa[5] in numeros) and (placa[6] in numeros):
    print(2)
else:
    print(0)