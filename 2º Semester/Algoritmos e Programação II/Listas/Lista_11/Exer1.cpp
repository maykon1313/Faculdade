#include <stdio.h>

void enfilerar(int num, int *s, int *t, int v[]);
void desenfilerar(int *s, int *t, int v[]);
void printar(int s, int t, int v[]);
void elementos(int s, int t);

int main(){
    int v[6] = {-1, -1, -1, -1, -1, -1}, s = 0, t = 0;

    enfilerar(33, &s, &t, v);
    printar(s, t, v);
    enfilerar(7, &s, &t, v);
    printar(s, t, v);
    enfilerar(11, &s, &t, v);
    printar(s, t, v);
    elementos(s, t);

    desenfilerar(&s, &t, v);
    printar(s, t, v);
    desenfilerar(&s, &t, v);
    printar(s, t, v);
    elementos(s, t);


    enfilerar(2, &s, &t, v);
    printar(s, t, v);
    elementos(s, t);

    return 0;
}

void enfilerar(int num, int *s, int *t, int v[]){
    if ((*t+1)%6 == *s) printf("Fila cheia.\n");
    
    else if (((*t+1)%6) == *s) printf("Fila cheia.\n");

    else{
        v[*t] = num;
        *t = *t + 1;
    }

    if (*t > 5) *t = 0;
}

void desenfilerar(int *s, int *t, int v[]){
    if (*s == *t) printf("Fila vazia.\n");

    else{
        *s = *s + 1;
    }

    if (*s > 5) *s = 0;
}

void printar(int s, int t, int v[]){
    printf("S = %d, V[S] = %d.\n", s, v[s]);
    printf("T = %d, V[T] = %d.\n", t, v[t]);
}

void elementos(int s, int t){
    if (t > s) printf("Elementos: %d.\n\n", t-s);
    else printf("Elementos: %d.\n\n", 5+t-s);
}