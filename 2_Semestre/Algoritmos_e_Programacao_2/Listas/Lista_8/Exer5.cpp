#include <stdio.h>

void funcao(int n) {
    if (n == 1) {
        printf("%d\n", n);
    }

    else {
        printf("%d\n", n);
        funcao(n-1);
    }
}

int main() {
    int n = 10, aux;

    funcao(n);
    return 0;
}