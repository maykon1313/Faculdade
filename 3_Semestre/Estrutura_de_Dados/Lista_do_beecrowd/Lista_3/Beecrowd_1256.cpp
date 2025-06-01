#include <iostream>

using namespace std;

struct no {
    int valor;
    struct no* prox;

    no(int num) : valor(num), prox(nullptr) {}
};

void inserir_tabela_hash(no* v[], no* novo, int m) {
    int index = novo->valor%m;
    no* aux = v[index];

    if (!aux) {
        v[index] = novo;
        return;
    }

    while (aux->prox) aux = aux->prox;
    aux->prox = novo;
}

void printar_encadeamento(int i, no* node) {
    cout << i << " -> ";
    while (node) {
        cout << node->valor << " -> ";
        node = node->prox;
    }
    cout << '\\' << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c, num, i;
    cin >> n;

    while (n--) {
        cin >> m >> c;

        no* v[m];
        for (i = 0; i < m; i++) v[i] = nullptr;

        for (i = 0; i < c; i++) {
            cin >> num;
            no* novo = new no(num);
            inserir_tabela_hash(v, novo, m);
        }

        for (i = 0; i < m; i++) {
            printar_encadeamento(i, v[i]);
        }

        if (n > 0) cout << '\n';
    }

    return 0;
}
