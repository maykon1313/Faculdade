	#include <iostream>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string>
	using namespace std;

	struct cel {
		struct cel *ant;
		char conteudo;
		struct cel *seg;
	};

	typedef struct cel celula;

	celula* inicializa_pilha();
	void inserir(celula *cabeca, char valor);
	void remover(celula *cabeca);
	void liberar(celula *cabeca);
	int tamanho(celula *cabeca);

	int main() {
		string linha;
		int caso = 1, desequilibrioEsquerda, desequilibrioDireita, operacoes;
		char caracter;
		bool pare = false;
		celula *pilha;

		while (getline(cin, linha)) {

			if (linha[0] == '-') pare = true;

			if (pare) break;

			pilha = inicializa_pilha();
			desequilibrioEsquerda = 0, desequilibrioDireita = 0;

			for (char caracter : linha) {
				if (caracter == '{') {
					inserir(pilha, caracter);
				} else if (caracter == '}') {
					if (pilha->ant != pilha && pilha->ant->conteudo == '{') {
						remover(pilha);
					} else {
						desequilibrioDireita++;
					}
				}
			}
			
			desequilibrioEsquerda = tamanho(pilha);

			operacoes = (desequilibrioEsquerda + 1) / 2 + (desequilibrioDireita + 1) / 2;

			printf("%d. %d\n", caso, operacoes);
			caso++;
			
			liberar(pilha);
		}

		return 0;
	}

	celula* inicializa_pilha() {
		celula *cabeca = (celula*) malloc(sizeof(celula));
		cabeca->seg = cabeca;
		cabeca->ant = cabeca;

		return cabeca;
	}

	void inserir(celula *cabeca, char valor) {
		celula *nova = (celula*) malloc(sizeof(celula));
		nova->conteudo = valor;

		nova->seg = cabeca;
		nova->ant = cabeca->ant;
		cabeca->ant->seg = nova;
		cabeca->ant = nova;
	}

	void remover(celula *cabeca) {
		celula *p = cabeca->ant;

		if (cabeca->ant == cabeca) return;

		p->ant->seg = cabeca;
		cabeca->ant = p->ant;

		free(p);
	}

	void liberar(celula *cabeca) {
		celula *p = cabeca->seg;

		while (p != cabeca) {
			p = p->seg;
			free(p->ant);
		}
		
		free(cabeca);
	}

	int tamanho(celula *cabeca) {
		int contador = 0;
		celula *p = cabeca->seg;

		while (p != cabeca) {
			contador++;
			p = p->seg;
		}

		return contador;
	}