n = int(input())
i = 1
tem = False

while i < len(str(n))+1:
    if i == 1:
      anterior = int(n)%10
    else:
      atual = (n%(10**i) - n%(10**(i-1)))//10**(i-1)
      if atual == anterior and tem == False:
         tem = True
         num_rep = str(atual) + str(atual)
      anterior = atual 
    i = i + 1

if tem:
   print(str(n) + ", possuí pelo menos dois números iguais consecutivos, " + str(num_rep) + ".")
else:
   print("O número não possuí dois números iguais consecutivos.")