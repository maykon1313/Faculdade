#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, l, c, r, posi, cont;

    while (true) {
        cin >> m;
        if (!m) break;

        posi = 2;
        cont = 0;

        while (m--) {
            cin >> l >> c >> r;

            if (l == 1 && posi == 1) {
                if (c == 0) {
                    posi = 2;
                    cont += 1;
                } else {
                    posi = 3;
                    cont += 2;
                }
            }

            else if (c == 1 && posi == 2) {
                if (l == 0) {
                    posi = 1;
                    cont += 1;
                } else {
                    posi = 3;
                    cont += 1;
                }
            }

            else if (r == 1 && posi == 3) {
                if (c == 0) {
                    posi = 2;
                    cont += 1;
                } else {
                    posi = 1;
                    cont += 2;
                }
            }
        }

        cout << cont << '\n';
    }

    return 0;
}