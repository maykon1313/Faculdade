#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, i, j;
    long long total_valor, atual_valor;

    while (cin >> n) {
        vector<long long> frequencias[64];

        for (i = 0; i < n; i++) {
            cin >> x;
            frequencias[x].push_back(-1);
        }

        total_valor = 0;
        atual_valor = 1;

        for (i = 55; i >= 1; i--) {
            for (j = 0; j < frequencias[i].size(); j++) {
                if (frequencias[i][j] == -1) {
                    frequencias[i][j] = atual_valor;
                    total_valor += atual_valor;
                }
            }

            for (j = 0; j < frequencias[i].size(); j += 2) {
                if (j + 1 < frequencias[i].size()) {
                    if (i > 1) {
                        frequencias[i-1].push_back(frequencias[i][j] +frequencias[i][j+1]);
                    }

                    atual_valor = max(atual_valor, frequencias[i][j]);
                    atual_valor = max(atual_valor, frequencias[i][j+1]);
                }
            }
        }

        cout << total_valor << '\n';
    }

    return 0;
}