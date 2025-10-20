#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, m, x, y;

    cin >> t;
    while (t--) {
        cin >> n >> m >> x >> y;

        vector<int> a(n);
        vector<int> b(m);

        for (int i = 0; i < n; i++) {cin >> a[i];}
        for (int i = 0; i < m; i++) {cin >> b[i];}
    
        cout << n+m << '\n';
    }

    return 0;
}