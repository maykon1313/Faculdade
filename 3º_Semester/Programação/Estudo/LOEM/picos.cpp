#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // Para usar std::fixed e std::setprecision

using namespace std;

vector<int> descobrir_picos(vector<double>& alturas) {
    int i = 0, n = alturas.size();
    vector<int> picos;

    while (i < n) {
        if (i == 0) {
            if (alturas[i] >= alturas[i+1]) picos.push_back(i);
        }
        else if (i == n-1) { 
            if (alturas[i-1] <= alturas[i]) picos.push_back(i);
        }
        else {
            if (alturas[i-1] <= alturas[i] && alturas[i] >= alturas[i+1]) picos.push_back(i);
        }

        i++;
    }

    return picos;
}

void substituirVirgulaPorPonto(string &s) {
    for (char &c : s) {
        if (c == ',') c = '.';
    }
}

// Função auxiliar para substituir pontos por vírgulas em uma string
string substituirPontoPorVirgula(double valor) {
    stringstream ss;
    ss << valor;
    string resultado = ss.str();
    for (char &c : resultado) {
        if (c == '.') c = ',';
    }
    return resultado;
}

int main() {
    string t, h;
    vector<double> tempos, alturas;
    vector<int> picolinos;

    ofstream picos("picos.txt");

    while (cin >> t >> h) {
        substituirVirgulaPorPonto(t);
        substituirVirgulaPorPonto(h);

        stringstream ss;
        double tem, alt;

        ss.str(t);
        ss >> tem;
        ss.clear();

        ss.str(h);
        ss >> alt;

        tempos.push_back(tem);
        alturas.push_back(alt);
    }

    picolinos = descobrir_picos(alturas);

    for (int i : picolinos) {
        picos << substituirPontoPorVirgula(tempos[i]) << ". " << substituirPontoPorVirgula(alturas[i]) << endl;
    }

    picos.close();
    return 0;
}

