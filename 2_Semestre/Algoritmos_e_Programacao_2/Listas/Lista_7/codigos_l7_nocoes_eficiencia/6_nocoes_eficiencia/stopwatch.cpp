#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int conte (int a[], int n);

/* Main */
int main() {
  char filename[30];
  int a[1000000], n, i;
  double time1, timedif;

  srand(time(NULL));

  // Leia o tamanho do vetor
  printf("n: ");
  scanf("%d", &n);

  // Preencha o vetor a com n numeros inteiros aleatorios
  for (i = 0; i < n; i++)
    a[i] = (rand() % 20000) - 10000;

  time1 = (double) clock();            /* get initial time */
  time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */

  // Conte e imprima quantas vezes 3 elementos somam 0
  printf("%d\n", conte(a, n));

  timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
  printf("The elapsed time is %lf seconds\n", timedif);
}

// Funcao que conta e retorna quantas vezes 3 elementos somam 0
int conte (int a[], int n) {
  int i, j, k, c = 0;

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      for (k = j + 1; k < n; k++) {
        if ( (a[i] + a[j] + a[k]) == 0)
          c = c + 1;
      }
    }
  }

  return c;
}