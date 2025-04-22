#include <stdio.h>

void troque2(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

int main() {
    int a, b, c;
    
    printf("Digite a: ");
    scanf("%d", &a);
    printf("Digite b: ");
    scanf("%d", &b);
    printf("Digite c: ");
    scanf("%d", &c);
    
    troque2(&a, &b);
    troque2(&b, &c);
    troque2(&c, &a);
    
    printf("a = %d, b = %d e c = %d", a, b, c);
        
    return 0;
}
