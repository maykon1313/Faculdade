#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int E, D;

    cin >> E >> D;

    if (E > D) {
        cout << E + D << "\n";
    } else {
        cout << 2 * (D - E) << "\n";
    }

    return 0;
}