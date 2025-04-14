#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, i;
    bool leu = true;

    for (i = 0; i < 8; i++) {
        cin >> n;

        if (n == 9) {
            leu = false;
        }
    }

    if (leu) {
        cout << "S\n";
    } else {
        cout << "F\n";
    }

    return 0;
}