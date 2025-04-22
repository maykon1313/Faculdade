#include <stdio.h>

void programa1() {
    int i, a, b, aux;
    FILE *f, *s;

    f = fopen("entrada.dat", "r");
    s = fopen("saida.dat", "w");

    if (!feof(f)) fscanf(f, "%d %d", &a, &b);
    
    while (!feof(f)) {
        fprintf(s, "%d\n", a+b);
        
        aux = fscanf(f, "%d %d", &a, &b);
        if (aux == 0) break;
    }

    fclose(f);
    fclose(s);
}

void programa2() {
    int sai;
    FILE *s;

    s = fopen("saida.dat", "r");

    fscanf(s, "%d", &sai);

    printf("%d\n", sai);

    fclose(s);
}

int main() {
    programa1();
    programa2();
    return 0;
}