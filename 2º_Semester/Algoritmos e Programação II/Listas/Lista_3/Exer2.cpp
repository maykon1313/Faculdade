#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[20];
    char genero[20];
    int n_integrantes;
    int ranking;
} banda;

int menu() {
    int escolha;
    printf("O que fazer?\n");
    printf("1 - Adicionar bandas.\n");
    printf("2 - Mostrar bandas.\n");
    printf("3 - Mostrar banda pelo rank.\n");
    printf("4 - Mostrar bandas pelo gênero.\n");
    printf("5 - Constar presença da banda pelo nome.\n");
    printf("6 - Sair.\n");

    scanf("%d", &escolha);
    return escolha;
}

void criar_bandas(banda bandas[]) {
    for (int i = 0; i < 5; i++) {
        banda temp;
        printf("Nome da banda: ");
        scanf("%s%*c", temp.nome);
        printf("Gênero da banda: ");
        scanf("%s%*c", temp.genero);
        printf("Número de integrantes da banda: ");
        scanf("%d%*c", &temp.n_integrantes);
        printf("Ranking da banda: ");
        scanf("%d%*c", &temp.ranking);

        bandas[i] = temp;
    }
}

void printar_bandas(banda bandas[]) {
    for (int i = 0; i < 5; i++) {
        printf("Nome: %s. Gênero: %s. Número de integrantes: %d. Ranking: %d.\n", bandas[i].nome, bandas[i].genero, bandas[i].n_integrantes, bandas[i].ranking);
    }
}

void mostrar_por_rank(banda bandas[]) {
    int posicao;
    printf("Ranking a ser mostrado: ");
    scanf("%d", &posicao);

    for (int i = 0; i < 5; i++) {
        if (bandas[i].ranking == posicao) {
            printf("Nome: %s.\nGênero: %s.\nNúmero de integrantes: %d.\nRanking: %d.\n", bandas[i].nome, bandas[i].genero, bandas[i].n_integrantes, bandas[i].ranking);
            break;
        }
    }
}

void mostrar_por_genero(banda bandas[]) {
    char genero[20];
    printf("Gênero a ser mostrado: ");
    scanf("%s", genero);

    for (int i = 0; i < 5; i++) {
        if (strcmp(bandas[i].genero, genero) == 0) {
            printf("Nome: %s.\nGênero: %s.\nNúmero de integrantes: %d.\nRanking: %d.\n", bandas[i].nome, bandas[i].genero, bandas[i].n_integrantes, bandas[i].ranking);
        }
    }
}

void nome_presente(banda bandas[]) {
    bool presente = false;
    char nome[20];
    printf("Nome da banda para procurar: ");
    scanf("%s", nome);

    for (int i = 0; i < 5; i++) {
        if (strcmp(bandas[i].nome, nome) == 0) {
            presente = true;
            break;
        }
    }

    if (presente) {
        printf("Essa banda está no seu top 5.\n");
    } else {
        printf("Essa banda não está no seu top 5.\n");
    }
}

int  main() {
    banda bandas[5];
    int escolha;
    bool repete = true;

    while (repete) {
        escolha = menu();

        switch (escolha){
        case 1:
            criar_bandas(bandas);
            break;
        case 2:
            printar_bandas(bandas);
            break;
        case 3:
            mostrar_por_rank(bandas);
            break;
        case 4:
            mostrar_por_genero(bandas);
            break;
        case 5:
            nome_presente(bandas);
            break;
        case 6:
            repete = false;
            break;
            
        default:
            printf("Escolha inválida.\n");
            break;
        }
    }

    return 0;
}