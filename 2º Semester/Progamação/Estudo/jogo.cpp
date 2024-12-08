#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

void sprint_tanque(int direcao) {
    if (direcao == 2) printf("▼ ");  // Tanque para baixo
    if (direcao == 4) printf("◄ ");  // Tanque para esquerda
    if (direcao == 6) printf("► ");  // Tanque para direita
    if (direcao == 8) printf("▲ ");  // Tanque para cima
}

void sprint_inimigos(int tipo) {
    if (tipo == 1) printf("1 ");  // Inimigo 1
    if (tipo == 3) printf("2 ");  // Inimigo 2
    if (tipo == 5) printf("3 ");  // Inimigo 3
}

void sprint_caminhos(int parede) {
    if (parede == 7) printf("O ");  // Caminho livre
    if (parede == 9) printf("@ ");  // Parede
    if (parede == 10) printf("X "); // Inimigo morto
}

void sprint_central(int num) {
    if (num%2 == 0) sprint_tanque(num);
    if (num < 7) sprint_inimigos(num);
    else sprint_caminhos(num);
}

void show_map(int map[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            sprint_central(map[i][j]);
        }
        printf("\n\n");
    }
}

void hit_enemie(int map[10][10], enemie *ene, int x, int y) {
    if (ene->position_x == x && ene->position_y == y && ene->life > 0) {
        ene->life--;
        if (ene->life == 0) {
            map[x][y] = 10;  // Marca o inimigo como morto no mapa
        }
    }
}

void fire_ball(int map[10][10], int diretion, int x, int y, enemie *ene1, enemie *ene2, enemie *ene3) {
    int i = x, j = y, sprint;

    // Baixo
    if (diretion == 2) {
        for (; i < 10; i++) {
            sprint = map[i][j];

            // Parede
            if (sprint == 9) return;

            // Inimigo
            if (sprint == 1 || sprint == 3 || sprint == 5) {
                hit_enemie(map, ene1, i, j);
                hit_enemie(map, ene2, i, j);
                hit_enemie(map, ene3, i, j);
                return;
            }
        }
    }

    // Esquerda
    if (diretion == 4) {
        for (; j >= 0; j--) {
            sprint = map[i][j];
            if (sprint == 9) return;
            if (sprint == 1 || sprint == 3 || sprint == 5) {
                hit_enemie(map, ene1, i, j);
                hit_enemie(map, ene2, i, j);
                hit_enemie(map, ene3, i, j);
                return;
            }
        }
    }

    // Direita
    if (diretion == 6) {
        for (; j < 10; j++) {
            sprint = map[i][j];
            if (sprint == 9) return;
            if (sprint == 1 || sprint == 3 || sprint == 5) {
                hit_enemie(map, ene1, i, j);
                hit_enemie(map, ene2, i, j);
                hit_enemie(map, ene3, i, j);
                return;
            }
        }
    }

    // Cima
    if (diretion == 8) {
        for (; i >= 0; i--) {
            sprint = map[i][j];
            if (sprint == 9) return;
            if (sprint == 1 || sprint == 3 || sprint == 5) {
                hit_enemie(map, ene1, i, j);
                hit_enemie(map, ene2, i, j);
                hit_enemie(map, ene3, i, j);
                return;
            }
        }
    }
}

bool move_tank(int map[10][10], tank *me, int move, enemie *ene1, enemie *ene2, enemie *ene3) {
    int x = me->position_x;
    int y = me->position_y;

    if (move == 2) {
        if (map[x+1][y] == 7 || map[x+1][y] == 10) {
            map[x][y] = 7;
            map[x+1][y] = 2;

            me->position_x += 1;
            me->direction = 2;
            return true;
        } else {
            printf("Movimento inválido.\n");
            return false;
        }
    }

    if (move == 4) {
        if (map[x][y-1] == 7 || map[x+1][y] == 10) {
            map[x][y] = 7;
            map[x][y-1] = 4;

            me->position_y -= 1;
            me->direction = 4;
            return true;
        } else {
            printf("Movimento inválido.\n");
            return false;
        }
    }

    if (move == 6) {
        if (map[x][y+1] == 7 || map[x+1][y] == 10) {
            map[x][y] = 7;
            map[x][y+1] = 6;

            me->position_y += 1;
            me->direction = 6;
            return true;
        } else {
            printf("Movimento inválido.\n");
            return false;
        }
    }

    if (move == 8) {
        if (map[x-1][y] == 7 || map[x+1][y] == 10) {
            map[x][y] = 7;
            map[x-1][y] = 8;

            me->position_x -= 1;
            me->direction = 8;
            return true;
        } else {
            printf("Movimento inválido.\n");
            return false;
        }
    }

    if (move == 0) {
        fire_ball(map, me->direction, x, y, ene1, ene2, ene3);
        printf("FIRE BALL!\n");
        return true;
    }

    else {
        printf("Movimento inválido.\n");
        return false;
    }
}

int menu() {
    int movimento;

    printf("2 - Baixo.\n");
    printf("4 - Esquerda.\n");
    printf("6 - Direita.\n");
    printf("8 - Cima.\n");
    printf("0 - Atirar.\n");

    scanf("%d", &movimento);
    return movimento;
}

