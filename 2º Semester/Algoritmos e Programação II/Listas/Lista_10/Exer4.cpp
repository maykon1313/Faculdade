#include <stdio.h>
#include <stdlib.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;
celula *inicia_com_cabeca(bool cabecao);
void inicia_lista(celula *p);
void inserir_no_final(int x, celula *p);
void imprimir(celula *p);

void buscar(celula *c, celula *s);
void busca_ite(int num, celula *p);
void busca_recur(int num, celula *p, int posicao);

int main() {
    celula *cabeca, *sem_cabeca;

    cabeca = inicia_com_cabeca(true);
    inicia_lista(cabeca);

    sem_cabeca = inicia_com_cabeca(false);
    inicia_lista(sem_cabeca);

    buscar(cabeca, sem_cabeca);

    printf("\nLista com cabeça:\n");
    imprimir(cabeca);

    printf("\nLista sem cabeça:\n");
    imprimir(sem_cabeca);
    return 0;
}

celula *inicia_com_cabeca(bool cabecao) {
    celula *cabeca;

    cabeca = (celula *) malloc(sizeof(celula));

    if (cabecao) cabeca->conteudo = -1;
    else cabeca->conteudo = 0;
    cabeca->seg = NULL;

    return cabeca;
}

void inicia_lista(celula *p) {
    int i;

    for (i = 1; i <= 10; i++) {
        if (i == 1 && p->conteudo != -1) p->conteudo = i;
        else inserir_no_final(i, p);
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

void imprimir(celula *p) {
    int posicao = 0;

    if (p->conteudo == -1) {
        printf("Posição(%i): Cabeça.\n", posicao);
        p = p->seg;
        posicao++;
    }

    while (p != NULL) {
        printf("Posição(%d): %d.\n", posicao, p->conteudo);
        p = p->seg;
        posicao++;
    }
}

void buscar(celula *c, celula *s) {
    int num, posicao = 0;

    printf("Qual o valor para buscar?\n");
    scanf("%d", &num);

    printf("\nBusca iterativa em lista com cabeça:\n");
    busca_ite(num, c);

    printf("\nBusca iterativa em lista sem cabeça:\n");
    busca_ite(num, s);

    printf("\nBusca recursiva em lista com cabeça:\n");
    busca_recur(num, c, posicao);

    printf("\nBusca recursiva em lista sem cabeça:\n");
    busca_recur(num, s, posicao);
}

void busca_ite(int num, celula *p) {
    int posicao = 0;

    while (p != NULL) {
        if (p->conteudo == num) {
            printf("O número %d, foi encontrado na %dª celula.\n", num, posicao);
            return;
        }

        p = p->seg;
        posicao++;
    }

    printf("O número %d, não foi encontrado.\n", num);
}

void busca_recur(int num, celula *p, int posicao) {
    if (p != NULL) {
        if (p->conteudo == num) {
            printf("O número %d, foi encontrado na %dª celula.\n", num, posicao);
            return;
        }

        busca_recur(num, p->seg, posicao + 1);
    } else {
        printf("O número %d, não foi encontrado.\n", num);
    }
}