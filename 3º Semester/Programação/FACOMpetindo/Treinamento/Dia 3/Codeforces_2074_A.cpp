#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, l, r, d, u, i;

    cin >> t;

    for (i = 0; i < t; i++) {
        cin >> l >> r >> d >> u;

        if (l != r || r != d || d != u) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }

    return 0;
}