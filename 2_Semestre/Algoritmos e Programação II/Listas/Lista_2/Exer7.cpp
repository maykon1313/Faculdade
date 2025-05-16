#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    char *noime;
    
    printf("Quantas letras tem o nome?\n");
    scanf("%d", &n);

    noime = (char *) malloc(n * sizeof(char));

    printf("Digite o nome: ");
    scanf("%s", noime);   

    printf("As quatro primeiras letras são: ");

    char letra;
    for (int i = 0; i < 4 && i < n;) {
        letra = noime[i];
        if (letra != ' ') {
            i += 1;
            printf("%c", letra);
        }
    }

    printf(".\n");
    free(noime);
    return 0;
}