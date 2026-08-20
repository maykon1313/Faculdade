A = list(map(int, input().split()))
B = list(map(int, input().split()))

def subconjunto(A, B):
    i = 0
    while i < len(A):
        if A_nao_presente_B(A[i], B):
            return False
        i += 1
    return True

def A_nao_presente_B(num, B):
    z = 0
    while z < len(B):
        if num == B[z]:
            return False #Presente
        z += 1
    return True #Não está presente

A_em_B = subconjunto(A, B)

if A_em_B:
    print("True.")
else:
    print("False.")

if (len(A) == len(B)) and A_em_B:
    print("Iguais.")
else:
    print("Diferentes.")