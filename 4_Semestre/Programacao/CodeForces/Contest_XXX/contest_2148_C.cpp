#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, m, a, b, posi, temp, cont;

    cin >> t;
    while (t--) {
        cin >> n >> m;

        posi = 0;
        temp = 0;
        cont = 0;

        for (int i = 0; i < n; i++) {
            cin >> a >> b;

            if (a == temp+1 && posi == b) {continue;}
            else {
                while (a--) {
                    temp += 1;

                    if (a == temp+1 && posi == b) {continue;}
                    else {
                        cont += 1;
                        if (posi == 0) {posi = 1;}
                        else {posi = 0;}
                    }
                }
            }
        }
    
        cout << cont << '\n';
    }

    return 0;
}