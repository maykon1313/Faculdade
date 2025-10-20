#include <stdio.h>

enum estado_civil {SOLTEIRO, CASADO, DIVORCIADO, VIÚVO};

int main() {
    char *estado_nome[] = {"Solteiro", "Casado", "Divorciado", "Viúvo"};
    enum estado_civil estado; 
    
    printf("Estado civil?");
    printf("0 - Solteiro.\n");
    printf("1 - Casado.\n");
    printf("2 - Divorciado.\n");
    printf("3 - Viúvo.\n");

    scanf("%d", &estado);

    if (estado >= SOLTEIRO && estado <= VIÚVO) {
        printf("Estado civil: %s.\n", estado_nome[estado]);
        printf("Estado civil (numérico): %d.\n", estado);
    } else {
        printf("Estado civil inválido.\n");
    }
    return 0;
}