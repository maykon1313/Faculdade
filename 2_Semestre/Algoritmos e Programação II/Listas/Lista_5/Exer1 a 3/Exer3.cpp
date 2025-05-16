#include <stdio.h>

int main() {
    int i, a, b, aux;
    FILE *f, *s;

    f = fopen("entrada.txt", "r");
    s = fopen("saida.txt", "w");

    if (!feof(f)) fscanf(f, "%d %d", &a, &b);
    
    while (!feof(f)) {
        fprintf(s, "%d\n", a+b);
        
        aux = fscanf(f, "%d %d", &a, &b);
        if (aux == 0) break;
    }

    fclose(f);
    fclose(s);
    return 0;
}