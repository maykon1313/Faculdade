#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct node {
    int valor;
    struct node* esq;
    struct node* dir;
    struct node* pai;

    node(int num) : valor(num), esq(nullptr), dir(nullptr), pai(nullptr) {}
};

typedef struct node no;

no* ler_arvore() {
    vector<pair<int,int>> arestas;
    unordered_map<int, no*> mp;
    int n, u, v, i;
    no* pai;
    no* filho;
    no* raiz;

    cin >> n;

    if (n == 1) {
        raiz = new no(1);
        return raiz;
    }

    arestas.reserve(n-1);

    for (i = 0; i < n-1; i++) {
        cin >> u >> v;
        arestas.emplace_back(u,v);

        if (!mp.count(u)) mp[u] = new no(u);
        if (!mp.count(v)) mp[v] = new no(v);
    }

    for (pair<int,int>& p : arestas) {
        u = p.first, v = p.second;
        pai = mp [u];
        filho = mp[v];

        filho->pai = pai;

        !pai->esq ? pai->esq = filho : pai->dir = filho;
    }

    raiz = mp.begin()->second;
    while (raiz->pai) raiz = raiz->pai;
    return raiz;
}

bool isomorfas(no* arv_esq, no* arv_dir) {
    if (!arv_esq && !arv_dir) return true;
    else if (!arv_esq || !arv_dir) return false;
    else return (isomorfas(arv_esq->esq, arv_dir->esq) && isomorfas(arv_esq->dir, arv_dir->dir)) || (isomorfas(arv_esq->esq, arv_dir->dir) && isomorfas(arv_esq->dir, arv_dir->esq));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    no* raiz1 = ler_arvore();
    no* raiz2 = ler_arvore();
    
    if (isomorfas(raiz1, raiz2)) cout << 'Y';
    else cout << 'N';    
    
    return 0;
}