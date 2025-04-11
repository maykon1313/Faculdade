#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a = 0, b = 1, aux;

    cin >> n;

    if (n == 1) {
        cout << a << "\n";
    } else if (n == 2) {
        cout << a << " " << b << "\n";
    } else {
        cout << a << " " << b; 

        n -= 2;
        while (n) {
            aux = b;
            b = a + b;
            a = aux;
            
            cout << " " << b;

            n--;
        }
        cout << "\n";
    }

    return 0;
}