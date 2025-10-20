#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    char letra;
    int p = 0; 

    while (cin.get(letra)) {
        if (letra == 'p') {
            p++;
        }

        else if (letra == ' ') {
            cout << letra;
        }
        
        else {
            cout << letra;
            p--; 
        }
        
        if (p == 2) {
            cout << letra;
            p -= 2;
        }  
    }

    return 0;
}