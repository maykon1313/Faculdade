#include <stdio.h>
#include <math.h>

bool sufixo(int num1, int num2) {
    int aux = num2, digitos = 0;

    while (aux > 0) {
        digitos += 1;
        aux /= 10;
    }

    num1 = num1 % (int)pow(10, digitos);

    if (num1 == num2) {
        return true;  
    } else {
        return false;
    }  
}

int main() {
    int num1, num2;
    bool ele_eh;

    printf("Digite o primeiro número: ");
    scanf("%d", &num1);
    printf("Digite o segundo número: ");
    scanf("%d", &num2);

    ele_eh = sufixo(num1, num2);

    if (ele_eh) {
        printf("O segundo número é sufixo do primeiro número.\n");
    } else {
        printf("O segundo número não é sufixo do primeiro número.\n");
    }
}