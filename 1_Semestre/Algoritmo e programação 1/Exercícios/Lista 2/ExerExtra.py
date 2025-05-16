#Organize 5 valores do menor ao maior:
print("Digite o valor de a:")
a = int(input())
print("Digite o valor de b:")
b = int(input())
print("Digite o valor de c:")
c = int(input())
print("Digite o valor de d:")
d = int(input())
print("Digite o valor de e:")
e = int(input())
 
#Para a posição "a" o menor valor de todos:
if a<=b and a<=c and a<=d and a<=e:
    a = a
elif b<=a and b<=c and b<=d and b<=e:
    aux = a
    a = b
    b = aux
elif c<=b and c<=a and c<=d and c<=e:
    aux = a
    a = c
    c = aux
elif d<=b and d<=c and d<=a and d<=e:
    aux = a
    a = d
    d = aux
else:
    aux = a
    a = e
    e = aux

#Para a posição "b" o menor valor e maior que "a" de todos:
if b<=c and b<=d and b<=e:
    b = b
elif c<=b and c<=d and c<=e:
    aux = b
    b = c
    c = aux
elif d<=b and d<=c and d<=e:
    aux = b
    b = d
    d = aux
else:
    aux = b
    b = e
    e = aux

#Para a posição "c" o menor valor e maior que "b" de todos:
if c<=c and c<=d and c<=e:
    c = c
elif d<=c and d<=e:
    aux = c
    c = d
    d = aux
else:
    aux = c
    c = e
    e = aux

#Para a posição "d" basta confirir "d" e "e":
if d<=e:
    d = d
else:
    aux = d
    d = e
    e = aux

#Para a posição "e" é o valor que sobrou.

print("Para o a: " + str(a) + ", Para o b: " + str(b) + ", Para o c: " + str(c) + ", Para o d: " + str(d) + " e Para o e: " + str(e))