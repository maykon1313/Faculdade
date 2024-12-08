#include <stdio.h>
#include <stdlib.h>

struct celula
{
    struct celula *ant;
    int valor;
    struct celula *seg;
};

typedef struct celula c;

void enfilerar(int num, celula *c);
void desenfilerar(celula *c);
void printar(celula *p);

int main(){
    c *cabeca;
    cabeca = (c *) malloc(sizeof(c));
    cabeca->ant = cabeca;
    cabeca->valor = -1;
    cabeca->seg = cabeca;

    enfilerar(33, cabeca);
    enfilerar(7, cabeca);
    enfilerar(11, cabeca);
    printar(cabeca);
    printf("\n");
    
    desenfilerar(cabeca);
    desenfilerar(cabeca);
    desenfilerar(cabeca);
    desenfilerar(cabeca);
    printar(cabeca);
    printf("\n");
    
    enfilerar(2, cabeca);
    printar(cabeca);
    printf("\n");
    
    return 0;
}

// Adiciona ao fim
void enfilerar(int num, celula *c){
    celula *nova;
    
    nova = (celula *) malloc(sizeof(celula));
    
    nova->valor = num;
    
    c->ant->seg = nova;
    nova->seg = c;
    
    nova->ant = c->ant;
    c->ant = nova;
}

// Remove o primeiro
void desenfilerar(celula *c){
    celula *velha = c->seg;
    
    if (c->ant == c){
        printf("Lista vazia.\n");
        return;
    }
    
    c->seg = velha->seg;
    velha->seg->ant = c;
    
    free(velha);
}

// Printa todos os valores da lista
void printar(celula *p){
    celula *cabeca = p;
    int i = 1;
    
    if (p->seg == p) {
        printf("Lista vazia.\n");
        return;
    }
    
    p = p->seg;
    while (p != cabeca) {
        printf("Celula %d: %d.\n", i, p->valor);
        p = p->seg;
        i++;
    }
}









