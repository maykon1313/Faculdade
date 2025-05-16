#include <iostream>
#include <string>

using namespace std;

struct no {
    struct no* esq;
    struct no* dir;
    char letra;
};

typedef struct no no;

class arv_bin {
    public:
        no* raiz = nullptr;

        no* criar_no(char letra) {
            no* node = new no;

            node->esq = nullptr;
            node->dir = nullptr;
            node->letra = letra;

            return node;
        }
        
        void inserir(char letra) {
            no* node = criar_no(letra);
            
            if (raiz == nullptr) {
                raiz = node;
            }

            else return insert_recursivo(raiz, node);
        }
        
        void insert_recursivo(no* raiz, no* novo_no) {
            if (raiz->letra > novo_no->letra) {
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
                    cout << node->letra;
                    primeiro = false;
                } else {
                    cout << " " << node->letra;
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
                    cout << node->letra;
                    primeiro = false;
                } else {
                    cout << " " << node->letra;
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
                    cout << node->letra;
                    primeiro = false;
                } else {
                    cout << " " << node->letra;
                }
            }

            return primeiro;
        }

        bool busca(no* node, char letra) {
            if (node != nullptr) {
                if (node->letra == letra) {
                    cout << letra << " existe" << endl;
                    return true;
                }

                if (node->letra > letra) {
                    if (busca(node->esq, letra)) return true;
                }

                else {
                    if (busca(node->dir, letra)) return true;
                }
            }

            return false;
        }
};

typedef class arv_bin arv_bin;

void inserir_busca(string& linha, char& letra, arv_bin& arv) {
    if (linha == "I") {
        arv.inserir(letra);
    } 
    
    else if (linha == "P") {
        if (!arv.busca(arv.raiz, letra)) {
            cout << letra << " nao existe" << endl;
        }
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
    char letra;
    arv_bin arv;

    while (cin >> linha) {
        if (linha == "I" || linha == "P") {
            cin >> letra;
            inserir_busca(linha, letra, arv);
        } else {
            print(linha, arv);
        }
        
    }

    return 0;
}
