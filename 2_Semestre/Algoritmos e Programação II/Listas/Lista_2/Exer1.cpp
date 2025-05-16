#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, produto = 0, *vetor_u, *vetor_v;
    
    printf("Informe o tamanho dos vetores: ");
    scanf("%d", &n);
    
    vetor_u = (int *) malloc(sizeof(int) * n);
    vetor_v = (int *) malloc(sizeof(int) * n);
    
    printf("Informe os elementos do vetor U: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor_u[i]);
    }
    
    printf("Informe os elementos do vetor V: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor_v[i]);
    }
    
    for (int i = 0; i < n; i++) {
        produto += vetor_u[i] * vetor_v[i];
    }
    
    printf("O produto escalar desses vetores é: %d\n", produto);

    free(vetor_u);
    free(vetor_v);
    return 0;
}
