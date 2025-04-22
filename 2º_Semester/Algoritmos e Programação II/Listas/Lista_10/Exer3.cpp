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

void conteudo_minimo(celula *p);
int conteudo_minimoR(celula *p, int posicao, int menor, int *posicao_menor);

int main() {
    celula *cabeca;
    int menor, posicao = 1, posicao_menor = 0;

    cabeca = inicia_cabeca();
    inicia_lista(cabeca);

    conteudo_minimo(cabeca);

    menor = cabeca->seg->conteudo;

    menor = conteudo_minimoR(cabeca->seg, posicao, menor, &posicao_menor);
    printf("A célula com o menor conteúdo é a %dª, com o valor de %d.\n", posicao_menor, menor);

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

    for (i = 10; i > 0; i--) {
        inserir_no_final(i, c);
    }
}

void inserir_no_final(int x, celula *p) {
    celula *nova;

    nova = (celula *) malloc(sizeof(celula));
    nova->conteudo = x;
    nova->seg = NULL;

    while (p->seg != NULL) {
        p = p->seg;
    }
    
    p->seg = nova;
}

void conteudo_minimo(celula *p) {
    int menor = p->seg->conteudo, posicao = 1, posicao_menor;
    p = p->seg;

    while (p != NULL) {
        if (p->conteudo < menor) {
            menor = p->conteudo;
            posicao_menor = posicao;
        }

        p = p->seg;
        posicao++;
    }

    printf("A célula com o menor conteúdo é a %dª, com o valor de %d.\n", posicao_menor, menor);
}

int conteudo_minimoR(celula *p, int posicao, int menor, int *posicao_menor) {
    if (p != NULL) {
        if (p->conteudo < menor) {
            menor = p->conteudo;
            *posicao_menor = posicao;
        }

        posicao++;
        menor = conteudo_minimoR(p->seg, posicao, menor, posicao_menor);
    }

    return menor;
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