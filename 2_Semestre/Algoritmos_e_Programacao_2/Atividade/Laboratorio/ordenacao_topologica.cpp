#include <stdio.h>
#include <stdlib.h>

/* Definições de tipos */
struct cel {
    int contador;
    struct cel *seg;
};

typedef struct cel celula;

/* Protótipos */
celula *inicialize(int n, int m);
void ordene_topologicamente(int n, int m);

int main() {
    int n, m;

    // Leia n (número de objetos)
    printf("n:\n");
    scanf("%d", &n);

    // Leia m (número de pares)
    printf("m:\n");
    scanf("%d", &m);

    ordene_topologicamente(n, m);

    return 0;
}

celula *inicialize(int n, int m) {
    int i;
    celula *cb;

    // Alocar um vetor de n células cabeça
    cb = (celula *)malloc(sizeof(celula) * (n + 1));

    // Inicializar as n listas
    for (i = 0; i <= n; i++) {
        cb[i].contador = 0;
        cb[i].seg = NULL;
    }

    for (i = 1; i <= m; i++) {
        celula *p;
        int j, k;

        // Leia o par (j, k) - j precede k
        scanf("%d%d", &j, &k);

        // Crie uma célula e inicialize com o sucessor k
        p = (celula *)malloc(sizeof(celula));
        p->contador = k;

        // Adicione na lista j, que contém os sucessores de j
        p->seg = cb[j].seg;
        cb[j].seg = p;

        // Incrementa o contador de k
        cb[k].contador += 1;
    }
    return cb;
}

void ordene_topologicamente(int n, int m) {
    celula *cb;
    int i, fim, objeto, indice;

    cb = inicialize(n, m);
    fim = 0;
    cb[0].contador = 0;

    // Buscar objetos sem predecessores
    for (i = 1; i <= n; i++) {
        if (cb[i].contador == 0) {
            cb[fim].contador = i;
            fim = i;
        }
    }

    objeto = cb[0].contador;
    while (objeto != 0) {
        celula *p;

        printf("%d -> ", objeto); // Saída do objeto
        p = cb[objeto].seg;       // p recebe a lista do objeto

        while (p != NULL) {
            // Armazene em índice o contador da célula (sucessor)
            indice = p->contador;

            // Decrementa o contador do índice
            cb[indice].contador -= 1;

            // Se o índice não possui mais predecessores
            if (cb[indice].contador == 0) {
                cb[fim].contador = indice;
                fim = indice;
            }
            p = p->seg;
        }
        // Objeto recebe o próximo objeto na sequência
        objeto = cb[objeto].contador;
    }
    printf("FIM\n");
}
