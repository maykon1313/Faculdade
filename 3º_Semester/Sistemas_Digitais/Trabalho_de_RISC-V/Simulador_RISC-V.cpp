#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace Constantes {const string WHITESPACE = " \t\n\r";}


string remover_espaco(const string& linha);
vector<string> lerInstrucoes(const string& nome_do_arquivo); 
 
int main() {
    vector<string> instrucoes = lerInstrucoes("entrada2.txt");

    for (const string& intrucao : instrucoes) cout << instrucao << endl;

    return 0;
}

string remover_espaco(const string& linha) {
    size_t comeco = linha.find_first_not_of(Constantes::WHITESPACE);

    // string::npos = -1 = Não encontrado.
    if (comeco == string::npos) return "";

    size_t fim = linha.find_last_not_of(Constantes::WHITESPACE);

    return linha.substr(comeco, fim - comeco + 1);
}

vector<string> lerInstrucoes(const string& nome_do_arquivo) {
    ifstream arquivo(nome_do_arquivo);
    vector<string> instrucoes;
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o aquivo: " << nome_do_arquivo << endl;
        return instrucoes;
    }

    while (getline(arquivo, linha)) {
        size_t comentario = linha.find('#');

        // string::npos = -1 = Não encontrado.
        if (comentario != string::npos) { 
            linha = linha.substr(0, comentario);
        }

        linha = remover_espaco(linha);

        if (!linha.empty()) {
            instrucoes.push_back(linha);
        }
    }

    arquivo.close();
    return instrucoes;
}

