#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, i;
    long long int n, k, cont;
    
    cin >> t;

    for (i = 0; i < t; i++) {
        cont = 0;

        cin >> n >> k;

        if (n%2 != 0) {
            n -= k;
            cont++;
        }

        if (n > (k-1)) {            
            cont += n/(k-1);
            n = n%(k-1);
        }

        if (n > 0) {
            cont += 1;
        }

        cout << cont << "\n";
    }
    
    return 0;
}


// 39   7

// 32   26   20  14   8   2   0