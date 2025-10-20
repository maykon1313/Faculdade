#include <stdio.h>

int mdc(int n, int m) {
    if (m <= n && n%m == 0) return m;
    else return (m, n%m);
}

int main() {
    int n, m, aux;

    scanf("%d", &n);
    scanf("%d", &m);

    if (n < m) {
        aux = n;
        n = m;
        m = aux;
    }

    aux = mdc(n, m);

    printf("O MDC de %d e %d: %d.\n", n, m, aux);

    return 0;
}