#a)
a = int(input())
b = int(input())

if a < b:
    aux = a
    a = b
    b =  aux

def MDC(a,b):
    resto = a%b
    while resto != 0:
            a = b
            b = resto
            resto = a%b
    return b

print(MDC(a, b))

#b)
n = int(input())
numeros = 2
x = int(input())
y = int(input())

mdc = MDC(x,y)

while numeros != n:
     z = int(input())
     mdc = MDC(mdc, z)
     numeros = numeros + 1

print(int(mdc))