#include <stdio.h>
#include <stdlib.h>

void distancia(int num, int grafo[5][5]);
void caminho(int anterior[], int destino);

int main(){
    int grafo[5][5] = {0}, num;

    grafo[0][1] = 1;
    grafo[0][2] = 1;
    grafo[1][4] = 1;
    grafo[2][1] = 1;
    grafo[2][3] = 1;
    grafo[3][4] = 1;

    for (num = 0; num < 5; num++){
        distancia(num, grafo);
        printf("\n");
    }

    return 0;
}

void caminho(int anterior[], int destino) {
    if (anterior[destino] == -1) {
        printf("%d ", destino);
        return;
    }
    caminho(anterior, anterior[destino]);
    printf("%d ", destino);
}

void distancia(int num, int grafo[5][5]){
    int distancias[5] = {-1, -1, -1, -1, -1}, x, y;
    int anterior[5] = {-1, -1, -1, -1, -1};
    int fila[5] = {-1, -1, -1, -1, -1}, s = 0, t = 1;

    distancias[num] = 0;
    fila[0] = num;

    while (s < t){
        x = fila[s];
        s++;

        for (y = 0; y < 5; y++){
            if (grafo[x][y] == 1 && distancias[y] == -1){
                distancias[y] = distancias[x] + 1;
                anterior[y] = x;
                fila[t] = y;
                t += 1;
            }
        }
    }

    for (x = 0; x < 5; x++) {
        if (distancias[x] != -1) {
            printf("Distância de %d para %d: %d. Caminho: ", num, x, distancias[x]);
            caminho(anterior, x);
            printf("\n");
        } else {
            printf("Distância de %d para %d: Infinito (sem caminho).\n", num, x);
        }
    }
}
