numero = int(input())

digito1 = numero%10

while numero != 0:
    digitofinal = numero
    numero = numero//10

if digito1 == digitofinal:
    print("O primeiro e o último digitos são iguais.")
else:
    print("O primeiro e o último não são iguais.")