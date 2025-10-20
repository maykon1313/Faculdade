#include <stdio.h>

void pro_valor(int n, int soma) {
    while (n > 0) {
        soma = soma + n;
        n--;
    }
    
    printf("A soma dos primeiros números é: %d.\n", soma);
}

void por_ref(int &n, int &soma) {
    while (n > 0) {
        soma = soma + n;
        n--;
    }
    
    printf("A soma dos primeiros números é: %d.\n", soma);
}

int main() {
    int n, soma = 0;
    
    printf("Digite o valor de n: ");
    scanf("%d", &n);
    
    pro_valor(n, soma);
    por_ref(n, soma);
    
    return 0;
}
