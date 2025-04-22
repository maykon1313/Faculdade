#include <stdio.h>
double area(float raio, double PI) {
    double area_da_esfera;
    area_da_esfera = 4 * PI * (raio * raio);
    return area_da_esfera;
}

int main() {
    const double PI = 3.14159265359;
    double area_da_esfera;
    float raio;

    printf("Digite o raio da esfera: ");
    scanf("%f", &raio);

    area_da_esfera = area(raio, PI);

    printf("A área da esfera é: %.5fu.a.\n", area_da_esfera);

    return 0;
}