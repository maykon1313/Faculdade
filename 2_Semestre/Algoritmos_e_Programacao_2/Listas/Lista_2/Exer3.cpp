#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n, num, **matriz;

    printf("Digite a quantidade de linhas: ");
    scanf("%d", &m);

    printf("Digite a quantidade de colunas: ");
    scanf("%d", &n);

    matriz = (int **) malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matriz[i] = (int *) malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        printf("Digite a %d° linha:\n", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &num);
            matriz[i][j] = num;
        }
    }

    printf("A matriz transposta será:\n");
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return 0;
}
