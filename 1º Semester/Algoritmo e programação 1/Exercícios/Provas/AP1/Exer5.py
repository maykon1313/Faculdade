print("Qual o valor do troco?")
troco = int(input())

nota100 = int(troco/100)
nota50 = int((troco % 100)/50)
nota10 = int((troco % 50)/10)
nota5 = int((troco % 10)/5)
nota1 = int((troco % 5)/1)

print("Notas de 100: " + str(nota100))
print("Notas de 50: " + str(nota50))
print("Notas de 10: " + str(nota10))
print("Notas de 5: " + str(nota5))
print("Notas de 1: " + str(nota1))