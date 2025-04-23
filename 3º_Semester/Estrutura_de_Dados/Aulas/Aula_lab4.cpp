#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

enum TipoNo {
    FOLHA,
    F_DIR,
    F_ESQ
};

struct AVL_no {
    int num;
    AVL_no* pai;
    AVL_no* esq;
    AVL_no* dir;
    int b;
};

typedef struct AVL_no no;

class AVL_arvore {
    no* raiz = nullptr;

    public:
        ~AVL_arvore() {
            if (!no_vazio(raiz)) liberar_memoria();
        }

        void liberar_memoria() {
            if (no_vazio(raiz)) return;
            else liberar_memoria_recursivo(raiz);
        }

        void liberar_memoria_recursivo(no* node) {
            if (!no_vazio(node)) {
                liberar_memoria_recursivo(node->esq);
                liberar_memoria_recursivo(node->dir);
                delete node;
            }
        }

        int altura() {
            no* aux;

            if (no_vazio(raiz)) {
                cout << "Árvore vazia.\n";
                return -1;
            }

            else {
                return calcular_altura(raiz);
            }
        }

        int calcular_altura(no* node) {
            int altura_esq, altura_dir;
            if (!no_vazio(node)) {
                altura_esq = calcular_altura(node->esq);
                altura_dir = calcular_altura(node->dir);

                if (altura_esq > altura_dir) return altura_esq + 1;
                else return altura_dir + 1;
            }

            else {
                return 0;
            }
        }
        
        bool no_vazio(no* node) {
            return node == nullptr;
        }

        TipoNo condicao_no(no* node) {
            if (node->esq == nullptr && node->dir == nullptr) return FOLHA;
            else if (node->dir != nullptr) return F_DIR;
            else return F_ESQ;
        }
        
        void rotacao_dir(no* node) {
            no* aux = node->esq;
            node->esq = aux->dir;

            if (!no_vazio(aux->dir)) aux->dir->pai = node;

            aux->pai = node->pai;

            if (no_vazio(node->pai)) raiz = aux;
            else if (node == node->pai->esq) node->pai->esq = aux;
            else node->pai->dir = aux;

            aux->dir = node;
            node->pai = aux;

            node->b = node->b - 1 + min(0, aux->b);
            aux->b = aux->b - 1 - max(0, node->b);
        }

        void rotacao_esq(no* node) {
            no* aux = node->dir;
            node->dir = aux->esq;

            if (!no_vazio(aux->esq)) aux->esq->pai = node;

            aux->pai = node->pai;

            if (no_vazio(node->pai)) raiz = aux;
            else if (node == node->pai->esq) node->pai->esq = aux;
            else node->pai->dir = aux;

            aux->esq = node;
            node->pai = aux;

            node->b = node->b + 1 - min(0, aux->b);
            aux->b = aux->b + 1 + max(0, node->b);
        }

        void rotacao(no* node) {
            if (node->b == 2) {
                if (node->esq->b >= 0) {
                    rotacao_dir(node);
                } else {
                    rotacao_esq(node->esq);
                    rotacao_dir(node);
                }
            } else if (node->b == -2) {
                if (node->dir->b <= 0) {
                    rotacao_esq(node);
                } else {
                    rotacao_dir(node->dir);
                    rotacao_esq(node);
                }
            }
        }

        void atualizar_balanco(no* node) {
            no* pai = node->pai;

            while (!no_vazio(pai)) {
                if (node == pai->esq) pai->b--;
                else pai->b++;

                if (pai->b == 0) break;
                else if (pai->b == -2 || pai->b == 2) {
                    rotacao(pai);
                    break;
                }

                node = pai;
                pai = node->pai;
            }
        }

        bool insert(no* novo_no) {
            if (no_vazio(raiz)) {
                raiz = novo_no;
                return true;
            }

            else return insert_recursivo(raiz, novo_no);
        }

        bool insert_recursivo(no* node, no* novo_no) {
            if (novo_no->num == node->num) return false;
            
            else if (novo_no->num < node->num) {
                if (node->esq == nullptr) {
                    node->esq = novo_no;
                    novo_no->pai = node;
                    atualizar_balanco(novo_no);
                    return true;
                } 

                else {
                    return insert_recursivo(node->esq, novo_no);
                }
            }

            else {
                if (node->dir == nullptr) {
                    node->dir = novo_no;
                    novo_no->pai = node;
                    atualizar_balanco(novo_no);
                    return true;
                } 

                else {
                    return insert_recursivo(node->dir, novo_no);
                }
            }
        }

        void print() {
            if (no_vazio(raiz)) cout << "Árvore vazia.\n";
            else {
                in_order_recursivo(raiz);
                cout << "\n";
            }
        }

