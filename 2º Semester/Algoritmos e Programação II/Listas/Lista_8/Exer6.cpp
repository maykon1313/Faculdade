#include <stdio.h>

int cont(int n) {
    if (n < 10) return 1;
    else return 1 + cont(n/10);
}

int main() {
    int n, a;

    scanf("%d", &n);

    a = cont(n);

    printf("Digitos de %d: %d.\n", n, a);
    return 0;
}