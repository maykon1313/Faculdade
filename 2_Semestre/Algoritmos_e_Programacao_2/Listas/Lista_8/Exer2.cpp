#include <stdio.h>

int eleve(int x, int n) {
    if (n == 0) return 1;
    else return x * eleve(x, n-1);
}

int main() {
    int x, n, a;

    scanf("%d", &x);
    scanf("%d", &n);
    
    a = eleve(x, n);

    printf("Resultado de %d: %d.\n", n, a);
    return 0;
}