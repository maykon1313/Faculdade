print("Digite o 1° horário:")
a, b, c = input().split(":")
print("Digite o 2° horário:")
x, y, z = input().split(":")

m = int(a) + int(x)
n = int(b) + int(y)
o = int(c) + int(z)

if o >= 60:
    o = o%60
    n = n + ((o - o%60)/60)

if n >= 60:
    n = n%60
    m = m + ((n - n%60)/60)

hora = str(int(m)) + ":" + str(int(n) + ":" + str(o))

print("A soma é: " + hora)