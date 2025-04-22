def e_primo(num):
    for i in range(2, 1 + int(num**(1/2))):
        if num%i == 0:
            return False
    return True

casos = int(input())

for _ in range(casos):
    num = int(input())

    if e_primo(num):
        print(f"{num} eh primo")
    else:
        print(f"{num} nao eh primo")
