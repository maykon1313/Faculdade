#include <stdio.h>

void print_addr(int x) {
    printf("x = %d e &x = %p\n", x, &x);
}

int main() {
    int x = 3;
    
    printf("x = %d e &x = %p\n", x, &x);
    
    print_addr(x); // envia uma cópia do x, endereço diferente.
    
    return 0;
}
