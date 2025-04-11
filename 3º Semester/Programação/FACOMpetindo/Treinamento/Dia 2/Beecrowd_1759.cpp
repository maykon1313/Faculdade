#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cout << " ";
        }

        cout << "Ho";
    }

    cout << "!\n";

    return 0;
}