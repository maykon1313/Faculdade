grupos = [ [(0,0), (1,1), (2,2)],
           [(0,0), (2,1), (1,2)],
           [(0,1), (1,2), (2,0)],
           [(0,1), (2,2), (1,0)],
           [(0,2), (1,0), (2,1)],
           [(0,2), (2,0), (1,1)],
           [(0,0), (1,0), (2,0)],
           [(0,1), (1,1), (2,1)],
           [(0,2), (1,2), (2,2)],
           [(0,0), (0,1), (0,2)],
           [(1,0), (1,1), (1,2)],
           [(2,0), (2,1), (2,2)],
           [(0,0), (0,0), (0,0)],
           [(0,1), (0,1), (0,1)],
           [(0,2), (0,2), (0,2)],
           [(1,0), (1,0), (1,0)],
           [(1,1), (1,1), (1,1)],
           [(1,2), (1,2), (1,2)],
           [(2,0), (2,0), (2,0)],
           [(2,1), (2,1), (2,1)],
           [(2,2), (2,2), (2,2)], ]

def maior_soma_grupo(matriz):    
    maior_grupo = None
    maior_soma = 0
    segundo_maior_soma = 0

    for grupo in grupos:
        i1, j1 = grupo[0]       
        i2, j2 = grupo[1]
        i3, j3 = grupo[2]

        elem1 = matriz[i1][j1]
        elem2 = matriz[i2][j2]
        elem3 = matriz[i3][j3]

        if elem1 == 0 or elem2 == 0 or elem3 == 0:
            continue
        
        if i1 == i2 == i3 and j1 == j2 == j3:
            soma_do_grupo = elem1
        else:
            soma_do_grupo = elem1 + elem2 + elem3

        if soma_do_grupo > maior_soma and soma_do_grupo >= 3:
            maior_soma = soma_do_grupo
            maior_grupo = grupo
        elif soma_do_grupo > segundo_maior_soma:
            segundo_maior_soma = soma_do_grupo
        
    if maior_grupo:
        retirar = (maior_soma - segundo_maior_soma) // 3
        
        i1, j1 = maior_grupo[0]       
        i2, j2 = maior_grupo[1]
        i3, j3 = maior_grupo[2]
        retirar = max(1, min(retirar, matriz[i1][j1], matriz[i2][j2], matriz[i3][j3]))
        
        return maior_grupo, retirar
    return None, 0

def grupos_possiveis(matriz):
    cont = 0

    while True:
        grupo, retirar = maior_soma_grupo(matriz)
        if grupo is None:
            break

        i1, j1 = grupo[0]       
        i2, j2 = grupo[1]
        i3, j3 = grupo[2]

        matriz[i1][j1] -= retirar
        matriz[i2][j2] -= retirar
        matriz[i3][j3] -= retirar
        cont += retirar
     
    return cont

while True:
    cartas = int(input())
    if cartas == 0:
        break

    matriz = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    
    for _ in range(cartas):
        num, sim = input().split()
        
        if sim in ["circulo", "circulos"]:
            i = 0
        elif sim in ["triangulo", "triangulos"]:
            i = 1
        else:
            i = 2
        
        if num == "um":
            j = 0
        elif num == "dois":
            j = 1
        else:
            j = 2
            
        matriz[i][j] += 1
    
    resultado = grupos_possiveis(matriz)
    print(f"{resultado}")
