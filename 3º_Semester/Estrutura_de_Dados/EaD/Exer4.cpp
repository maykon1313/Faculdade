#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Primo próximo de 10.000 para melhor distribuição
const int N = 10007; 

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

void inserir(int num, vector<Node*>& tabela) {
    int index = num%N;
    Node* novo = new Node(num);
    novo->next = tabela[index];
    tabela[index] = novo;
}

vector<int> calcular_distribuicao(const vector<Node*>& tabela) {
    vector<int> distribuicao(N, 0);
    Node* atual;
    
    for (int i = 0; i < N; ++i) {
        atual = tabela[i];
        while (atual) {
            distribuicao[i]++;
            atual = atual->next;
        }
    }

    return distribuicao;
}

void liberar_tabela(vector<Node*>& tabela) {
    Node* atual;
    Node* prox;
    
    for (int i = 0; i < N; ++i) {
        atual = tabela[i];
        while (atual) {
            prox = atual->next;
            delete atual;
            atual = prox;
        }
        tabela[i] = nullptr;
    }
}

int main() {
    vector<Node*> tabela(N, nullptr);
    ifstream fin("dados_teste.txt");

    int num, count = 0;
    while (fin >> num && count < 10000) {
        inserir(num, tabela);
        count++;
    }
    fin.close();

    // Calcula distribuição
    vector<int> distribuicao = calcular_distribuicao(tabela);

    // Salva distribuição em arquivo para plotar no Python
    ofstream fout("distribuicao.txt");
    for (int i = 0; i < N; ++i) {
        fout << distribuicao[i] << "\n";
    }
    fout.close();

    // Calcula média e variância
    double soma = 0, soma2 = 0;
    for (int i = 0; i < N; ++i) {
        soma += distribuicao[i];
        soma2 += distribuicao[i] * distribuicao[i];
    }
    double media = soma / N;
    double variancia = (soma2 / N) - (media * media);
    cout << "Média do tamanho das listas: " << media << endl;
    cout << "Variância do tamanho das listas: " << variancia << endl;

    liberar_tabela(tabela);
    return 0;
}

//Média do tamanho das listas: 0.9993
//Variância do tamanho das listas: 1.00819