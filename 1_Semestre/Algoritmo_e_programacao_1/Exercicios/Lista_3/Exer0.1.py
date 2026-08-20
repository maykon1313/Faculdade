n = int(input())
i = 0

while i < n:
    z = 1 + (i)
    i = i + 1
    if z%2 == 0:
        print(str(z) + " é par.")
    else:
        print(str(z) + " é ímpar.")