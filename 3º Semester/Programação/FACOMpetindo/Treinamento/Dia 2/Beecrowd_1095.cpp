#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int i = 1, j = 60;

    while (j >= 0) {
        cout << "I=" << i << " J=" << j << "\n";
        i+=3;
        j-=5;
    }

    return 0;
}