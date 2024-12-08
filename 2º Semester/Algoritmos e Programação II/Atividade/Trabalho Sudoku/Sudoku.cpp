#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Protótipos */
FILE* carregue(char quadro[9][9]);
FILE* carregue_continue_jogo(char quadro[9][9], char* nome_arquivo);
void carregue_novo_jogo(char quadro[9][9], char* nome_arquivo);
FILE* crie_arquivo_binario(char quadro[9][9]);
int valido(const char quadro[9][9], int x, int y, int valor);
int valido_na_coluna(const char quadro[9][9], int y, int valor);
int valido_no_quadrante(const char quadro[9][9], int x, int y, int valor);
int valido_na_linha(const char quadro[9][9], int x, int valor);
int existe_posicao_vazia(const char quadro[9][9]);
void imprima(const char quadro[9][9]);
void jogue();
void resolve_completo(FILE*, char quadro[9][9]);
void resolve_um_passo(char quadro[9][9]);
void salve_jogada_em_binario(FILE* fb, const char quadro[9][9]);

/* Funções auxiliares */
int leia_opcao();
void gen_random(char* s, const int len);
void menu();
void menu_arquivo();

/* MAIN */
int main() {
    srand(time(NULL)); // Cria uma semente aleatória para o rand.
	jogue();

	return 0;
}

FILE* carregue(char quadro[9][9]) {
	char nome_arquivo[10];
	FILE* arquivo = NULL;
	int opcao;

	menu_arquivo();
	opcao = leia_opcao();

	switch (opcao) {
	    
		// carregar novo sudoku
	case 1:
		printf("Nome do arquivo (Adicione '.txt' ao final): ");
		scanf("%s", nome_arquivo);

		carregue_novo_jogo(quadro, nome_arquivo); // Não dá para saber se ele leu corretamente o arquivo ".txt", e não pode alterar a função.
		arquivo = crie_arquivo_binario(quadro); // Cria o arquivo apesar de qualquer erro no carregamento.
		break;

		// continuar jogo
	case 2:
		printf("Nome do arquivo (Adicione '.bin' ao final): ");
		scanf("%s", nome_arquivo);

		arquivo = carregue_continue_jogo(quadro, nome_arquivo);
		break;

		// retornar ao menu anterior
	case 9:
		break; // Voltar ao menu anterior acaba retornando o ponteiro como NULL, mesmo após ter carregado um quadro.

	default:
		printf("Opção inválida!\n");
		break;
	}

	return arquivo;
}

void carregue_novo_jogo(char quadro[9][9], char* nome_arquivo) {
	FILE* arquivo = fopen(nome_arquivo, "r"); // Leitura do arquivo .txt, o binário será criado depois.

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo: %s.\n", nome_arquivo);
		return;
	}

	rewind(arquivo);

	// Ler o estado inicial do jogo
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf(arquivo, " %c", &quadro[i][j]);  // Lê os caracteres do arquivo texto
		}
	}

	printf("Novo jogo carregado com sucesso do arquivo: %s!\n", nome_arquivo);
	fclose(arquivo);
}

FILE* carregue_continue_jogo(char quadro[9][9], char* nome_arquivo) {
	FILE* arquivo = fopen(nome_arquivo, "rb+");
	int jogada;

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo: %s.\n", nome_arquivo);
		return NULL;
	}

    rewind(arquivo); // Garantir que está no começo do arquivo.
	fread(&jogada, sizeof(int), 1, arquivo);

	fseek(arquivo, sizeof(int) + (sizeof(char) * 81 * jogada), SEEK_SET); // SEEK_SET lê a partir do começo.

	fread(quadro, sizeof(char), 81, arquivo);

	return arquivo;
}

FILE* crie_arquivo_binario(char quadro[9][9]) {
	char nome_arquivo[10];
	FILE* arquivo;
	int jogada = 0;

	gen_random(nome_arquivo, 5);

	arquivo = fopen(nome_arquivo, "wb+");

	if (arquivo == NULL) {
		printf("Erro ao criar o arquivo: %s.\n", nome_arquivo);
		return NULL;
	}

	printf("\nJogada: %d.\n", jogada);

	// Escreve a matriz 9x9 diretamente no arquivo binário
	rewind(arquivo); // Garantir que está no começo do arquivo.
	fwrite(&jogada, sizeof(int), 1, arquivo);
	fwrite(quadro, sizeof(char), 81, arquivo);  // 81 é o número de elementos (9x9).

	return arquivo;
}

