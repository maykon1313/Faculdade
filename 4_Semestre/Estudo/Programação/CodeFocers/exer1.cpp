#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, k;
    
    cin >> n;

    while(n--) {
        cin >> k >> x;
        
        x = x * (1 << k);

        cout << x << '\n';
    }

    return 0;
}