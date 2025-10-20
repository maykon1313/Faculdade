#include <stdio.h>
int main(){
    char instalacao;
    int kwh;
    float conta;

    printf("Quantos kWh consumido? \n");
    scanf("%d%*c", &kwh);

    printf("Qual o tipo de instalação? R, C ou I. \n");
    scanf("%c%*c", &instalacao);

    if (instalacao == 'R') {
        if (kwh > 500) {
            conta = kwh * 0.65;
        }
        else {
            conta = kwh * 0.4;
        }
    }

    else if (instalacao == 'C') {
        if (kwh > 1000) {
            conta = kwh * 0.60;
        }
        else {
            conta = kwh * 0.55;
        }
    }

    else if (instalacao == 'I') {
        if (kwh > 5000) {
            conta = kwh * 0.60;
        }
        else {
            conta = kwh * 0.55;
        }
    }

    printf("O valor da conta será de: %fR$. \n", conta);

    return 0;
}