n_arv1 = int(input())
arv_canhota = [[] for _ in range(n_arv1 + 1)]
for _ in range(n_arv1):
    num, left, mid = map(int, input().split())

    arv_canhota[num] = [left, mid, 0]

n_arv2 = int(input())
arv_destra = [[] for _ in range(n_arv2 + 1)]
for _ in range(n_arv2):
    num, mid, right = map(int, input().split())

    arv_destra[num] = [0, mid, right]

# Contagem da sequẽncia da árvore esquerda pela raiz
no_meio = arv_canhota[1][1]
seq_raiz_e = 1
while no_meio != 0:
    no_meio = arv_canhota[no_meio][1]
    seq_raiz_e += 1

# Contagem da sequẽncia da árvore direita pela raiz
no_meio = arv_destra[1][1]
seq_raiz_d = 1
while no_meio != 0:
    no_meio = arv_destra[no_meio][1]
    seq_raiz_d += 1

# Contagem da sequẽncia da árvore esqueda pelos nós
seq_e = 0
for i in range(2, n_arv1+1):
    no_meio = arv_canhota[i][1]
    arv_canhota[i][1] = 0 # Evitar repetição, não é necessário revisitar a árvore.
    aux_seq_e = 1
    while no_meio != 0:
        anterior = no_meio 
        no_meio = arv_canhota[no_meio][1]
        arv_canhota[anterior][1] = 0
        aux_seq_e += 1

    seq_e = max(seq_e, aux_seq_e)

# Contagem da sequẽncia da árvore esqueda pelos nós 
seq_d = 0
for i in range(2, n_arv2+1):
    no_meio = arv_destra[i][1]
    arv_destra[i][1] = 0 # Evitar repetição, não é necessário revisitar a árvore.
    aux_seq_d = 1
    while no_meio != 0:
        anterior = no_meio 
        no_meio = arv_destra[no_meio][1]
        arv_destra[anterior][1] = 0
        aux_seq_d += 1

    seq_d = max(seq_d, aux_seq_d)

# Calcula a maior intersecção, sem que a árvore esquerda fique a direita da árvore direta, ou vise-versa.
interseccao = max(min(seq_e, seq_raiz_d), min(seq_d, seq_raiz_e), min(seq_raiz_e, seq_raiz_d))

resultado = n_arv1 + n_arv2 - interseccao

print(resultado)