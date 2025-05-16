#include <stdio.h>
int main(){
    int a, b, contador = 0;

    printf("Entre com 'a': \n");
    scanf("%d", &a);

    printf("Entre com 'b': \n");
    scanf("%d", &b);

    // a//b
    while (a >= b) {
        a = a - b;
        contador += 1;
    }

    printf("A divisão inteira de 'a' por 'b' é: %d. \n", contador);
    printf("E o retso da divisão inteira de 'a' por 'b' é: %d. \n", a);

    return 0;
}