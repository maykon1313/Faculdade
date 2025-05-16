#include <iostream>

using namespace std;

struct no {
    int valor;
    struct no* esq;
    struct no* dir;
    struct no* pai;

    no(int num) : valor(num), esq(nullptr), dir(nullptr), pai(nullptr) {}
};

typedef struct no no;

class arv_bin {
    public:
    no* raiz = nullptr;
    
    void inserir(int valor) {
        no* node = new no(valor);

        if (!raiz) {
            raiz = node;
            return;
        }

        no* atual = raiz;

        while (true) {
            if (atual->valor > valor && atual->esq) atual = atual->esq;
            else if (atual->valor < valor && atual->dir) atual = atual->dir;
            else break;
        }

        if (atual->valor > valor) atual->esq = node;
        else atual->dir = node;

        node->pai = atual;
    }
    
    no* busca(int valor) {
        no* atual = raiz;

        while (true) {
            if (atual->valor > valor && atual->esq) atual = atual->esq;
            else if (atual->valor < valor && atual->dir) atual = atual->dir;
            else if (atual->valor == valor) return atual;
            else break;
        }

        return nullptr;
    }   
    
    void remover(int valor) {
        no* atual = busca(valor);
        if (!atual) return;

        no* filho;
        no* antecessor;

        // 0 filho(s):
        if (!atual->esq && !atual->dir) {
            if (atual->pai) {
                if (atual->pai->esq == atual) atual->pai->esq = nullptr;
                else atual->pai->dir = nullptr;
            } 
            
            else {
                raiz = nullptr;
            }

            delete atual;
        }

        // 1 filho(s):
        else if (!atual->esq || !atual->dir) {
            filho = atual->esq ? atual->esq : atual->dir;

            if (!atual->pai) {
                raiz = filho;
                filho->pai = nullptr;
            } 
            
            else {
                if (atual->pai->esq == atual) atual->pai->esq = filho;
                else atual->pai->dir = filho;
                filho->pai = atual->pai;
            }

            delete atual;
        }

        // 2 filho(s):
        else {
            antecessor = atual->esq;
            while (antecessor->dir) antecessor = antecessor->dir;

            atual->valor = antecessor->valor;

            if (antecessor->esq) antecessor->esq->pai = antecessor->pai;

            if (antecessor->pai->esq == antecessor) antecessor->pai->esq = antecessor->esq;
            else antecessor->pai->dir = antecessor->esq;

            delete antecessor;
        }
    }

    bool pre(no* node, bool primeiro) {
        if (node != nullptr) {
            if (primeiro) {
                cout << node->valor;
                primeiro = false;
            } else {
                cout << " " << node->valor;
            }

            primeiro = pre(node->esq, primeiro);
            primeiro = pre(node->dir, primeiro);
        }

        return primeiro;
    }

    bool in(no* node, bool primeiro) {
        if (node != nullptr) {
            primeiro = in(node->esq, primeiro);
            
            if (primeiro) {
                cout << node->valor;
                primeiro = false;
            } else {
                cout << " " << node->valor;
            }

            primeiro = in(node->dir, primeiro);
        }

        return primeiro;
    }

    bool pos(no* node, bool primeiro) {
        if (node != nullptr) {
            primeiro = pos(node->esq, primeiro);
            primeiro = pos(node->dir, primeiro);
            
            if (primeiro) {
                cout << node->valor;
                primeiro = false;
            } else {
                cout << " " << node->valor;
            }
        }

        return primeiro;
    }
};

typedef class arv_bin arv_bin;

void inserir_busca(string& linha, int& valor, arv_bin& arv) {
    if (linha == "I") {
        arv.inserir(valor);
    } 
    
    else if (linha == "P") {
        if (arv.busca(valor)) {
            cout << valor << " existe" << endl;
        }
        
        else {
            cout << valor << " nao existe" << endl;
        }
    } 
    
    else if (linha == "R") {
        arv.remover(valor);
    }
}

void print(string& linha, arv_bin& arv) {
    if (linha == "INFIXA") {
        arv.in(arv.raiz, true);
        cout << endl;
    }

    else if (linha == "PREFIXA") {
        arv.pre(arv.raiz, true);
        cout << endl;
    }

    else if (linha == "POSFIXA") {
        arv.pos(arv.raiz, true);
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
