#include <iostream>
#include <vector>
#include <algorithm> // Para std::max
using namespace std;

struct no {
    int num;
    int left;
    int mid;
    int right;
};

int maiorSequenciaDescendente(int no, const vector<no>& arvore) {
    if (no == 0) return 0;  // Nó 0 significa que não existe filho

    int seqEsq = maiorSequenciaDescendente(arvore[no].left, arvore);  // Filhos esquerdo
    int seqMid = maiorSequenciaDescendente(arvore[no].mid, arvore);   // Filhos central
    int seqDir = maiorSequenciaDescendente(arvore[no].right, arvore); // Filhos direito

    // A maior sequência descendente a partir deste nó é 1 + a maior sequência entre seus filhos
    return 1 + max(max(seqEsq, seqMid), seqDir);
}

int main() {
    int n_arv1 = 0, n_arv2 = 0;

    // Árvore 1
    cin >> n_arv1;    
    vector<no> arv_canhota(n_arv1 + 1);

    for (int i = 1; i <= n_arv1; i++) {
        cin >> arv_canhota[i].num >> arv_canhota[i].left >> arv_canhota[i].mid;
    }

    // Árvore 2
    cin >> n_arv2;    
    vector<no> arv_destra(n_arv2 + 1);

    for (int i = 1; i <= n_arv2; i++) {
        cin >> arv_destra[i].num >> arv_destra[i].mid >> arv_destra[i].right;
    }

    // Encontrar a maior sequência descendente da árvore canhota (começando da raiz, que é o nó 1)
    int resultadoArv1 = maiorSequenciaDescendente(1, arv_canhota);

    // Encontrar a maior sequência descendente da árvore destra (começando da raiz, que também é o nó 1)
    int resultadoArv2 = maiorSequenciaDescendente(1, arv_destra);
    
    // Exibir o resultado da maior sequência descendente entre as duas árvores
    cout << max(resultadoArv1, resultadoArv2) << endl;

    return 0;
}

