#include <stdio.h>

int main() {
    int a, b;
    FILE *f;

    f = fopen("entrada.txt", "r+");
    
    while (true) {
        printf("Digite os valores para A e B (-1 finaliza): ");
        scanf("%d %d", &a, &b);
        if (a == -1 || b == -1) break;
        fprintf(f, "%d %d\n", a, b);
    }

    fclose(f);
    return 0;
}

//fprintf
//fcanf

//fwrite
//fread