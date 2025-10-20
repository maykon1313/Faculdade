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

int conte_celulas(celula *p);

int main() {
    celula *cabeca;
    int celulas;

    cabeca = inicia_cabeca();
    inicia_lista(cabeca);

    celulas = conte_celulas(cabeca);

    imprimir(cabeca);
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

int conte_celulas(celula *p) {
    int celulas = 0;

    while (p != NULL) {
        p = p->seg;
        celulas++;
    }

    printf("São %d celulas (com a cabeça).\n", celulas);
    return celulas;
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