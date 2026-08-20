#include <stdio.h>
#include <stdlib.h>
int main() {
    int m, n, num, soma = 0, linhas_nula = 0, colunas_nula = 0, **matriz, i;

    printf("Digite a quantidade de linhas: ");
    scanf("%d", &m);

    printf("Digite a quantidade de colunas: ");
    scanf("%d", &n);

    matriz = (int **) malloc(m * sizeof(int *));
    for (i = 0; i < m; i++){
        matriz[i] = (int *) malloc(n * sizeof(int));
    }

    for (int j = 0; j < m; j++) {
        printf("Digite a %d° linha:\n", j+1);
        for (int i = 0; i < n; i++) {
            scanf("%d", &num);
            matriz[j][i] = num;
        }
    }

    for (int j = 0; j < m; j++) {
        soma = 0;
        for (int i = 0; i < n; i++) {
            soma += matriz[j][i];
        }
        if (soma == 0) {
            linhas_nula += 1;
        }
    }

    for (int i = 0; i < m; i++) {
        soma = 0;
        for (int j = 0; j < n; j++) {
            soma += matriz[j][i];
        }
        if (soma == 0) {
            colunas_nula += 1;
        }
    }

    printf("A quantidade de linhas nulas é: %d.\n", linhas_nula);
    printf("A quantidade de colunas nulas é: %d.\n", colunas_nula);

    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return 0;
}