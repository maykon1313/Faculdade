#include <iostream>
#include <cmath>

using namespace std;

const long long int MB = 1000000 * 8; // bytes para bits

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long int M;
    cin >> M;

    cout << ceil(log2(M * MB)) << '\n';
    return 0;
}

