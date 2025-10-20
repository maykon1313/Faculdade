#include <stdio.h>

int main() {
    int x = 2, y = 8, *p = &x, *q = &y;
    
    printf("&x = %p e x = %d\n", &x, x);
    printf("p = %p e *p = %d\n", p, *p);
    printf("&y = %p e y = %d\n", &y, y);
    printf("&p = %p\n", &p);
    
    return 0 ;
}