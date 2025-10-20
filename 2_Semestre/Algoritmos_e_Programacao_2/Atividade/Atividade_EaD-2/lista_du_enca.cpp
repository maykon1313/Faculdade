#include <stdio.h>
#include <stdlib.h>

struct celula
{
    struct celula *ant;
    int valor;
    struct celula *seg;
};

typedef struct celula c;

c *iniciar_cabeca() {
    c *cabeca;

    cabeca = (c *) malloc(sizeof(c));

    cabeca->ant = cabeca;
    cabeca->valor = -1;
    cabeca->seg = cabeca;

    return cabeca;
}

void inserir(c *cabeca, int num) {
    c *nova;

    nova = (c *) malloc(sizeof(c));

    nova->ant = cabeca;
    nova->valor = num;
    nova->seg = cabeca->seg;

    cabeca->seg->ant = nova;
    cabeca->seg = nova;
}

void remover(c *cabeca, int num) {
    c *ponteiro = cabeca->seg;

    while (ponteiro != cabeca) {
        if (ponteiro->valor == num) break;
        ponteiro = ponteiro->seg;
    }

    ponteiro->ant->seg = ponteiro->seg;
    ponteiro->seg->ant = ponteiro->ant;

    free(ponteiro);
}

c *buscar(c *cabeca, int num) {
    c *ponteiro = cabeca->seg;

    while (ponteiro != cabeca) {
        if (ponteiro->valor == num) return ponteiro;
        ponteiro = ponteiro->seg;
    }

    return NULL;
}

void imprimir(c *cabeca) {
    c *ponteiro = cabeca->seg;
    int i = 1;

    while (ponteiro != cabeca) {
        printf("%dº célula: %d.\n", i, ponteiro->valor);
        ponteiro = ponteiro->seg;
        i++;
    }

    if (i == 1) printf("Lista vazia.\n");
}

void free_lista(c *cabeca){
    c *ponteiro = cabeca;

    while (ponteiro != NULL){
        c *temp = ponteiro;
        ponteiro = ponteiro->seg;
        free(temp);
    }
}

int main() {
    c *cabeca, *endereco;

    cabeca = iniciar_cabeca();

    printf("Estado inicial:\n");
    imprimir(cabeca);
    inserir(cabeca, 3);
    inserir(cabeca, 2);
    inserir(cabeca, 1);

    printf("\nNovo estado:\n");
    imprimir(cabeca);

    printf("\nNovo estado:\n");
    remover(cabeca, 2);
    imprimir(cabeca);

    printf("\nNovo estado:\n");
    remover(cabeca, 1);
    imprimir(cabeca);

    endereco = buscar(cabeca, 3);
    printf("O número três está localizado nesse endereço: %p.\n", endereco);
    printf("O valor nesse endereço: %d.\n", endereco->valor);

    free_lista(cabeca);
    return 0;
}
