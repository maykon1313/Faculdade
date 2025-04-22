#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string linha;

    while (getline(cin, linha)) {
        if (linha == "esquerda") {
            cout << "ingles" << "\n";
        } else if (linha == "direita") {
            cout << "frances" << "\n";
        } else if (linha == "nenhuma") {
            cout << "portugues" << "\n";
        } else {
            cout << "caiu" << "\n";
        }
    }

    return 0;
}