#include <stdio.h>
#include <stdlib.h>

void bubble_sort(void *base, size_t n_itens, size_t tipo, int (*compara)(const void *, const void*));
int compara_int(const void *a, const void *b);
int compara_float(const void *a, const void *b);
int compara_char(const void *a, const void *b);

int main() {
    int array_int[] = {10, 9, 2, 4, 5, 1, 6};
    float array_float[] = {5.1, 3.2, 2.4, 1.2, 5.2, 1.3};
    char array_char[] = {'B', 'Z', 'Q', 'C', 'A', 'M', 'A', 'Y', 'K', 'O', 'N'};
    size_t n_int, n_float, n_char;
    int i;
    
    n_int = sizeof(array_int)/sizeof(int);
    n_float = sizeof(array_float)/sizeof(float);
    n_char = sizeof(array_char)/sizeof(char);
    
    bubble_sort(array_int, n_int, sizeof(int), compara_int);
    bubble_sort(array_float, n_float, sizeof(float), compara_float);
    bubble_sort(array_char, n_char, sizeof(char), compara_char);
    
    //Print para o array de INT
    for (i = 0; i < n_int; i++){
        printf("%d ", array_int[i]);
    }
    
    printf("\n");
    
    
    //Print para o array de FLOAT
    for (i = 0; i < n_float; i++){
        printf("%.1f ", array_float[i]);
    }
    
    printf("\n");
    
    
    //Print para o array de CHAR
    for (i = 0; i < n_char; i++){
        printf("%c ", array_char[i]);
    }
    
    printf("\n");
    return 0;
}

void bubble_sort(void *base, size_t n_itens, size_t tipo, int (*compara)(const void *, const void*)) {
    int i, j;
    
    for (i = 0; i < n_itens - 1; i++) {
        for (j = 0; j < n_itens - 1; j++){
            void *endereco1 = (char *)base + (j * tipo);
            void *endereco2 = (char *)base + ((j +1) * tipo);
            
            if (compara(endereco1, endereco2) > 0) {
                if (tipo == sizeof(int)) {
                    int temp = *(int *)endereco1;
                    *(int *)endereco1 = *(int *)endereco2;
                    *(int *)endereco2 = temp;
                } else if (tipo == sizeof(float)) {
                    float temp = *(float *)endereco1;
                    *(float *)endereco1 = *(float *)endereco2;
                    *(float *)endereco2 = temp;
                } else if (tipo == sizeof(char)) {
                    char temp = *(char *)endereco1;
                    *(char *)endereco1 = *(char *)endereco2;
                    *(char *)endereco2 = temp;
                }
            }
        }
    }
}

int compara_int(const void *a, const void *b) {
    int diff = (*(int *)a - *(int *)b);
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int compara_float(const void *a, const void *b) {
    float diff = (*(float *)a - *(float *)b);
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int compara_char(const void *a, const void *b) {
    int diff = (*(char *)a - *(char *)b);
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}