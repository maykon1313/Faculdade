print("Salário:")
s = float(input())

if s < 500:
    s = s * 1.3
    print("Novo salário: " + str(s))
else:
    print("Sai fora oportunista.")