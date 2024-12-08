#include <stdio.h>
#include <stdlib.h>

/* Prototipos */
void leia_ints (char nome_do_arquivo[], int a[], int &n);
int conte (int a[], int n);

/* Main */
int main() {
  char filename[30];
  int a[1000000], n;

  // Leia o nome do arquivo
  printf("Entre com o nome do arquivo:\n");
  scanf("%s", filename);

  // Carregue o arquivo no vetor a
  leia_ints(filename, a, n);

  // Conte e imprima quantas vezes 3 elementos somam 0
  printf("%d\n", conte(a, n));
}

// Funcao que abre arquivo e carrega todos os ints para o vetor a
void leia_ints (char nome_do_arquivo[], int a[], int &n) {
  FILE *f;

  f = fopen(nome_do_arquivo, "r");
  if (f == NULL) {
    printf("Erro! Nao foi possivel abrir o arquivo!\n");
  }
  else {
    n = 0;
    while(!feof(f)) {
      fscanf(f, "%d", &a[n]);
      n = n + 1;
    }
    n = n - 1;
  }
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