#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int valor;
    struct node* esq;
    struct node* dir;

    node(int num) : valor(num), esq(nullptr), dir(nullptr) {}
};

typedef struct node no;

class ARV_BIN {
    public:
    no* raiz = nullptr;

    void inserir(int valor) {
        no* node = new no(valor);
        
        if (!raiz) raiz = node;

        no* atual = raiz;

        while (atual) {
            if (atual->valor > valor) {
                if (!atual->esq) break;
                else atual = atual->esq;
            }

            else if (atual->valor < valor) {
                if (!atual->dir) break;
                else atual = atual->dir;
            }

            else return;
        }

        if (atual->valor > valor) atual->esq = node;
        else atual->dir = node;
    }
};

typedef class ARV_BIN arv_bin;

void bfs(no* raiz) {
    queue<no*> fila;
    no* atual;
    bool primeiro = true;

    fila.push(raiz);

    while (!fila.empty()) {
        atual = fila.front();
        fila.pop();

        if (primeiro) {
            cout << atual->valor;
            primeiro = false;
        } else {
            cout << " " << atual->valor;
        }

        if (atual->esq) fila.push(atual->esq);
        if (atual->dir) fila.push(atual->dir);
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n, valor, i = 1;

    cin >> c;
    while (i <= c) {
        arv_bin arv;

        cin >> n;
        while (n--) {
            cin >> valor;
            arv.inserir(valor);
        }

        cout << "Case " << i << ":\n";
        bfs(arv.raiz);
        cout << '\n';
        i++;
    }

    return 0;
}