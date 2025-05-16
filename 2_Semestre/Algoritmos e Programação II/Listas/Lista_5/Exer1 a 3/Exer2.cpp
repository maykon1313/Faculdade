#include <stdio.h>

int main() {
    int a, b;
    FILE *f;

    printf("Digite os valores para A e B: ");
    scanf("%d %d", &a, &b);
    
    f = fopen("entrada.txt", "r+");
    
    fprintf(f, "%d %d", a, b);

    fclose(f);

    f = fopen("saida.txt", "r+");

    fprintf(f, "%d\n", a+b);

    fclose(f);
    return 0;
}