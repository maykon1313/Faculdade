#include <iostream>
#include <vector>

using namespace std;

int tamanho_arvore1, tamanho_arvore2;
vector<vector<int>> adjacencias_arvore1, adjacencias_arvore2;

bool busca_caminho(int no_atual, vector<vector<int>>& grafo, vector<int>& correspondencias, vector<bool>& visitados) {
    for (int vizinho : grafo[no_atual]) {
        if (visitados[vizinho]) continue;
        visitados[vizinho] = true;
        if (correspondencias[vizinho] < 0 || busca_caminho(correspondencias[vizinho], grafo, correspondencias, visitados)) {
            correspondencias[vizinho] = no_atual;
            return true;
        }
    }
    return false;
}

bool subarvores_isomorfas(int no1, int pai1, int no2, int pai2) {
    vector<int> filhos_arvore1, filhos_arvore2;

    for (int vizinho : adjacencias_arvore1[no1]) if (vizinho != pai1) filhos_arvore1.push_back(vizinho);
    for (int vizinho : adjacencias_arvore2[no2]) if (vizinho != pai2) filhos_arvore2.push_back(vizinho);

    int tamanho1 = filhos_arvore1.size(), tamanho2 = filhos_arvore2.size();

    if (tamanho1 < tamanho2) return false;

    vector<vector<int>> grafo(tamanho2);

    for (int i = 0; i < tamanho2; i++) {
        for (int j = 0; j < tamanho1; j++) {
            if (subarvores_isomorfas(filhos_arvore1[j], no1, filhos_arvore2[i], no2)) grafo[i].push_back(j);
        }
        if (grafo[i].empty()) return false;
    }
    
    vector<int> correspondencias(tamanho1, -1);
    int contador = 0;
    for (int i = 0; i < tamanho2; i++) {
        vector<bool> visitados(tamanho1, false);
        if (busca_caminho(i, grafo, correspondencias, visitados)) contador++;
        else return false;
    }
    return (contador == tamanho2);
}

void ler_arvore(int& tamanho, vector<vector<int>>& adjacencias) {
    cin >> tamanho;
    adjacencias.assign(tamanho+1, {});
    for (int i = 0; i < tamanho-1; i++) {
        int no1, no2;
        cin >> no1 >> no2;
        adjacencias[no1].push_back(no2);
        adjacencias[no2].push_back(no1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ler_arvore(tamanho_arvore1, adjacencias_arvore1);
    ler_arvore(tamanho_arvore2, adjacencias_arvore2);

    if (tamanho_arvore1 < tamanho_arvore2) {
        cout << 'N' << '\n';
        return 0;
    }

    for (int raiz1 = 1; raiz1 <= tamanho_arvore1; raiz1++) {
        if (subarvores_isomorfas(raiz1, 0, 1, 0)) {
            cout << 'Y' << '\n';
            return 0;
        }
    }

    cout << 'N' << '\n';
    return 0;
}