#include <stdio.h>
int main(){
    int v, m;
    int const TAXA = 5;

    printf("Entre com a velocidade: \n");
    scanf("%d", &v);

    if (v > 80) {
        m = (v - 80) * TAXA;
        printf("A multa será de: %iR$. \n", m);
    }

    return 0;
}