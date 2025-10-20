#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long int n, p;

    cin >> n >> p;

    cout << (int) (log(n) / log(p)) << "\n";

    return 0;
}