int valido(const char quadro[9][9], int x, int y, int valor) {
	// verifica as três condições:
	if (!valido_na_coluna(quadro, y, valor))
		return false;
	if (!valido_na_linha(quadro, x, valor))
		return false;
	if (!valido_no_quadrante(quadro, x, y, valor))
		return false;

	return true;
}

int valido_na_coluna(const char quadro[9][9], int y, int valor) {
	int i;

	for (i = 0; i < 9; i++) {
		if (quadro[i][y] == (valor + '0')) return false;
	}

	return true;
}

int valido_na_linha(const char quadro[9][9], int x, int valor) {
	int j;

	for (j = 0; j < 9; j++) {
		if (quadro[x][j] == (valor + '0')) return false;
	}

	return true;
}

int valido_no_quadrante(const char quadro[9][9], int x, int y, int valor) {
	int i, j, ini_x, ini_y;

	ini_x = (x / 3) * 3;
	ini_y = (y / 3) * 3;

	for (i = ini_x; i < ini_x + 3; i++) {
		for (j = ini_y; j < ini_y + 3; j++) {
			if (quadro[i][j] == (valor + '0')) {
				return false;
			}
		}
	}

	return true;
}

int existe_posicao_vazia(const char quadro[9][9]) {
	int i, j;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (quadro[i][j] == '0')
				return true;
		}
	}

	return false;
}

void imprima(const char quadro[9][9]) {
	int i, j;

	printf("\n~~~~~~~~~~~ SUDOKU ~~~~~~~~~~~\n");
	printf("    0 1 2   3 4 5   6 7 8\n");

	for (i = 0; i < 9; i++) {
		if (i % 3 == 0)
			printf("  -------------------------\n");

		for (j = 0; j < 9; j++) {

			if (j == 0)
				printf("%d | ", i);
			else if (j % 3 == 0)
				printf("| ");

			printf("%c ", quadro[i][j]);
		}
		printf("|\n");
	}
	printf("  -------------------------\n");
}

void jogue() {
	FILE* fb = NULL;
	int opcao = 0, x, y, valor;
	char quadro[9][9] = {
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0'}
	};

	while (opcao != 9) {
		// imprima na tela o quadro atual
		imprima(quadro);

		// apresente um menu com as opcoes
		menu();
		opcao = leia_opcao();

		switch (opcao) {

			// carregue sudoku
		case 1:
		    if (fb != NULL) {
		        fclose(fb);
		        printf("Arquivo anterior fechado.\n");
		    }
		    
			fb = carregue(quadro);

			if (fb == NULL) {
                printf("Falha ao carregar o arquivo. Tente novamente com um arquivo válido.\n");
            }
			break;

			// preencha quadro com um valor
		case 2: {
			// Verifica se o arquivo está aberto
			if (fb == NULL) {
				printf("Nenhum arquivo aberto para salvar a jogada.\n");
				break;
			}

			if (existe_posicao_vazia(quadro)) {
				printf("Entre com a posição e o valor (linha, coluna, valor): ");
				scanf("%d %d %d", &x, &y, &valor);

				if (valido(quadro, x, y, valor)) {
					quadro[x][y] = (char)(valor + '0');
					salve_jogada_em_binario(fb, quadro);
				} else {
					printf("Valor ou posição incorreta! Tente novamente!\n");
				}
			} else {
				printf("Não há posições vazias.\n");
			}
			break;
		}

			  // resolva 1 passo
		case 3:
		    if (existe_posicao_vazia(quadro)) {
			    resolve_um_passo(quadro);
			    salve_jogada_em_binario(fb, quadro);
		    } else {
		        printf("Nenhum passo para resolver.\n");
		    }
		    
			break;

			// resolva o sudoku completo
		case 4:
			resolve_completo(fb, quadro);
			break;

		case 9:
			if (fb == NULL) {
				printf("Nenhum arquivo aberto para fechar.\n");
			} 
			else {
				fclose(fb);
				printf("Arquivo fechado.\n");
			}
			
			printf("Programa finalizado.\n");
			break;

		default:
			printf("Opção inválida! Tente novamente!\n");
			break;
		}
	}
}

