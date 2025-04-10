a = int(input())
b = int(input())

if b < a:
    a, b = b, a

for num in range(a+1, b):
    if num%5 == 2 or num%5 == 3:
        print(num)