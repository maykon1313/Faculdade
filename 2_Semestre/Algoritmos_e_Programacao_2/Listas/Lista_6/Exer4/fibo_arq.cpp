#include <stdio.h>

int main() {
    FILE *f;
    int i, a = 1, b = 1, aux, v[30] = {1, 1};
    
    f = fopen("seq30_fib.dat", "wb");
    
    for (i = 2; i < 30; i++) {
        aux = a;
        a = b;
        b = a + aux;
        v[i] = b;
    }
    
    fwrite(v, sizeof(int), 30, f);
    
    fclose(f);
    return 0;
}