#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct no {
    struct no* esq;
    struct no* dir;
    int valor;
};

typedef struct no no;

class arv_bin {
    public:
        no* raiz = nullptr;

        no* criar_no(int valor) {
            no* node = new no;

            node->esq = nullptr;
            node->dir = nullptr;
            node->valor = valor;

            return node;
        }
        
        void inserir(int valor) {
            no* node = criar_no(valor);
            
            if (raiz == nullptr) {
                raiz = node;
            }

            else return insert_recursivo(raiz, node);
        }
        
        void insert_recursivo(no* raiz, no* novo_no) {
            if (raiz->valor > novo_no->valor) {
                if (raiz->esq == nullptr) raiz->esq = novo_no;
                else insert_recursivo(raiz->esq, novo_no);
            } else {
                if (raiz->dir == nullptr) raiz->dir = novo_no;
                else insert_recursivo(raiz->dir, novo_no);
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

        bool busca(no* node, int valor) {
            if (node != nullptr) {
                if (node->valor == valor) {
                    cout << valor << " existe" << endl;
                    return true;
                }

                if (node->valor > valor) {
                    if (busca(node->esq, valor)) return true;
                }

                else {
                    if (busca(node->dir, valor)) return true;
                }
            }

            return false;
        }
};

typedef class arv_bin arv_bin;

void remover(no*& raiz, int valor) {
    if (raiz == nullptr) return;

    if (valor < raiz->valor) {
        remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        remover(raiz->dir, valor);
    } else {
        if (raiz->esq == nullptr) {
            no* temp = raiz;
            raiz = raiz->dir;
            delete temp;
        } else if (raiz->dir == nullptr) {
            no* temp = raiz;
            raiz = raiz->esq;
            delete temp;
        } else {
            no* temp = raiz->dir;
            while (temp->esq != nullptr) {
                temp = temp->esq;
            }
            raiz->valor = temp->valor;
            remover(raiz->dir, temp->valor);
        }
    }
}

void inserir_iterativo(int valor, arv_bin& arv) {
    no* node = arv.criar_no(valor);
    if (arv.raiz == nullptr) {
        arv.raiz = node;
        return;
    }

    no* atual = arv.raiz;
    no* anterior = nullptr;

    while (atual != nullptr) {
        anterior = atual;
        if (valor < atual->valor) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (valor < anterior->valor) {
        anterior->esq = node;
    } else {
        anterior->dir = node;
    }
}

bool busca_iterativa(no* raiz, int valor) {
    while (raiz != nullptr) {
        if (raiz->valor == valor) {
            cout << valor << " existe" << endl;
            return true;
        } else if (valor < raiz->valor) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return false;
}

void inserir_busca(string& linha, int& valor, arv_bin& arv) {
    if (linha == "I") {
        inserir_iterativo(valor, arv);
    } 
    
    else if (linha == "P") {
        if (!busca_iterativa(arv.raiz, valor)) {
            cout << valor << " nao existe" << endl;
        }
    } else if (linha == "R") {
        remover(arv.raiz, valor);
    }
}

void print(string& linha, arv_bin& arv) {
    bool p;
    if (linha == "INFIXA") {
        p = arv.in(arv.raiz, true);
        cout << endl;
    }

    else if (linha == "PREFIXA") {
        p = arv.pre(arv.raiz, true);
        cout << endl;
    }

    else if (linha == "POSFIXA") {
        p = arv.pos(arv.raiz, true);
        cout << endl;
    }
}

int main() {
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
