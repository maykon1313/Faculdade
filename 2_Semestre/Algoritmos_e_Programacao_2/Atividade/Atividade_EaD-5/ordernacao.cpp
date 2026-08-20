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
void inserir(celula *ponteiro, int valor);
celula* buscar_menor(celula *ponteiro);
void bubble_sort(celula *ponteiro);
void selection_sort(celula *ponteiro);
void imprimir(celula *ponteiro);
void liberar(celula *ponteiro);

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
            bubble_sort(cabeca);
            imprimir(cabeca);
            
        } else if (opcao == 3) {
            selection_sort(cabeca);
            imprimir(cabeca);

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
    if (cabeca == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    cabeca->seg = NULL;
    cabeca->ant = NULL;
    cabeca->conteudo = -1;
    return cabeca;
}

int menu() {
    int opcao;
    
    printf("O que deseja fazer?\n");
    printf("1 - Inserir elemento.\n");
    printf("2 - Bubble Sort.\n");
    printf("3 - Selection Sort.\n");
    printf("4 - Imprimir todos os elementos.\n");
    printf("9 - Sair.\n");
    
    scanf("%d", &opcao);
    return opcao;
}

void inserir(celula *ponteiro, int valor) {
    celula *nova = (celula*)malloc(sizeof(celula));
    if (nova == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    nova->conteudo = valor;
    nova->seg = NULL;

    while (ponteiro->seg != NULL) {
        ponteiro = ponteiro->seg;
    }

    ponteiro->seg = nova;
    nova->ant = ponteiro;
}

celula* buscar_menor(celula *ponteiro) {
    celula *menor_endereco = ponteiro;
    int menor = menor_endereco->conteudo;

    ponteiro = ponteiro->seg;

    while (ponteiro != NULL) {
        if (ponteiro->conteudo < menor) {
            menor_endereco = ponteiro;
            menor = ponteiro->conteudo;
        }
        ponteiro = ponteiro->seg;
    }
    return menor_endereco;
}

void bubble_sort(celula *ponteiro) {
    int trocou = 1;
    celula *atual;
    celula *lptr = NULL;

    if (ponteiro->seg == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    while (trocou) {
        trocou = 0;
        atual = ponteiro->seg;

        while (atual->seg != lptr) {
            if (atual->conteudo > atual->seg->conteudo) {
                int aux = atual->conteudo;
                atual->conteudo = atual->seg->conteudo;
                atual->seg->conteudo = aux;
                trocou = 1;
            }
            atual = atual->seg;
        }
        lptr = atual;
    }
}

void selection_sort(celula *ponteiro) {
    celula *atual = ponteiro->seg;
    celula *menor_endereco;
    int aux;

    if (ponteiro->seg == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    while (atual != NULL) {
        menor_endereco = buscar_menor(atual);
        if (menor_endereco != atual) {
            aux = atual->conteudo;
            atual->conteudo = menor_endereco->conteudo;
            menor_endereco->conteudo = aux;
        }
        atual = atual->seg;
    }
}

void imprimir(celula *ponteiro) {
    celula *p = ponteiro->seg;

    if (p == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("Elementos na lista:");
    while (p != NULL) {
        printf(" %d", p->conteudo);
        p = p->seg;
    }
    printf(".\n");
}

void liberar(celula *ponteiro) {
    celula *p = ponteiro->seg;
    celula *temp;
    
    while (p != NULL) {
        temp = p;
        p = p->seg;
        free(temp);
    }

    ponteiro->seg = NULL;
    free(ponteiro);
}
