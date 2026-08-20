#include <stdio.h>
#include <stdlib.h>

struct cel {
    struct cel *ant;
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula* inicializa_lista();
int menu();
void inserir(celula *cabeca, int valor);
void remover(celula *cabeca, int valor);
void buscar(celula *cabeca, int valor);
void imprimir(celula *cabeca);
void liberar(celula *cabeca);

int main() {
    int opcao = 0, valor;
    celula *cabeca = inicializa_lista();

    while (opcao != 9) {
        opcao = menu();
        
        if (opcao == 1) {
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(cabeca, valor);
        } else if (opcao == 2) {
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remover(cabeca, valor);
        } else if (opcao == 3) {
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            buscar(cabeca, valor);
        } else if (opcao == 4) {
            imprimir(cabeca);
        } else if (opcao == 9) {
            printf("Saindo.\n");
            liberar(cabeca);
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}

celula* inicializa_lista() {
    celula *cabeca = (celula*)malloc(sizeof(celula));
    cabeca->seg = cabeca;
    cabeca->ant = cabeca;
    cabeca->conteudo = -1;
    return cabeca;
}

int menu() {
    int opcao;
    
    printf("O que deseja fazer?\n");
    printf("1 - Inserir elemento.\n");
    printf("2 - Remover elemento.\n");
    printf("3 - Buscar elemento.\n");
    printf("4 - Imprimir todos os elementos.\n");
    printf("9 - Sair.\n");
    
    scanf("%d", &opcao);
    return opcao;
}

void inserir(celula *cabeca, int valor) {
    celula *nova = (celula*)malloc(sizeof(celula));
    nova->conteudo = valor;

    nova->seg = cabeca;
    nova->ant = cabeca->ant;
    cabeca->ant->seg = nova;
    cabeca->ant = nova;
}

void remover(celula *cabeca, int valor) {
    celula *p = cabeca->seg;

    while (p != cabeca) {
        if (p->conteudo == valor) {
            p->ant->seg = p->seg;
            p->seg->ant = p->ant;
            free(p);
            return;
        }
        p = p->seg;
    }

    printf("Elemento %d não encontrado.\n", valor);
}

void buscar(celula *cabeca, int valor) {
    int i = 1;
    celula *p = cabeca->seg;

    while (p != cabeca) {
        if (p->conteudo == valor) {
            printf("Elemento %d encontrado na %dª celula.\n", valor, i);
            return;
        }
        p = p->seg;
        i++;
    }

    printf("Elemento %d não encontrado.\n", valor);
}

void imprimir(celula *cabeca) {
    celula *p = cabeca->seg;

    if (p == cabeca) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("Elementos na lista:");
    while (p != cabeca) {
        printf(" %d", p->conteudo);
        p = p->seg;
    }
    printf(".\n");
}

void liberar(celula *cabeca) {
    celula *p = cabeca->seg;
    
    while (p != cabeca) {
        p = p->seg;
        free(p->ant);
    }

    free(cabeca);
}