void move_enemie(int map[10][10], enemie *ene, int player_x, int player_y, int num) {
    if (ene->life == 0) return; // Se o inimigo estiver morto, não se move

    int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // Baixo, Direita, Cima, Esquerda
    int chosen_direction;
    int move_valid = 0;

    // Tenta mover até conseguir um movimento válido
    while (!move_valid) {
        int move_random = rand() % 5; // 20% de chance de se mover aleatoriamente

        if (move_random == 0) {
            chosen_direction = rand() % 4; // Escolhe direção aleatória
        } else {
            int dx = player_x - ene->position_x;
            int dy = player_y - ene->position_y;
            if (abs(dx) > abs(dy)) {
                chosen_direction = (dx > 0) ? 0 : 2; // Baixo ou Cima
            } else {
                chosen_direction = (dy > 0) ? 1 : 3; // Direita ou Esquerda
            }
        }

        int new_x = ene->position_x + direction[chosen_direction][0];
        int new_y = ene->position_y + direction[chosen_direction][1];

        // Verifica se o novo movimento está dentro dos limites do mapa
        if (new_x >= 0 && new_x < 10 && new_y >= 0 && new_y < 10) {
            if (map[new_x][new_y] == 7 || map[new_x][new_y] == 10 || map[new_x][new_y] == 2 || map[new_x][new_y] == 4 || map[new_x][new_y] == 6 || map[new_x][new_y] == 8) { // Caminho livre ou posição de inimigo morto ou tanque
                map[ene->position_x][ene->position_y] = 7; // Marca a posição antiga como livre
                ene->position_x = new_x;
                ene->position_y = new_y;
                map[new_x][new_y] = num;
                move_valid = 1;
            }
        }
    }
}

bool check_collision(tank *me, enemie *ene1, enemie *ene2, enemie *ene3, int map[10][10]) {
    if (me->position_x == ene1->position_x && me->position_y == ene1->position_y && ene1->life > 0) {
        map[ene1->position_x][ene1->position_y] = 7; // Posição do inimigo se torna livre
        map[me->position_x][me->position_y] = 10; // Posição do tanque se torna 'X'
        return false;
    } else if (me->position_x == ene2->position_x && me->position_y == ene2->position_y && ene2->life > 0) {
        map[ene2->position_x][ene2->position_y] = 7;
        map[me->position_x][me->position_y] = 10;
        return false;
    } else if (me->position_x == ene3->position_x && me->position_y == ene3->position_y && ene3->life > 0) {
        map[ene3->position_x][ene3->position_y] = 7;
        map[me->position_x][me->position_y] = 10;
        return false;
    }
    return true;
}

bool game(int map[10][10], tank *me, enemie *ene1, enemie *ene2, enemie *ene3) {
    int move, x = me->position_x, y = me->position_y;
    bool moved = false;

    while (ene1->life + ene2->life + ene3->life != 0) {
        show_map(map);

        printf("Seu turno:\n");
        // Repete até um movimento válido for feito
        while (!moved) {
            move = menu();

            moved = move_tank(map, me, move, ene1, ene2, ene3);
        }
        show_map(map);

        printf("Turno dos inimigos:\n");

        if (ene1->life > 0) {
            printf("\nInimigo 1:\n");
            usleep(100000);
            
            move_enemie(map, ene1, x, y, 1);
            show_map(map);
            usleep(2500000);
        }

        if (ene2->life > 0) {
            printf("\nInimigo 2:\n");
            usleep(100000);

            move_enemie(map, ene2, x, y, 3);
            show_map(map);
            usleep(2500000);
        }

        if (ene3->life > 0) {
            printf("\nInimigo 3:\n");
            usleep(100000);

            move_enemie(map, ene3, x, y, 5);
        }

        if (!check_collision(me, ene1, ene2, ene3, map)) { 
            show_map(map);
            return false;
        }

        moved = false;
    }

    return true;
}

void config(tank *me, enemie *ene1, enemie *ene2, enemie *ene3) {
    me->direction = 2;
    me->position_x = 2;
    me->position_y = 2;

    ene1->life = 1;
    ene1->position_x = 2;
    ene1->position_y = 8;

    ene2->life = 1;
    ene2->position_x = 8;
    ene2->position_y = 1;

    ene3->life = 1;
    ene3->position_x = 6;
    ene3->position_y = 6;
}

int main() {
    tank me;
    enemie ene1, ene2, ene3;
    bool win = false;
    int map[10][10] = {
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 7, 7, 7, 9, 9, 9, 7, 7, 9},
        {9, 7, 2, 7, 9, 9, 9, 7, 1, 9},
        {9, 7, 7, 7, 7, 7, 7, 7, 7, 9},
        {9, 9, 9, 9, 7, 9, 9, 9, 7, 9},
        {9, 9, 9, 9, 7, 9, 9, 9, 7, 9},
        {9, 7, 7, 7, 7, 7, 5, 9, 7, 9},
        {9, 7, 9, 9, 9, 9, 7, 9, 7, 9},
        {9, 3, 7, 7, 9, 7, 7, 7, 7, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9}
    };

    config(&me, &ene1, &ene2, &ene3);

    win = game(map, &me, &ene1, &ene2, &ene3);

    if (win) printf("\n VITÓRIA! \n");
    else printf("Colisão detectada! O jogo terminou.\n"); 

    return 0;
}
