#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cont = 0, i;
    char letra;
    bool indo = false, primeiro = false;

    cin >> n;
    
    for (i = 0; i < n; i++) {
        cin >> letra;

        if (letra != 'a') indo = false;
        
        else if (indo) {
            cont++;

            if (primeiro) {
                primeiro = false;
                cont++;
            }
        }

        else {
            indo = true;
            primeiro = true;
        }
    }

    cout << cont << "\n";

    return 0;
}