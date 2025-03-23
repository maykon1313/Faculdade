// Não funcionou através da recursão
/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct no {
    int left = 0;
    int mid = 0;
    int right = 0;
};

int maior_seq(int no_idx, vector<no>& v, int num) {
    if (no_idx == 0 || no_idx >= v.size()) return num - 1;

    int n_mid = maior_seq(v[no_idx].mid, v, num + 1);
    int n_left = maior_seq(v[no_idx].left, v, 1);
    int n_right = maior_seq(v[no_idx].right, v, 1);

    return max({n_mid, n_left, n_right});
}

int main() {
    int n_arv1 = 0, n_arv2 = 0;
    int num, left, mid, right;

    // Árvore 1
    cin >> n_arv1;    
    vector<no> arv_canhota(n_arv1 + 1);

    for (int i = 0; i < n_arv1; i++) {
        cin >> num >> left >> mid;
        arv_canhota[num].left = left;
        arv_canhota[num].mid = mid;
        arv_canhota[num].right = 0;
    }

    // Árvore 2
    cin >> n_arv2;    
    vector<no> arv_destra(n_arv2 + 1);

    for (int i = 0; i < n_arv2; i++) {
        cin >> num >> mid >> right;
        arv_destra[num].left = 0;
        arv_destra[num].mid = mid;
        arv_destra[num].right = right;
    }

    // Encontrar a maior sequência descendente da árvore canhota (começando da raiz, que é o nó 1)
    int resultadoArv1 = maior_seq(1, arv_canhota, 1);

    // Encontrar a maior sequência descendente da árvore destra (começando da raiz, que também é o nó 1)
    int resultadoArv2 = maior_seq(1, arv_destra, 1);
    
    // Calcular interseção e resultado final
    int interseccao = min(resultadoArv1, resultadoArv2);
    int resultado = n_arv1 + n_arv2 - interseccao;
    
    // Exibir o resultado da menor quantidade de nós
    cout << resultado << endl;

    return 0;
}
*/
