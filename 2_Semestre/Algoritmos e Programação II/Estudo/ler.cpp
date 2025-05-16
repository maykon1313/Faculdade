#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    char v[26];
    FILE *f;

    f = fopen("arq_bin.dat", "rb");

    fread(v, sizeof(char), sizeof(v)/sizeof(char), f);

    for (i = 0; i < 26; i++) printf("%c ", v[i]);
    
    fclose(f);
    return 0;
}