void resolve_completo(FILE* fb, char quadro[9][9]) {
    if (existe_posicao_vazia(quadro)) {
    	while (existe_posicao_vazia(quadro)) {
    		resolve_um_passo(quadro);
    		salve_jogada_em_binario(fb, quadro);
    	}
    } else {
        printf("Nenhum passo para resolver.\n");
    }
}

void resolve_um_passo(char quadro[9][9]) {
	int i, j, z, cont, ultima_resposta, quebra = 0;
	int quadrante_i, quadrante_j;
	int presente[9] = { 0 };
	int linha_vazia = -1, coluna_vazia = -1;
	int num_faltante;
	char valor;

	// Primeiro, percorre todas as posições
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (quadro[i][j] == '0') {
				cont = 0; // Contador de quantas respostas válidas

				for (z = 1; z < 10; z++) {
					if (valido(quadro, i, j, z)) {
						ultima_resposta = z;
						cont++;
					}

					if (cont > 1) break;
				}

				// Se houver exatamente uma resposta válida
				if (cont == 1) {
					quadro[i][j] = ultima_resposta + '0';
					printf("Um passo resolvido!\n");
					return;
				}
			}
		}
	}

	// Se nenhum for resolvido
	for (quadrante_i = 0; quadrante_i < 9; quadrante_i += 3) {
		for (quadrante_j = 0; quadrante_j < 9; quadrante_j += 3) {

			for (z = 0; z < 9; z++) {
				presente[z] = 0;
			}

			linha_vazia = -1;
			coluna_vazia = -1;
			cont = 0;
			quebra = 0;

			// Verificar o quadrante 3x3
			for (i = quadrante_i; i < quadrante_i + 3 && !quebra; i++) {
				for (j = quadrante_j; j < quadrante_j + 3 && !quebra; j++) {
					valor = quadro[i][j];
					if (valor != '0') {
						presente[valor - '1'] = 1;  // Marcar o número como presente
					} else {
						coluna_vazia = j;
						cont++;
						
						if (cont >= 2) quebra = 1;
					}
				}
			}

			// Se houver exatamente uma célula vazia, preencha-a com o número faltante
			if (cont == 1) {
				for (num_faltante = 0; num_faltante < 9; num_faltante++) {
					if (!presente[num_faltante]) {
						quadro[linha_vazia][coluna_vazia] = (num_faltante + 1) + '0';
						printf("Um passo resolvido pelo quadrante!\n");
						return;
					}
				}
			}
		}
	}
	
	printf("Nenhum passo resolvido.\n");
}

void salve_jogada_em_binario(FILE* fb, const char quadro[9][9]) {
	int jogada;

	if (fb == NULL) {
		printf("O arquivo binário não está aberto!\n");
		return;
	}

	rewind(fb);
	fread(&jogada, sizeof(int), 1, fb);

	jogada++;

	printf("\nJogada: %d.\n", jogada);

	rewind(fb);
	fwrite(&jogada, sizeof(int), 1, fb);

	fseek(fb, 0, SEEK_END);
	fwrite(quadro, sizeof(char), 81, fb);

	printf("Estado do jogo salvo com sucesso!\n");
}

void gen_random(char* s, const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	int i;

	for (i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
    
    s[i] = '.';
    s[i+1] = 'b';
    s[i+2] = 'i';
    s[i+3] = 'n';
    
	// Finaliza a string com o caractere nulo ('\0').
	s[i+4] = '\0';
}

int leia_opcao() {
	int opcao;

	printf("Opção: ");
	scanf("%d", &opcao);

	return opcao;
}

void menu() {
	printf("\n~~~~~~~~ SUDOKU ~~~~~~~~\n");
	printf("[1] - Carregar jogo.\n");
	printf("[2] - Jogar.\n");
	printf("[3] - Resolver um passo.\n");
	printf("[4] - Resolver.\n");
	printf("[9] - Finalizar.\n");
	printf("------------------------\n");
}

void menu_arquivo() {
	printf("\n~~~~~ MENU ARQUIVO ~~~~~\n");
	printf("[1] - Novo jogo.\n");
	printf("[2] - Continuar jogo.\n");
	printf("[9] - Retornar ao menu anterior.\n");
	printf("--------\n");
}