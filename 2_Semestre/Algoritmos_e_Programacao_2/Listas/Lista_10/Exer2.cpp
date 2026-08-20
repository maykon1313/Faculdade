#include <stdio.h>
#include <stdlib.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;
celula *inicia_cabeca();
void inicia_lista(celula *c);
void inserir_no_final(int x, celula *p);
void imprimir(celula *p);

celula *unir(celula *cabeca1, celula *cabeca2);

int main() {
    celula *cabeca1, *cabeca2, *cabeca3;

    cabeca1 = inicia_cabeca();
    inicia_lista(cabeca1);

    cabeca2 = inicia_cabeca();
    inicia_lista(cabeca2);

    cabeca3 = unir(cabeca1, cabeca2);

    imprimir(cabeca3);
    return 0;
}

celula *inicia_cabeca() {
    celula *cabeca;

    cabeca = (celula *) malloc(sizeof(celula));
    cabeca->conteudo = -1;
    cabeca->seg = NULL;

    return cabeca;
}

void inicia_lista(celula *c) {
    int i;

    for (i = 1; i <= 10; i++) {
        inserir_no_final(i, c);
    }
}

void inserir_no_final(int x, celula *p) {
    celula *nova;

    nova = (celula *) malloc(sizeof(celula));

    while (p->seg != NULL) {
        p = p->seg;
    }

    nova->conteudo = x;
    nova->seg = NULL;
    p->seg = nova;
}

celula *unir(celula *p1, celula *p2) {
    celula *inicio = p1;

    while (p1->seg != NULL) {
        p1 = p1->seg;
    }

    p1->seg = p2->seg;
    return inicio;
}

void imprimir(celula *p) {
    int posicao = 1;
    p = p->seg;

    while (p != NULL) {
        printf("Posição(%d): %d.\n", posicao, p->conteudo);
        p = p->seg;
        posicao++;
    }
}