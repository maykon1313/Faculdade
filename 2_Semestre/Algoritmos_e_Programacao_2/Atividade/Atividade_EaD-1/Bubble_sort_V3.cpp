#include <stdio.h>

void bubble_sort(int v[], int len) {
    int i, j, aux;

    for (i = 0; i < len-1; i++) {
        for (j = 0; j < len-1; j++) {
            if (v[j] > v[j+1]) {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void bubble_sort_ponteiro(int *v, int len) {
    int i, j, aux;

    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1; j++) {
            if (*(v + j) > *(v + (j + 1))) {
                aux = *(v + j);
                *(v + j) = *(v + (j + 1));
                *(v + (j + 1)) = aux;
            }
        }
    }
}

void bubble_sort_endereco(int **v, int len) {
    int i, j, *aux;

    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1; j++) {
            if (**(v + j) > **(v + (j + 1))) {
                aux = *(v + j);
                *(v + j) = *(v + (j + 1));
                *(v + (j + 1)) = aux;
            }
        }
    }
}

void imprimir(int v[], int len) {
    int i;
    for (i = 0; i < len; i++) printf("%dº elemento: %d\n", i+1, v[i]); 
}

void imprimir_por_endereco(int **v, int len) {
    int i;
    for (i = 0; i < len; i++) printf("%dº elemento: %d\n", i+1, **(v+i)); 
}

int main() {
    int vetor[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int a = 3, b = 2, c = 1;
    int *vetor_endereço[] = {&a, &b, &c};

    bubble_sort_endereco(vetor_endereço, 3);

    imprimir_por_endereco(vetor_endereço, 3);
    return 0;
}
