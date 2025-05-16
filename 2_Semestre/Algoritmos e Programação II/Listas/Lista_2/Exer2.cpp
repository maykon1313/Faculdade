#include <stdio.h>
#include <stdlib.h>

int main() {
    int vetor[6], num, entrada;
    bool achou = false;
    
    for (int i = 0; i < 6; i++) {
        num = rand() % 60;
        vetor[i] = num;
    }
    
    printf("Digite um número: ");
    scanf("%d", &entrada);
    
    while (entrada != 0) {
        achou = false;
        for (int i = 0; i < 6; i++){
            if (vetor[i] == entrada) {
                achou = true;
                break;
            }
            
        }
        
        if (achou) {
            printf("O número está no vetor.\n");
        } else {
            printf("O número não está no vetor.\n");
        }
        
        printf("Digite um número: ");
        scanf("%d", &entrada);
    }
    
    printf("O vetor:");
    for (int i = 0; i < 6; i++) {
        printf(" %d", vetor[i]);
    }
    
    return 0;
}
