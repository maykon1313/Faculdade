import random

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

class ArvoreBinaria:
    def __init__(self):
        self.raiz = None

    def inserir(self, valor):
        novo_no = NoArvoreBinaria(valor)
        if self.raiz is None:
            self.raiz = novo_no
        else:
            atual = self.raiz
            while True:
                if valor < atual.info:
                    if atual.esq is None:
                        atual.set_esq(novo_no)
                        break
                    else:
                        atual = atual.esq
                else:
                    if atual.dir is None:
                        atual.set_dir(novo_no)
                        break
                    else:
                        atual = atual.dir

    def busca(self, valor):
        atual = self.raiz
        while atual is not None:
            if valor == atual.info:
                return True
            elif valor < atual.info:
                atual = atual.esq
            else:
                atual = atual.dir
        return False

    def _em_ordem(self, no):
        if no is not None:
            self._em_ordem(no.esq)
            print(no.info, end=" ")
            self._em_ordem(no.dir)

    def em_ordem(self):
        self._em_ordem(self.raiz)
        print()

    def busca_erd(self, no, valor):
        if no is None:
            return False

        if self.busca_erd(no.esq, valor):
            return True
        if no.info == valor:
            return True
        if self.busca_erd(no.dir, valor):
            return True
        return False

    def erd_primeiro(self):
        no = self.raiz
        if no is None:
            return None
        while no.esq is not None:
            no = no.esq
        return no.info

    def erd_sucessor(self, no, valor):
        if no is None:
            return [None, None]
        
        filhos = self.erd_sucessor(no.esq, valor)
        if filhos != [None, None]:
            return filhos
        
        if no.info == valor:
            esq = no.esq.info if no.esq else None
            dir = no.dir.info if no.dir else None
            return [esq, dir]
        
        filhos = self.erd_sucessor(no.dir, valor)
        if filhos != [None, None]:
            return filhos
        
        return filhos

if __name__ == "__main__":
    arvore = ArvoreBinaria()
    
    valores = random.sample(range(1, 21), 20)
    print(f"Sequência dos valores adicionados: {valores}")

    for num in valores:
        arvore.inserir(num)

    if arvore.busca_erd(arvore.raiz, 12):
        print("12 está na árvore.")
    else:
        print("12 não está na árvore.")

    if arvore.busca_erd(arvore.raiz, 21):
        print("21 está na árvore.")
    else:
        print("21 não está na árvore.")

    print("Árvore em ordem:")
    arvore.em_ordem()

    primeiro = arvore.erd_primeiro()
    if primeiro is not None:
        print("Primeiro elemento em ordem:", primeiro)
    else:
        print("A árvore está vazia.")

    filhos = arvore.erd_sucessor(arvore.raiz, 12)
    print(f"Filho esquerdo de 12: {filhos[0]}")
    print(f"Filho direito de 12: {filhos[1]}")
