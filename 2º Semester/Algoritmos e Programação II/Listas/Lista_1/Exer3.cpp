#include <stdio.h>
int main(){
    int a, b, c, aux;

    printf("Entre com o 1° valor: \n");
    scanf("%d", &a);

    printf("Entre com o 2° valor: \n");
    scanf("%d", &b);

    printf("Entre com o 3° valor: \n");
    scanf("%d", &c);

    if (b < c){
        aux = b;
        b = c;
        c = aux;
    }

    if (a < b){
        aux = a;
        a = b;
        b = aux;
    }

    if (b < c){
        aux = b;
        b = c;
        c = aux;
    }

    printf("Maior: %d; Médio: %d; Menor: %d. \n", a, b, c);

    return 0;
}