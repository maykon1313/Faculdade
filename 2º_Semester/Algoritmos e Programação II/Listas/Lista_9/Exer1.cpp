#include <stdio.h>
#include <stdlib.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;
int menu();
void inserir_ordenado_entre(int y, celula *p);
void imprimir(celula *p);
celula *busca(int x, celula *p);
void remova_seg(int x, celula *p);
void remove(int x, celula *p);
void remove_tudo(celula *p);
void remove_tudoR(celula *p);


int main() {
    celula c, *lst, *posicao;
    int buscar, opcao, valor;
    bool continua = true;

    c.seg = NULL;
    lst = &c;

    while (continua) {
        opcao = menu();

        switch (opcao) {
            case 1:
                printf("Insira o valor para adicionar de forma ordenada: ");
                scanf("%d", &valor);
                inserir_ordenado_entre(valor, lst);
                break;

            case 2:
                printf("Imprimindo lista:\n");
                imprimir(lst);
                break;

            case 3:
                printf("Qual valor deseja buscar? ");
                scanf("%d", &buscar);
                posicao = busca(buscar, lst);
                if (posicao != NULL) {
                    printf("Valor %d encontrado.\n", buscar);
                } else {
                    printf("Valor %d não encontrado.\n", buscar);
                }
                break;

            case 4:
                printf("Remover o elemento seguinte a qual valor? ");
                scanf("%d", &buscar);
                remova_seg(buscar, lst);
                break;

            case 5:
                printf("Remover qual valor? ");
                scanf("%d", &buscar);
                remove(buscar, lst);
                break;

            case 6:
                printf("Removendo todos os elementos da lista...\n");
                remove_tudo(lst->seg);
                lst->seg = NULL;
                break;

            case 7:
                printf("Removendo todos os elementos da lista (recursão)...\n");
                remove_tudoR(lst->seg);
                lst->seg = NULL;
                break;

            case 9:
                printf("Encerrando o programa.\n");
                continua = false;
                break;

            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    }

    return 0;
}

int menu() {
    int opcao;

    printf("\nO que fazer?\n");
    printf("1 - Inserir ordenado.\n");
    printf("2 - Imprimir.\n");
    printf("3 - Buscar.\n");
    printf("4 - Remover o elemento seguinte.\n");
    printf("5 - Remover elemento.\n");
    printf("6 - Remover tudo.\n");
    printf("7 - Remover tudo por recursão.\n");
    printf("9 - Sair.\n");

    scanf("%d", &opcao);
    return opcao;
}

void inserir_ordenado_entre(int y, celula *p) {
    celula *nova;

    nova = (celula *) malloc(sizeof(celula));

    nova->conteudo = y; 

    while (p->seg != NULL && y > p->seg->conteudo) {
        p = p->seg;
    }

    nova->seg = p->seg;
    p->seg = nova;
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

celula *busca(int x, celula *p) {
    p = p->seg;

    while (p != NULL) {
        if (p->conteudo == x) return p;

        p = p->seg;
    }

    return NULL;
}

void remova_seg(int x, celula *p) {
    celula *q;

    while (p->seg != NULL) {
        if (p->conteudo == x) {
            if (p->seg != NULL) {
                q = p->seg;
                p->seg = q->seg;
                free(q);
            }
            return;
        }
        p = p->seg;
    }

    printf("Valor %d não encontrado ou não há próximo elemento para remover.\n", x);
}


void remove(int x, celula *p) {
    celula *q;

    while (p->seg != NULL) {
        if (p->seg->conteudo == x) {
            q = p->seg;
            p->seg = q->seg;
            free(q);
            return;
        }
        p = p->seg;
    }

    printf("Valor não encontrado.\n");
}

void remove_tudo(celula *p) {
    celula *q;

    while (p != NULL) {
        q = p;
        p = p->seg;
        free(q);
    }
}


void remove_tudoR(celula *p) {
    if (p != NULL) {
        remove_tudoR(p->seg);
        free(p);
    }
}