print("Valor da aplicação mensal:")
p = float(input())
print("Taxa de rendimento:")
i = float(input())
print("Número de meses:")
n = float(input())

saldo = ((p * ((1 + i)**n)) - 1)/i

print("O rendimento foi: " + str(saldo))