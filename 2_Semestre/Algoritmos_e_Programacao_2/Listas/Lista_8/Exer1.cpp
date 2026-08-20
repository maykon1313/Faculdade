#include <stdio.h>

int fibonacci(int n) {
    if (n == 0 || n == 1) return n;
    
    return fibonacci(n-1) + fibonacci(n-1);
}

int main() {
    int n;

    printf("Digite qual elemento da sequência de Fibonacci desejado: ");
    scanf("%d", &n);

    printf("%d", fibonacci(n));
    return 0;
}