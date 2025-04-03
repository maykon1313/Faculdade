#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

struct AVL_Node {
    int num;
    AVL_Node* left;
    AVL_Node* right;
    AVL_Node* parent;
    int b;
};
typedef struct AVL_Node no;

class Node {
    public:
        static AVL_Node* create(int value) {
            return new AVL_Node{value, nullptr, nullptr, nullptr, 0};
        }
};
typedef Node node;

class arv {
    no* raiz;

    public:
        arv() {
            raiz = nullptr;
        }

        ~arv() {
            destroy(raiz);
        }

        void destroy(no* node) {
            if (node != nullptr) {
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

        bool insert(no* novo_no) {
            if (raiz == nullptr) {
                raiz = novo_no;
                novo_no->parent = nullptr;
                return true;
            }

            no* aux = raiz;
            no* ant = aux;

            while (aux != nullptr) {
                ant = aux;

                if (aux->num < novo_no->num) {
                    aux = aux->right;
                } else if (aux->num > novo_no->num) {
                    aux = aux->left;
                } else {
                    // Duplicate value, do not insert
                    return false;
                }
            }

            if (ant->num < novo_no->num) {
                ant->right = novo_no;
            } else {
                ant->left = novo_no;
            }

            novo_no->parent = ant;
            return true;
        }

        void print() {
            print_ERD(raiz);
            cout << endl;
        }
        
        void print_ERD(no* no) {
            if (no != nullptr) {
                print_ERD(no->left);
                cout << " " << no->num << " ";
                print_ERD(no->right);
            }
        }

        no* busca(int num) {
            no* aux = raiz;
            while (aux != nullptr) {
                if (aux->num == num) {
                    return aux;
                } else if (aux->num < num) {
                    aux = aux->right;
                } else {
                    aux = aux->left;
                }
            }
            return nullptr;
        }
        
        bool folha(no* p) {
            return (p->left == nullptr && p->right == nullptr);
        }

        no* sucessor(no* p) {
            no* atual = p->right;
            while (atual->left != nullptr) {
                atual = atual->left;
            }
            return atual;
        }

        void remover(no* p) {
            if (p == nullptr) {
                cout << "Nó inválido." << endl;
                return;
            }

            // Caso 1: p é folha.
            if (folha(p)) {
                if (p->parent == nullptr) {
                    raiz = nullptr;
                } else if (p->parent->right == p) {
                    p->parent->right = nullptr;
                } else {
                    p->parent->left = nullptr;
                }
                delete p;
                return;
            }

            // Caso 2: p possuí filho direito.
            if (p->right != nullptr) {
                no* q = sucessor(p);
                p->num = q->num;

                if (q->parent->left == q) {
                    q->parent->left = q->right;
                } else {
                    q->parent->right = q->right;
                }

                if (q->right != nullptr) {
                    q->right->parent = q->parent;
                }

                delete q;
                return;
            }
            
            // Caso 3: p não possuí filho direito.
            if (p->parent != nullptr) {
                if (p->parent->left == p) {
                    p->parent->left = p->left;
                } else {
                    p->parent->right = p->left;
                }
                
                if (p->left != nullptr) {
                    p->left->parent = p->parent;
                }
            } else {
                raiz = p->left;
                if (raiz != nullptr) {
                    raiz->parent = nullptr;
                }
            }
            delete p;
        }
};

int main() {
    srand(time(nullptr)); // Seed random number generator

    arv AVL;

    for (int i = 1; i <= 10;) {
        no* novo_no = node::create(rand() % 21);

        if (AVL.insert(novo_no)) {
            i++;
        } else {
            delete novo_no; // Avoid memory leak
        }
    }

    AVL.print();

    no* node_to_remove = AVL.busca(5);
    if (node_to_remove != nullptr) {
        AVL.remover(node_to_remove);
        cout << "Nó 5 removido." << endl;
    } else {
        cout << "Nó 5 não encontrado." << endl;
    }

    AVL.print();
    return 0;
}