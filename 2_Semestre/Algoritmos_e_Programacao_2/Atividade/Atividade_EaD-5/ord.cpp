#include <stdio.h>
#include <stdlib.h>

struct celula 
{
    struct celula *ant;
    int valor;
    struct celula *seg;
};  

typedef struct celula c;

c *iniciar_cabeca(c *cabeca) {
    cabeca = (c *) malloc(sizeof(c));

    cabeca->ant = NULL;
    cabeca->valor = -1;
    cabeca->seg = NULL;

    return cabeca;
}

void bubble_sort(c *cabeca) {
    c *ponteiro = cabeca->seg, *ultima_cel = NULL;
    int aux, houve_troca = 1;

    while (houve_troca) {
        houve_troca = 0;

        ponteiro = cabeca->seg;
        while (ponteiro->seg != NULL && ponteiro->seg != ultima_cel) {
            if (ponteiro->valor > ponteiro->seg->valor) {
                aux = ponteiro->valor;
                ponteiro->valor = ponteiro->seg->valor;
                ponteiro->seg->valor = aux;

                houve_troca = 1;
            }
            ponteiro = ponteiro->seg;
        }
        ultima_cel = ponteiro;
    }
}

void selection_sort(c *cabeca) {
    c *atual = cabeca->seg, *menor_endereco, *ponteiro;
    int aux;

    while (atual->seg != NULL) {
        menor_endereco = atual;
        ponteiro = atual->seg;

        while (ponteiro != NULL) {
            if (ponteiro->valor < menor_endereco->valor) {
                menor_endereco = ponteiro;
            }

            ponteiro = ponteiro->seg;
        }

        aux = atual->valor;
        atual->valor = menor_endereco->valor;
        menor_endereco->valor = aux;

        atual = atual->seg;
    }
}

void inserir(c *cabeca, int num) {
    c *ponteiro = cabeca, *nova;

    while (ponteiro->seg != NULL) ponteiro = ponteiro->seg;

    nova = (c *) malloc(sizeof(c));

    nova->ant = ponteiro;
    nova->valor = num;
    nova->seg = NULL;

    ponteiro->seg = nova;
}

void criar_lista(c *cabeca) {
    int num;

    scanf("%d", &num);
    while (num != -1) {
        inserir(cabeca, num);
        scanf("%d", &num);
    }
}

int lista_vazia(c * cabeca) {
    if (cabeca->seg == NULL) return 1;
    else return 0;
}

void imprimir(c *cabeca) {
    c *ponteiro = cabeca->seg;

    printf("Lista: ");
    while (ponteiro != NULL) {
        printf("%d ", ponteiro->valor);
        ponteiro = ponteiro->seg;
    }

    printf("\n");
}

void free_lista(c *cabeca) {
    c *ponteiro = cabeca->seg;

    while (ponteiro != NULL) {
        c *temp = ponteiro;
        ponteiro = ponteiro->seg;
        free(temp);
    }
}

void central_bubble(c *cabeca) {
    cabeca = iniciar_cabeca(cabeca);
    criar_lista(cabeca);

    if (lista_vazia(cabeca)) {
        printf("\nLista vazia.\n");
    } else {
        printf("\nAntes de ordenar:\n");
        imprimir(cabeca);
        
        bubble_sort(cabeca);

        printf("\nDepois de ordenar:\n");
        imprimir(cabeca);
    }

    free_lista(cabeca);
}

void central_selection(c *cabeca) {
    cabeca = iniciar_cabeca(cabeca);
    criar_lista(cabeca);

    if (lista_vazia(cabeca)) {
        printf("\nLista vazia.\n");
    } else {
        printf("\nAntes de ordenar:\n");
        imprimir(cabeca);
        
        selection_sort(cabeca);

        printf("\nDepois de ordenar:\n");
        imprimir(cabeca);
    }

    free_lista(cabeca);
}

int main() {
    c *cabeca;

    printf("Bubble sort (-1 para a inserção a lista):\n");
    central_bubble(cabeca);

    printf("\nSelection sort (-1 para a inserção a lista):\n");
    central_selection(cabeca);

    return 0;
}
