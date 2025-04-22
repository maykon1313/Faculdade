n = int(input())
todos_os_numeros = [0] * (n+1)
alm_pri = 0

for i in range(2, n+1):
    if todos_os_numeros[i] == 2:
        alm_pri = alm_pri + 1
    elif todos_os_numeros[i] == 0:
        for z in range(i, n+1, i):
            todos_os_numeros[z] = todos_os_numeros[z] + 1

print(alm_pri)