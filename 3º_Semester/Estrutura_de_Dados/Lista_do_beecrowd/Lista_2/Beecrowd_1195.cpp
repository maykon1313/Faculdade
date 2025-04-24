#include <iostream>

using namespace std;

struct no {
    struct no* esq;
    struct no* dir;
    int num;
};

typedef struct no no;

class arv_bin {
    public:
        no* raiz = nullptr;

        no* criar_no(int num) {
            no* node = new no;

            node->esq = nullptr;
            node->dir = nullptr;
            node->num = num;

            return node;
        }
        
        void inserir(int num) {
            no* node = criar_no(num);
            
            if (raiz == nullptr) {
                raiz = node;
            }

            else return insert_recursivo(raiz, node);
        }
        
        void insert_recursivo(no* raiz, no* novo_no) {
            if (raiz->num > novo_no->num) {
                if (raiz->esq == nullptr) raiz->esq = novo_no;
                else insert_recursivo(raiz->esq, novo_no);
            } else {
                if (raiz->dir == nullptr) raiz->dir = novo_no;
                else insert_recursivo(raiz->dir, novo_no);
            }
        }

        void saida() {
            cout << "Pre.:";
            pre(raiz); // RED
            cout << endl;

            cout << "In..:";
            in(raiz);  // ERD
            cout << endl;

            cout << "Post:";
            pos(raiz); // EDR
            cout << endl;
        }

        void pre(no* node) {
            if (node != nullptr) {
                cout << " " << node->num;
                pre(node->esq);
                pre(node->dir);
            }
        }

        void in(no* node) {
            if (node != nullptr) {
                in(node->esq);
                cout << " " << node->num;
                in(node->dir);
            }
        }

        void pos(no* node) {
            if (node != nullptr) {
                pos(node->esq);
                pos(node->dir);
                cout << " " << node->num;
            }
        }
};

typedef class arv_bin arv_bin;

int main() {
    int t, n, no, i = 1;

    cin >> t;

    while (i <= t) {
        arv_bin arv;

        cin >> n;

        while (n--) {
            cin >> no;
            arv.inserir(no);
        }

        cout << "Case " << i << ":" << endl;

        arv.saida();

        cout << endl;
        i++;
    }

    return 0;
}
