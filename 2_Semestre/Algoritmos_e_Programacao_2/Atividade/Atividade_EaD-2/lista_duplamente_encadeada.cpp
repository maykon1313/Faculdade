#include <stdio.h>
#include <stdlib.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;
void inserir_ao_final(int x, celula *p);
void inserir_ordenado_entre(int y, celula *p);
void imprimir(celula *p);
celula *busca(int x, celula *p);

int main() {
    celula c, *lst;
    int buscar; 
    celula *posicao;

    c.seg = NULL;
    lst = &c;

    inserir_ordenado_entre(1, lst);
    inserir_ordenado_entre(2, lst);
    inserir_ordenado_entre(5, lst);
    inserir_ordenado_entre(7, lst);

    printf("Burcar qual número, meu patrão?\n");
    scanf("%d", &buscar);

    posicao = busca(buscar, lst);

    printf("Posição dele: %d.\n", posicao);

    imprimir(lst);
    return 0;
}

void inserir_ao_final(int x, celula *p) {
    celula *nova;

    nova = (celula *) malloc(sizeof(celula));

    nova->conteudo = x;
    nova->seg = NULL;

    while (p->seg != NULL) {
        p = p->seg;
    }

    p->seg = nova;
}

void inserir_ordenado_entre(int y, celula *p) {
    celula *nova;

    nova = (celula *) malloc(sizeof(celula));

    nova->conteudo = y;

    while (p->seg != NULL && y > p->conteudo) {
        p = p->seg;
    }

    nova->seg = p->seg;
    p->seg = nova;
}

void imprimir(celula *p) {
    int i = 1;
    p = p->seg;

    while (p != NULL) {
        printf("Posição(%d): %d.\n", i, p->conteudo);
        p = p->seg;
        i++;
    }
}

celula *busca(int x, celula *p) {
    celula *temp;
    temp = p->seg;

    while (temp != NULL) {
        if (temp->conteudo == x) return temp;

        temp = temp->seg;
    }

    return NULL;
}