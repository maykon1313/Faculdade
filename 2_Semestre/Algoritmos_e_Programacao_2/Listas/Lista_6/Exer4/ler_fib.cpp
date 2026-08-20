#include <stdio.h>

int main() {
    FILE *f;
    int n, aux;
    
    f = fopen("seq30_fib.dat", "rb");
    
    printf("Quer o que?\n");
    scanf("%d", &n);
    
    fseek(f, (n-1) * sizeof(int), SEEK_SET);
    fread(&aux, sizeof(int), 1, f);
    
    printf("%d", aux);
    
    fclose(f);
    return 0;
}