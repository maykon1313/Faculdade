#include <stdio.h>

int potencia(int x, int i) {
    int aux = 1, j;

    for (j = 0; j < i; j++) {
        aux = aux * x;
    }

    return aux;
}

int fatorial(int i) {
    int aux = 1;

    while (i > 0) {
        aux = aux * i;
        i -= 1;
    }

    return aux;
}


double e_exp(int x, int i) {
    if (i > 30) return 0;
    else return ((double) potencia(x, i)/ fatorial(i)) + e_exp(x, i+1);
}

int main() {
    int x;
    double a;

    scanf("%d", &x);

    a = 1 + x + e_exp(x, 2);

    printf("Estimativa de e: %.8lf\n", a);
    return 0;
}