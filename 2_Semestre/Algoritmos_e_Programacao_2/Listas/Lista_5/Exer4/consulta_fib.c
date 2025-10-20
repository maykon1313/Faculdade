#include <stdio.h>

int main() {
    int n, sai, i;
    FILE *f;

    f = fopen("30_fib.txt", "r");

    printf("Digite qual a posição do número que você quer (1 a 30): ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        fscanf(f, "%d", &sai);
    }

    printf("%d\n", sai);
    fclose(f);
    return 0;
}