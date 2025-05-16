#include <stdio.h>
int main(){
    int n, contador = 0;
    float media = 0.0;

    printf("Entre com números, '0' termina o programa. \n");
    scanf("%d", &n);

    while (n != 0) {
        media += n;
        contador += 1;
        scanf("%d", &n);
    }
    
    media = media/contador;
    printf("%d números digitados.\n", contador);
    printf("A média aritmética foi de %f.\n", media);
}