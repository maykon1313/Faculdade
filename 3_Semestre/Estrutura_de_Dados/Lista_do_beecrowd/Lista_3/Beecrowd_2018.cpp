#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct medalha {
    int ouro = 0;
    int prata = 0;
    int bronze = 0;
};

bool comparar(const pair<string, medalha>& a, const pair<string, medalha>& b) {
    if (a.second.ouro != b.second.ouro) return a.second.ouro > b.second.ouro;
    if (a.second.prata != b.second.prata) return a.second.prata > b.second.prata;
    if (a.second.bronze != b.second.bronze) return a.second.bronze > b.second.bronze;
    return a.first < b.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, medalha> quadro;
    string modalidade, ouro, prata, bronze;

    while (getline(cin, modalidade)) {
        getline(cin, ouro);
        getline(cin, prata);
        getline(cin, bronze);

        quadro[ouro].ouro++;
        quadro[prata].prata++;
        quadro[bronze].bronze++;
    }

    vector<pair<string, medalha>> paises(quadro.begin(), quadro.end());
    sort(paises.begin(), paises.end(), comparar);

    cout << "Quadro de Medalhas\n";
    for (const auto& [nome, m] : paises) {
        cout << nome << ' ' << m.ouro << ' ' << m.prata << ' ' << m.bronze << '\n';
    }

    return 0;
}