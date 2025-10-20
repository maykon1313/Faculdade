#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, x, n;

    cin >> t;
    while (t--) {
        cin >> x >> n;

        if (n%2 == 0) cout << 0 << '\n'; 
        else cout << x << '\n'; 
    }

    return 0;
}