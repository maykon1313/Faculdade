#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// struct
struct tank {
    int direction;
    int position_x;
    int position_y;
};

struct enemie {
    int life;
    int position_x;
    int position_y;
};

typedef struct tank tank;
typedef struct enemie enemie;


int *make_enemies(int n_enemies) {
    enemie v[n_enemies], i;

    for (i = 1; i <= n_enemies; i++) {
        enemie aux;

        aux.life = 1;
        aux.position_x;
        aux.position_y;
        // TO DO

        v[i-1] = aux;
    }

    return v;
}


int main() {
    int n_enemies, *v;

    scanf("%d", &n_enemies);

    v = make_enemies(n_enemies);
}