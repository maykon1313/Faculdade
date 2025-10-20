def todos_um(dia):
    z = 1
    num = dia[z]
    if num != "1":
        return False
    else:
        z += 1
        while z < len(dia):
            num = dia[z]
            z += 1
            if num != "1":
                return False
        return True

while True:
    try:
        pessoas, datas = input().split()
        n_achou = True

        q = 0
        while q < int(datas):
            dia = input().split()
            if todos_um(dia) and n_achou:
                n_achou = False
                dia_marcado = dia[0]
            q += 1
        
        if n_achou:
            print("Pizza antes de FdI")
        else:
          print(str(dia_marcado))

    except EOFError:
        break
