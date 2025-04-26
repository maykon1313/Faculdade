#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct no {
    int valor;
    struct no* esq;
    struct no* dir;
    struct no* pai;
    int altura;

    no(int num) : valor(num), esq(nullptr), dir(nullptr), altura(1) {}
};

typedef struct no no;

class ARV_BIN {
    public:
    no* raiz = nullptr;

    int altura_arv() {
        return raiz->altura;
    }

    int altura_no(no* node) {
        return node == nullptr ? 0 : node->altura;
    }

    void atualizar_altura(no* node) {
        node->altura = 1 + max(altura_no(node->esq), altura_no(node->dir));
    }

    int fator_balanceamento(no* node) {
        return node == nullptr ? 0 : altura_no(node->esq) - altura_no(node->dir);
    }

    no* rotacao_direita(no* y) {
        no* x = y->esq;
        no* T2 = x->dir;

        x->dir = y;
        y->esq = T2;

        if (T2 != nullptr) T2->pai = y;
        x->pai = y->pai;
        y->pai = x;

        atualizar_altura(y);
        atualizar_altura(x);

        return x;
    }

    no* rotacao_esquerda(no* x) {
        no* y = x->dir;
        no* T2 = y->esq;

        y->esq = x;
        x->dir = T2;

        if (T2 != nullptr) T2->pai = x;
        y->pai = x->pai;
        x->pai = y;

        atualizar_altura(x);
        atualizar_altura(y);

        return y;
    }

    no* balancear(no* node) {
        int fb = fator_balanceamento(node);

        if (fb > 1 && fator_balanceamento(node->esq) >= 0) {
            return rotacao_direita(node);
        }

        if (fb > 1 && fator_balanceamento(node->esq) < 0) {
            node->esq = rotacao_esquerda(node->esq);
            return rotacao_direita(node);
        }

        if (fb < -1 && fator_balanceamento(node->dir) <= 0) {
            return rotacao_esquerda(node);
        }

        if (fb < -1 && fator_balanceamento(node->dir) > 0) {
            node->dir = rotacao_direita(node->dir);
            return rotacao_esquerda(node);
        }

        return node;
    }

    void inserir(int valor) {
        no* novo = new no(valor);

        if (raiz == nullptr) {
            raiz = novo;
            return;
        }

        no* aux;
        no* atual = raiz;
        no* pai = nullptr;

        while (atual != nullptr) {
            pai = atual;
            if (valor < atual->valor) {
                atual = atual->esq;
            } else if (valor > atual->valor) {
                atual = atual->dir;
            } else {
                delete novo;
                return;
            }
        }

        novo->pai = pai;
        if (valor < pai->valor) {
            pai->esq = novo;
        } else {
            pai->dir = novo;
        }

        atual = novo;
        while (atual != nullptr) {
            atualizar_altura(atual);
            aux = balancear(atual);
            
            if (aux->pai == nullptr) {
                raiz = aux;
            }

            atual = atual->pai;
        }
    }

    no* busca(int valor) {
        no* atual = raiz;

            while (atual != nullptr) {
                if (atual->valor == valor) return atual;

                if (valor < atual->valor) {
                    atual = atual->esq;
                } else {
                    atual = atual->dir;
                }
            }

        return nullptr;
    }

    int n_filhos(no* node) {
        if (node->dir == nullptr && node->esq == nullptr) return 0;
        else if (node->dir != nullptr && node->esq != nullptr) return 2;
        else return 1;
    }

    no* sucessor(no* node) {
        no* aux = node->dir;
        while (aux->esq != nullptr) aux = aux->esq;
        return aux;
    }

    void remover(int valor) {
        no* node = busca(valor);
        if (node == nullptr) return;

        no* substituto;
        if (n_filhos(node) == 0) {
            substituto = nullptr;
        } else if (n_filhos(node) == 1) {
            substituto = (node->esq != nullptr) ? node->esq : node->dir;
        } else {
            substituto = sucessor(node);
            remover(substituto->valor);
            substituto->esq = node->esq;
            substituto->dir = node->dir;
            if (substituto->esq != nullptr) substituto->esq->pai = substituto;
            if (substituto->dir != nullptr) substituto->dir->pai = substituto;
        }

        if (node->pai == nullptr) {
            raiz = substituto;
        } else if (node == node->pai->esq) {
            node->pai->esq = substituto;
        } else {
            node->pai->dir = substituto;
        }

        if (substituto != nullptr) substituto->pai = node->pai;

        no* atual = substituto != nullptr ? substituto : node->pai;
        while (atual != nullptr) {
            atualizar_altura(atual);
            atual = balancear(atual);
            if (atual->pai == nullptr) raiz = atual;
            atual = atual->pai;
        }

        delete node;
    }
    
    void imprimir(int valor, bool& primeiro) {
        if (primeiro) {
            cout << valor;
            primeiro = false;
        } else {
            cout << " " << valor;
        }
    }

    void in_recursivo(no* node, bool& primeiro) {
        if (node == nullptr) return;
        in_recursivo(node->esq, primeiro);
        imprimir(node->valor, primeiro);
        in_recursivo(node->dir, primeiro);
    }

    void pre_recursivo(no* node, bool& primeiro) {
        if (node == nullptr) return;
        imprimir(node->valor, primeiro);
        in_recursivo(node->esq, primeiro);
        in_recursivo(node->dir, primeiro);
    }

    void pos_recursivo(no* node, bool& primeiro) {
        if (node == nullptr) return;
        in_recursivo(node->esq, primeiro);
        in_recursivo(node->dir, primeiro);
        imprimir(node->valor, primeiro);
    }

    void in() {
        bool primeiro = true;
        in_recursivo(raiz, primeiro);
    }

    void pre() {
        bool primeiro = true;
        pre_recursivo(raiz, primeiro);
    }

    void pos() {
        bool primeiro = true;
        pos_recursivo(raiz, primeiro);
    }
};

typedef class ARV_BIN arv_bin;

void inserir_busca(string& linha, int& valor, arv_bin& arv) {
    if (linha == "I") {
        arv.inserir(valor);
    } 
    
    else if (linha == "P") {
        if (arv.busca(valor) != nullptr) {
            cout << valor << " existe" << endl;
        } else {
            cout << valor << " nao existe" << endl;
        }
    }

    else if (linha == "R") {
        arv.remover(valor);
    }
}

void print(string& linha, arv_bin& arv) {
    if (linha == "INFIXA") {
        arv.in();
        cout << endl;
    }

    else if (linha == "PREFIXA") {
        arv.pre();
        cout << endl;
    }

    else if (linha == "POSFIXA") {
        arv.pos();
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string linha;
    int valor;
    arv_bin arv;

    while (cin >> linha) {
        if (linha == "I" || linha == "P" || linha == "R") {
            cin >> valor;
            inserir_busca(linha, valor, arv);
        } else {
            print(linha, arv);
        }
    }

    return 0;
}
