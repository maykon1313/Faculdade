import sympy 
n = int(input())

def primo(z):
    j = 2
    if z == 0 or z == 1:
        return False
    while j < (z):
        if z%j == 0:
            return False
        j = j + 1
    return True

for i in range(n):
    x = int(input())
    a = x//2
    b = a + 1
    while (a != 0) and (primo(a) or primo(b)):
        a = a - 1
        b = b + 1
    if a == 0:
        print(-1)
    else:
        print(a, b)