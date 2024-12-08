#include <stdio.h>

void troque1(int &x, int &y) {
    int aux = x;
    x = y;
    y = aux;
}

int main() {
    int x, y;
    
    printf("Digite x: ");
    scanf("%d", &x);
    printf("Digite y: ");
    scanf("%d", &y);
    
    troque1(x, y);
    
    printf("x = %d e y = %d", x, y);
        
    return 0;
}
