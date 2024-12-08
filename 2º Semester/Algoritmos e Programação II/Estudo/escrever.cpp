#include <stdio.h>
#include <stdlib.h>

int compara_char(const void *a, const void *b) {
    char *c, *d;

    c = (char *)a;
    d = (char *)b;

    return *c - *d;
}

int main() {
    char v[26]= {'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'};
    FILE *f;

    qsort(v, sizeof(v)/sizeof(char), sizeof(char), compara_char);

    f = fopen("arq_bin.dat", "wb");

    fwrite(v, sizeof(char), sizeof(v)/sizeof(char), f);

    fclose(f);
    
    return 0;
}
