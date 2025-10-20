n = int(input())
zero = 0
um = 0
dois = 0
tres = 8

total = n*n*n

menor = n-2
total_menor = menor*menor*menor
zero = total_menor

total = total - total_menor - 8

if total > 0:
    um = ((menor*menor)) * 6
    dois = ((n*n) - (um//6) - 4) * 3

print(zero)
print(um)
print(dois)
print(tres)