#include <iostream>
#include <vector>

using namespace std;

struct nos {
    char pai;
    int valor;
    struct nos* esq;
    struct nos* dir;

    nos(int num) : valor(num), esq(nullptr), dir(nullptr) {}
};

typedef struct nos NO;

class arv {
    NO* raiz = nullptr;

    void inserir(int num) {
        NO* no = new NO(num);
        NO* aux = raiz;

        if (raiz == nullptr) {
            raiz = no;
            return;
        }

        while (aux) {
            if (num < aux->valor) {
                if (aux->esq) aux = aux->esq;
                else aux->esq = no;
            }

            else {

            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    vector<int> vetor;
    string entrada;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p;
        vetor.push_back(p);
    }
    cin >> entrada;

    return 0;
}