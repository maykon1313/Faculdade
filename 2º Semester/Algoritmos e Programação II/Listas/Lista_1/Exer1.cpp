#include <stdio.h>
int main(){
    float h, r, v;
    double const PI = 3.1415926535;

    printf("Entre com a altura: \n");
    scanf("%f", &h);

    printf("Entre com o raio: \n");
    scanf("%f", &r);

    v = PI * r * r * h;
    printf("O volume do cilíndro é: %f \n", v);

    return 0;
}