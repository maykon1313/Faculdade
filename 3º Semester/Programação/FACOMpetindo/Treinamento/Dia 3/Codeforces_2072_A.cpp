#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, k, p, i, aux;

    cin >> t;

    for (i = 0; i < t; i++) {
        cin >> n >> k >> p;

        if (n*p < abs(k)) {
            cout << -1 << "\n";
        } 
        
        else {
            aux = abs(k)/p;

            if (k%p != 0) {
                aux += 1;
            }

            cout << aux << "\n";
        }
    }

    return 0;
}