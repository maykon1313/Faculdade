#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const string vogais = "aeiou";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string entrada, aux1, aux2;
    cin >> entrada;

    for (char letra : entrada) {
        if (vogais.find(letra) != string::npos) {
            aux1 += letra;
        }
    }

    aux2 = aux1;
    reverse(aux1.begin(), aux1.end());

    if (aux1 == aux2) cout << "S\n";
    else cout << "N\n";

    return 0;
}