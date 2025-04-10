def maior_primo(num):
    if num == 2 or num == 3:
        return num
    
    for n in range(num, 1, -1):
        n_div = True
        for div in range(2, int(n**(1/2))+1):
            if n%div == 0:
                n_div = False
                break
        
        if n_div: 
            return n

for valor in range(2, 12):
    contador = 0
    while valor >= 2:
        valor -= maior_primo(valor)
        contador += 1

    if valor == 1:
        contador += 1

    print(contador)


