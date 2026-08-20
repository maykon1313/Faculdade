#include <stdio.h>
#include <stdlib.h>

float media_ari(int n, int v[]) {
    float media = 0;
    int i;
    
    for (i = 0; i < n; i++) {
        media += v[i];
    }
    
    media = media/n;
    
    return media;
}



int main() {
    int n, *v, i;
    float media;
    
    printf("Quantas notas?\n");
    scanf("%d", &n);
    
    v = (int *) malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    media = media_ari(n, v);
    
    printf("Média: %f", media);
    
    free(v);
    return 0;
}