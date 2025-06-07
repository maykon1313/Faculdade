#include <iostream>
#include <string>

using namespace std;

string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, soma, i, j;
    string entrada;
    cin >> t;
    while (t--) {
        cin >> n;
        soma = 0;
        for (i = 0; i < n; i++) {
            cin >> entrada;
            for (j = 0; j < entrada.size(); j++) {
                soma += alfabeto.find(entrada[j]) + i + j;
            }
        }
        cout << soma << '\n';
    }
    return 0;
}