#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct NO {
    NO* pai;
    NO* esquerda;
    NO* direita;
    int num;
};

typedef NO no;

no* criar_raiz(int num) {
    no* raiz = new no;
    raiz->pai = nullptr;
    raiz->esquerda = nullptr;
    raiz->direita = nullptr;
    raiz->num = num;
    return raiz;
}

no* criar_no(int num) {
    no* novo_no = new no;
    novo_no->pai = nullptr;
    novo_no->esquerda = nullptr;
    novo_no->direita = nullptr;
    novo_no->num = num;
    return novo_no;
}

void inserir(int num, no* raiz) {
    no* novo_no = criar_no(num);
    no* aux = raiz;
    no* pai = nullptr;

    while (aux != nullptr) {
        pai = aux;
        if (num < aux->num) {
            aux = aux->esquerda;
        } else {
            aux = aux->direita;
        }
    }

    novo_no->pai = pai;

    if (num < pai->num) {
        pai->esquerda = novo_no;
    } else {
        pai->direita = novo_no;
    }
}

string mostrar_arv(no* no_aux) {
    if (no_aux == nullptr) {
        return "";
    }

    string esq = mostrar_arv(no_aux->esquerda);
    string dir = mostrar_arv(no_aux->direita);

    return "(" + esq + " " + to_string(no_aux->num) + " " + dir + ")";
}

void mostrar_seq_arv(no* no_aux) {
    if (no_aux != nullptr) {
        mostrar_seq_arv(no_aux->esquerda);
        cout << " " + to_string(no_aux->num) + " ";
        mostrar_seq_arv(no_aux->direita);
    }
}

void liberar_memoria(no* raiz) {
    if (raiz == nullptr) return;
    liberar_memoria(raiz->esquerda);
    liberar_memoria(raiz->direita);
    delete raiz;
}

int main() {
    no* raiz = criar_raiz(10);
    int num;

    while (true) {
        cin >> num;
        if (num == -1) break;
        inserir(num, raiz);
    }

    cout << mostrar_arv(raiz) << endl;

    mostrar_seq_arv(raiz);

    liberar_memoria(raiz);
}

