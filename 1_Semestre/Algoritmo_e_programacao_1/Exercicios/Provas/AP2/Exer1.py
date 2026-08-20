print("Digite um valor entre 1 até 9 para 'N'.")
n = int(input())
print("Digite um valor entre 1 até 5 para 'M'.")
m = int(input())

resu = n**m

if resu < 10:
    print("O resultado possuí 1 dígitos.")
elif resu < 100:
    print("O resultado possuí 2 dígitos.")
elif resu < 1000:
    print("O resultado possuí 3 dígitos.")
elif resu < 10000:
    print("O resultado possuí 4 dígitos.")
else:
    print("O resultado possuí 5 dígitos.")

print("E o resultado foi: " + str(resu))