#include <stdio.h>

void bubble_sort(int v[], int n) {
    int i, j, aux;
    
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-1; j++){
            if (v[j] > v[j+1]) {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void insertion_sort(int v[], int n) {
    int i, j, key;
    
    for (i = 1; i < n; i++) {
        key = v[i];
        j = i-1;
        
        while (j >= 0 && v[j] > key) {
            v[j+1] = v[j];
            j--;
            
        v[j+1] = key;
        }
    }
}

void selection_sort(int v[], int n) {
    int i, j, index_min, aux;
    
    for (i = 0; i < n-1; i++) {
        index_min = i;
        
        for (j = i+1; j < n; j++) if (v[j] < v[index_min]) index_min = j;
        
        aux = v[index_min];
        v[index_min] = v[i];
        v[i] = aux;
    }
}

int main() {
    int i, n;
    int v1[] = {8,63,2,32,63,2,5,2,52,34,45,24,24,63,1,2,34,5,75,4,6,7,89,2,54,66,7,1,76,21,37,12,3,11,5,18,3,4,5,6,7,8,9,10,21};
    int v2[] = {8,63,2,32,63,2,5,2,52,34,45,24,24,63,1,2,34,5,75,4,6,7,89,2,54,66,7,1,76,21,37,12,3,11,5,18,3,4,5,6,7,8,9,10,21};
    int v3[] = {8,63,2,32,63,2,5,2,52,34,45,24,24,63,1,2,34,5,75,4,6,7,89,2,54,66,7,1,76,21,37,12,3,11,5,18,3,4,5,6,7,8,9,10,21};
    
    n = sizeof(v1)/sizeof(int);
    
    bubble_sort(v1, n);
    insertion_sort(v2, n);
    selection_sort(v3, n);
    
    //Vetor 1
    for  (i = 0; i < n; i++) {
        printf("%d ", v1[i]);
    }
    
    printf("\n");
    
    //Vetor 2
    for  (i = 0; i < n; i++) {
        printf("%d ", v2[i]);
    }
    
    printf("\n");
    
    //Vetor 3
    for  (i = 0; i < n; i++) {
        printf("%d ", v3[i]);
    }
    
    printf("\n");
    
    return 0;
}