        void in_order_recursivo(no* node) {
            if (node != nullptr) {
                in_order_recursivo(node->esq);
                cout << " " << node->num << " ";
                in_order_recursivo(node->dir);
            }
        }

        no* busca(no* node, int num) {
            if (no_vazio(node) || node->num == num) return node;
            else if (node->num > num) return busca(node->esq, num);
            else return busca(node->dir, num);
        }

        no* sucessor(no* node) {
            node = node->dir;
            while(node->esq != nullptr) node = node->esq;
            return node;
        }

        void transplantar(no* u, no* v) {
            if (no_vazio(u->pai)) raiz = v;
            else if (u == u->pai->esq) u->pai->esq = v;
            else u->pai->dir = v;

            if (!no_vazio(v)) v->pai = u->pai;
        }

        bool remover(int num) {
            no* aux;

            if (no_vazio(raiz)) {
                cout << "Árvore vazia.\n";
                return false;
            }

            aux = busca(raiz, num);

            if (no_vazio(aux)) {
                cout << "Nó não encontrado na árvore.\n";
                return false;
            }

            else {
                remover_com_busca(aux);
                return true;
            }
        }

        void remover_com_busca(no* node) {
            no* aux;
            no* pai = node->pai;
            int balanceamento_ajustado = 0;

            if (no_vazio(node->esq)) {
                transplantar(node, node->dir);
                balanceamento_ajustado = -1;
            } else if (no_vazio(node->dir)) {
                transplantar(node, node->esq);
                balanceamento_ajustado = 1;
            } else {
                aux = sucessor(node);

                if (aux->pai != node) {
                    transplantar(aux, aux->dir);
                    aux->dir = node->dir;
                    aux->dir->pai = aux;
                }

                transplantar(node, aux);
                aux->esq = node->esq;
                aux->esq->pai = aux;
                aux->b = node->b;
            }

            delete node;

            while (!no_vazio(pai)) {
                pai->b += balanceamento_ajustado;

                if (pai->b == -2 || pai->b == 2) {
                    rotacao(pai);
                    break;
                } else if (pai->b != 0) {
                    break;
                }

                balanceamento_ajustado = (pai->pai && pai == pai->pai->esq) ? 1 : -1;
                pai = pai->pai;
            }
        } 
};

typedef class AVL_arvore arv;

no* criar_novo_no(int num) {
    no* novo_no = new no;

    novo_no->num = num;
    novo_no->pai = nullptr;
    novo_no->esq = nullptr;
    novo_no->dir = nullptr;
    novo_no->b = 0;

    return novo_no;
}

int menu() {
    int escolha;

    cout << "\nO que deseja fazer?\n";
    cout << "1 - Gerar árvore com valores aleatórios.\n";
    cout << "2 - Inserir nó(s) na árvore.\n";
    cout << "3 - Remover nó(s) na árvore.\n";
    cout << "4 - Mostrar a árvore.\n";
    cout << "5 - Calcular altura da árvore.\n";
    cout << "6 - Sair.\n";

    cin >> escolha;
    return escolha;
}

int main() {
    srand(time(nullptr));

    int i, j, escolha, aux;
    bool continua = true;
    no* novo_no;
    arv T;

    while (continua) {
        escolha = menu();

        if (escolha == 1) {
            T.liberar_memoria();

            cout << "Quantos nós?\n";
            cin >> j;

            for (i = 0; i < j;) {
                novo_no = criar_novo_no(rand() % j);

                if (T.insert(novo_no)) {
                    T.print();
                    i++;
                }
                else {
                    delete novo_no;
                }
            }
        }

        else if (escolha == 2) {
            cout << "Quantos nós?\n";
            cin >> j;

            for (i = 0; i < j;) {
                cout << "valor do nó.\n";
                cin >> aux;

                novo_no = criar_novo_no(aux);

                if (T.insert(novo_no)) {
                    T.print();
                    i++;
                }
                else {
                    cout << "Nó já está na árvore, não foi aceito.\n";
                    delete novo_no;
                }
            }
        }

        else if (escolha == 3) {
            cout << "Quantos nós?\n";
            cin >> j;

            for (i = 0; i < j; i++) {
                cout << "valor do nó.\n";
                cin >> aux;

                if (T.remover(aux)) {
                    cout << "Nó removido.\n";
                    T.print();
                }
            }
        }

        else if (escolha == 4) {
            T.print();
        }
        
        else if (escolha == 5) {
            aux = T.altura();
            cout << "A altura da árvore é: " << aux << "\n";
        }

        else if (escolha == 6) {
            continua = false;
        }

        else {
            cout << "Escolha inválida.\n";
        }
    }
    
    return 0;
}
