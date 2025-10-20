#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string a;
    int i, size, resu = 0, fatorial[5] = {1, 2, 6, 24, 120};
    
    while (true) {
        resu = 0;
        cin >> a;

        if (a == "0") {
            return 0;
        }

        size = a.size();
        for(i = 0; i < size; i++) {
            resu += (a[i] - '0') * (fatorial[size - (i+1)]);
        }

        cout << resu << "\n";
    }

    return 0;
}