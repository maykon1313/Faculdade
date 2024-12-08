#include <stdio.h>

void um_n(int n, int aux) {
    if (aux%2 != 0 && aux <= n) {
        printf("%d\n", aux);
        um_n(n, aux+1);
    }
    else if (aux < n) um_n(n, aux+1);
}

void n_um(int n, int aux) {
    if (n%2 != 0 && n >= aux) {
        printf("%d\n", n);
        um_n(n-1, aux);
    }
    else if (aux < n) um_n(n-1, aux);
}

int main() {
    int n, aux = 1;
    scanf("%d", &n);

    um_n(n, aux);
    n_um(n, aux);

    return 0;
}