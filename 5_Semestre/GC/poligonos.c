#include <stdio.h>

#define X 0
#define Y 1
#define DIM 2

#define N 3

typedef enum { FALSE, TRUE } bool;

typedef int tPoint[DIM];

typedef tPoint tPolygon[N];

int AreaTriangulo(tPoint a, tPoint b, tPoint c) {
    return a[X] * b[Y] - a[Y] * b[X] + a[Y] * c[X] - a[X] * c[Y] + b[X] * c[Y] - b[Y] * c[X];
}

int AreaPoligono(int n, tPolygon P) {
    int sum = 0;
    for (int i = 1; i < n-1; i++) {
        sum += AreaTriangulo(P[i-1], P[i], P[i+1]);
    }
    return sum;
}

bool Left(tPoint a, tPoint b, tPoint c) {
    return AreaTriangulo(a, b, c) > 0;
    // C está a esquerda ou a direita do segmento de reta AB? Horário, área positiva, ponto a ESQUERDA.
}

bool LeftOn(tPoint a, tPoint b, tPoint c) {
    return AreaTriangulo(a, b, c) >= 0;
    // Zero se C estiver no segmento AB.
}

bool Collinear(tPoint a, tPoint b, tPoint c) {
    return AreaTriangulo(a, b, c) == 0;
    // Estão todos sobre a mesma linha.
}

bool Xor(bool x, bool y) {
    return x^y;
}

bool IntersecProp(tPoint a, tPoint b, tPoint c, tPoint d) {
    if (Collinear(a,b,c) || Collinear(a,b,d) || Collinear(c,d,a) || Collinear(c,d,b)) return FALSE;
    return Xor(Left(a,b,c), Left(a,b,d)) && Xor(Left(c,d,a), Left(c,d,b));
}

bool Between(tPoint a, tPoint b, tPoint c) {
    if (!Collinear(a, b, c)) return FALSE;

    if (a[X] != b[X]) return ((a[X] <= c[X]) && (c[X] <= b[X])) || ((a[X] >= c[X]) && (c[X] >= b[X]));
    else return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) || ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}

bool Intersect(tPoint a, tPoint b, tPoint c, tPoint d) {
    if (IntersecProp(a,b,c,d)) return TRUE;
    else if (Between(a,b,c) || Between(a,b,d) || Between(c,d,a) || Between(c,d,b)) return TRUE;
    else return FALSE;
}

bool Diagonalie(int i, int j, int n, tPolygon P) {
    int k, k1;
    for (k = 0; k < n; k++) {
        k1 = (k+1)%n;

        if (!((k==i) || (k1 == i) || (k == j) || (k1 == j))){
            if (Intersect(P[i], P[j], P[k], P[k1])) return FALSE;
        }

        else return TRUE;
    }
}

bool InCome(int i, int j, int n, tPolygon P) {

}

bool Diagonal(int i, int j, int n, tPolygon P) {
    return InCome(i,j,n,P) && Diagonalie(i,j,n,P);
}

int main() {
    tPolygon P = {
        {0, 0},
        {3, 0},
        {0, 4}
    };

    printf("%d\n", AreaPoligono(3, P));

    return 0;
}