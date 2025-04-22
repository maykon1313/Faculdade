print("Quantos segundos?")

sec = int(input())
dias = (sec/3600)/24
horas = sec/3600
minutos = sec/60

print("Dias: " + str(dias))
print("Horas: " + str(horas))
print("Minutos: " + str(minutos)) 
print("Segundos: " + str(sec))