#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long int i, t, x;
    
    cin >> t;
    for (i = 0; i < t; i++) {
        cin >> x;

        if (x > 14 && x%14 >= 1 && x%14 <= 6) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;    
}

// 1:
// 15 a 20

// 2:
// 14 + 15 a 20

// 3:
// 14 + 14 + 15 a 20

// 15%14 = 1
// 20%14 = 6