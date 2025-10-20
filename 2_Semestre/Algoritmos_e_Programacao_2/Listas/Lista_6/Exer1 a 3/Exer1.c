#include <stdio.h>

int main() {
    int a, b;
    FILE *f;

    f = fopen("entrada.dat", "wb");

    printf("Digite os valores de A e B: ");
    scanf("%d %d", &a, &b);

    fprintf(f, "%d %d ", a, b);

    fclose(f);
    return 0;
}