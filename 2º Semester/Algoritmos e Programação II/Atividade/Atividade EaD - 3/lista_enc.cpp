#include <stdio.h>
#include <stdlib.h>

struct celula
{
    int valor;
    struct celula *seg;
};

typedef struct celula c;

c *iniciar_cabeca() {
    c *cabeca;

    cabeca = (celula *) malloc(sizeof(celula));

    cabeca->valor = -1;
    cabeca->seg = NULL;

    return cabeca;
}

void enfilerar(c *cabeca, int num){
    c *nova, *ponteiro = cabeca;

    nova = (c *) malloc(sizeof(c));

    while (ponteiro->seg != NULL) {
        ponteiro = ponteiro->seg;
    }

    nova->valor = num;
    ponteiro->seg = nova;
    nova->seg = NULL;
}

void desenfilerar(c *cabeca){
    c *ponteiro = cabeca->seg;

    cabeca->seg = ponteiro->seg; 
    
    free(ponteiro);
}

void imprimir_primeiro(c *cabeca){
    if (cabeca->seg == NULL) { 
        printf("Empty!");
        return;
    }

    printf("%d\n", cabeca->seg->valor);
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
    c *cabeca;
    int casos, escolha, num;

    cabeca = iniciar_cabeca();

    scanf("%d", &casos);
    while (casos > 0) {
        scanf("%d", &escolha);

        if (escolha == 1) {
            scanf("%d", &num);
            enfilerar(cabeca, num);
        } else if (escolha == 2) {
            desenfilerar(cabeca);
        } else {
            imprimir_primeiro(cabeca);
        }
        casos--;
    }

    free_lista(cabeca);
    return 0;
}
