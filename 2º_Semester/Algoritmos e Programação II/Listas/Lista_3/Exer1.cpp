#include <stdio.h>

struct participante_1 {
    char nome[30];
    char cpf[12];
    char tipo_de_part;
    char socio_sbc;
};

typedef struct {
    char nome[30];
    char cpf[12];
    char tipo_de_part;
    char socio_sbc;
} participante_2;

int calcula_preco(struct participante_1 a) {
    int preco = 0;
    if (a.tipo_de_part == 'A') {
        preco = 30;
    } else if (a.tipo_de_part == 'B') {
        preco = 60;
    } else if (a.tipo_de_part == 'C') {
        preco = 90;
    } else {
        preco = 100;
    }
    
    if (a.socio_sbc == 'S') {
        preco = preco * 0.8;
    }

    return preco;
}

int main() {
    struct participante_1 a;
    int preco = 0;

    printf("Nome: ");
    scanf("%s%*c", a.nome);
    printf("CPF: ");
    scanf("%s%*c", a.cpf);
    printf("Tipo de participação (A, B, C, D): ");
    scanf("%c%*c", &a.tipo_de_part);
    printf("Sócio SBC (S/N): ");
    scanf("%s%*c", &a.socio_sbc);

    preco = calcula_preco(a);
    
    
    printf("O participante %s que possuí o CPF %s terá que pagar: %d.\n", a.nome, a.cpf, preco);

    return 0;
}