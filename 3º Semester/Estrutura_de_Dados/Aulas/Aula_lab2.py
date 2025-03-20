class NoArvoreBinaria:
    def __init__(self, info, pai=None, esq=None, dir=None):
        self.info = info
        self.pai = pai
        self.esq = esq
        self.dir = dir

    def __str__(self):
        return f'No(info={self.info})'

    def set_esq(self, no):
        self.esq = no
        if no is not None:
            no.pai = self

    def set_dir(self, no):
        self.dir = no
        if no is not None:
            no.pai = self

def busca_insercao(raiz, no):
    if raiz is None:
        return no

    ptr_aux = raiz
    anterior = None
    direcao = None

    while ptr_aux is not None:
        anterior = ptr_aux
        if no.info > ptr_aux.info:
            ptr_aux = ptr_aux.dir
            direcao = 1
        else:
            ptr_aux = ptr_aux.esq
            direcao = 0

    if direcao:
        anterior.dir = no
    else:
        anterior.esq = no

    no.pai = anterior
    return raiz

def busca(raiz, num):
    if raiz is None:
        return False
    
    ptr_aux = raiz
    while ptr_aux is not None:
        if num == ptr_aux.info: return True

        if num > ptr_aux.info:
            ptr_aux = ptr_aux.dir
        else:
            ptr_aux = ptr_aux.esq

def em_ordem(no):
    if no is not None:
        em_ordem(no.esq)
        print(no.info, end=" ")
        em_ordem(no.dir)

def busca_erd(no, num):
    achou = False
    if no is not None:    
        achou = busca_erd(no.esq, num)

        if (no.info == num): return True

        if not achou:
            achou = busca_erd(no.dir, num)
    
    return achou

def erd_primeiro(raiz):
    ptr_aux = raiz

    while ptr_aux.esq is not None:
        ptr_aux = ptr_aux.esq

    print(ptr_aux.info)

def main():
    raiz = NoArvoreBinaria(1)
    for i in range(2, 20 + 1):
        no = NoArvoreBinaria(i)
        raiz = busca_insercao(raiz, no)

    if (busca_erd(raiz, 12)): print("12 está na árvore.") 
    else: print("12 não está na árvore.")

    if (busca_erd(raiz, 21)): print("21 está na árvore.") 
    else: print("21 não está na árvore.")

    print("Árvore em ordem:")
    em_ordem(raiz)
    print()

    erd_primeiro(raiz)

    return 0

main()
