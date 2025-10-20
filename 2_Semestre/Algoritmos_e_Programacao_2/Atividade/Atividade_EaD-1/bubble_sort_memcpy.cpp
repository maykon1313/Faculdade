#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_int(const void *a, const void *b);
int comparar_float(const void *a, const void *b);
int comparar_char(const void *a, const void *b);
void bubble_sort(void *v, size_t n_itens, size_t size, int (*compare)(const void *, const void *));

int main() {
    int v_int[] = {6,1,1,2,3,4,3,2,46,8,4,6,2,85,5,21,45,8,9,3,4,8,7,2,9,1,5,6,2,3,6,7,1};
    float v_float[] = {1.1,2.01,1,2,5,4,4.5,0.4};
    char v_char[] = {'a','c','a','f','g','o','p','k'};
    int i;
    
    bubble_sort(v_int, sizeof(v_int)/sizeof(int), sizeof(int), comparar_int);
    bubble_sort(v_float, sizeof(v_float)/sizeof(float), sizeof(float), comparar_float);
    bubble_sort(v_char, sizeof(v_char)/sizeof(char), sizeof(char), comparar_char);
    
    for (i = 0; i < (sizeof(v_int)/sizeof(int)); i++) {
        printf("%d ", v_int[i]);
    }
    
    printf("\n");
    
    for (i = 0; i < (sizeof(v_float)/sizeof(float)); i++) {
        printf("%.2f ", v_float[i]);
    }
    
    printf("\n");
    
    for (i = 0; i < (sizeof(v_char)/sizeof(char)); i++) {
        printf("%c ", v_char[i]);
    }
    
    printf("\n");
    return 0;
}

int comparar_int(const void *a, const void *b) {
    int resu = *(const int *)a - *(const int *)b;
    if (resu > 0) return 1;
    else return 0;
}

int comparar_float(const void *a, const void *b) {
    float resu = *(const float *)a - *(const float *)b;
    if (resu > 0) return 1;
    else return 0;
}

int comparar_char(const void *a, const void *b) {
    int resu = *(const char *)a - *(const char *)b;
    if (resu > 0) return 1;
    else return 0;
}

void bubble_sort(void *v, size_t n_itens, size_t size, int (*compare)(const void *, const void *)) {
    int i, j;
    void *aux;
    char *end_1, *end_2;
    
    aux = malloc(size);
    
    for (i = 0; i < n_itens-1; i++){
        for (j = 0; j < n_itens-1; j++){
            end_1 = (char *) v + (j * (size));
            end_2 = (char *) v + ((j+1) * (size));
            
            if ((*compare)(end_1, end_2) == 1) {
                memcpy(aux, end_1, size);
                memcpy(end_1, end_2, size);
                memcpy(end_2, aux, size);
            }
        }
    }
    
    free(aux);
}