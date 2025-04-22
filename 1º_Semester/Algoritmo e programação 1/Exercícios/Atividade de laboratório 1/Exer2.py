print("Data de nascimento:")
x, y, z = input().split("/")
print("Data atual:")
a, b, c = input().split("/")

#Idade:
idade = int(c) - int(z)

#Já fez aniversário? (Mês atual maior ou igual ao mês de nascimento)
if b > y:
    #Fez aniversário
    print("Ele tem " + str(idade))
elif b == y:
    #Tem que confirir o dia
    if a < x:
        #Ele não fez
        idade = idade - 1
        print("Ele tem " + str(idade))
    else:
        #Ele fez.
        print("Ele tem " + str(idade))
else:
    #Mês atual menor do que o mês de nascimento.  
    #Ele não fez.
    idade = idade - 1
    print("Ele tem " + str(idade))