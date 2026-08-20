
hora_parti = 19
minu_parti = 00

hora_final = 5
minu_final = 18

if minu_final > 60:
    minu_final = minu_final - 60
    hora_final = hora_final + 1

if hora_final >= 24:
    div = hora_final//24
    hora_final = hora_final - (24*div)

if minu_final > 9:
    resposta = str(hora_final) + ":" + str(minu_final)
else:
    resposta = str(hora_final) + ":0" + str(minu_final)
print(resposta)