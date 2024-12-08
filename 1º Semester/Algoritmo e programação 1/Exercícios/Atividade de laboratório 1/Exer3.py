#Organize 4 valores do menor ao maior:
print("Digite o valor de a:")
a = int(input())
print("Digite o valor de b:")
b = int(input())
print("Digite o valor de c:")
c = int(input())
print("Digite o valor de d:")
d = int(input())
 
#Para a posição "a" o menor valor de todos:
if a>=b and a>=c and a>=d:
    a = a
elif b>=a and b>=c and b>=d:
    aux = a
    a = b
    b = aux
elif c>=b and c>=a and c>=d:
    aux = a
    a = c
    c = aux
else:
    aux = a
    a = d
    d = aux

#Para a posição "b" o menor valor e maior que "a" de todos:
if b>=c and b>=d:
    b = b
elif c>=b and c>=d:
    aux = b
    b = c
    c = aux
else:
    aux = b
    b = d
    d = aux


#Para a posição "c" o menor valor e maior que "b" de todos:
if c>=d:
    c = c
else:
    aux = c
    c = d
    d = aux

#Para a posição "d" é o valor que sobrou.

print("Para o a: " + str(a) + ", Para o b: " + str(b) + ", Para o c: " + str(c) + ", Para o d: " + str(d))