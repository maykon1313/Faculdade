#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[100];
    char *p[10];
    int i, k;
    
    while (1){
        printf("Digite um nome (até 10 nomes): ");
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (strlen(buffer) == 0) break;
        
        p[i] = (char *) malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(p[i], buffer);
        i++;
    }
    
    for (k = 0; k < i; k++){
        printf("Nome[%d]: %s.\n", k+1, p[k]);
    }
    
    for (k = 0; k < i; k++){
        free(p[k]);
    }
    
    return 0;
}