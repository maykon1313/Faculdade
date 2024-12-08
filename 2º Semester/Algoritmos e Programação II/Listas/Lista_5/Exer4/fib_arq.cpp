#include <stdio.h>

int main() {
    int a = 1, b = 1, i, aux;
    FILE *f;

    f = fopen("30_fib.txt", "w");

    fprintf(f, "%d %d ", a, b);

    for (i = 0; i < 30; i++) {
        aux = a;
        a = b;
        b = b + aux;
        fprintf(f, "%d ", b);
    }

    fclose(f);
    return 0;
}