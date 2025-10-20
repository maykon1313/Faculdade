#include <stdio.h>
#include <string.h>
int main() {
    int num;
    char texto1[100], texto2[100];

    printf("Digite o 1° texto: ");
    scanf("%s%*c", texto1);

    printf("Quantos caracteres do 1° texto no 2° texto?\n");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        texto2[i] = texto1[i];
    }
    texto2[num] = '\0';

    printf("2º texto: %s.", texto2);

    return 0;
}