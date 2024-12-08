e,v = map(int, input().split())

hora = e//v
minutos = int(((e/v) - (hora)) * (60))

hora_parti = 19
minu_parti = 00

hora_final = hora + hora_parti
minu_final = minutos + minu_parti

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