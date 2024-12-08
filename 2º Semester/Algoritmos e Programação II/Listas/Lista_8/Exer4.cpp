#include <stdio.h>

int funcao(int n) {
    if (n == 0) return 1;
    else return funcao(n-1) + 1/(funcao(n-1));
}

int main() {
    int n, aux;

    scanf("%d", &n);    

    aux = funcao(n);

    printf("O resultado para %d: %d.\n", n, aux);

    return 0;
}