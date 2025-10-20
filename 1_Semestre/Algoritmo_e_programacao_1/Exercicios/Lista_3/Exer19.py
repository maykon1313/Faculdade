n = int(input())
i = 1
somas = 0

while i <= n:
    somas = somas + i/(n - (i-1))
    i = i + 1

print(str(somas))