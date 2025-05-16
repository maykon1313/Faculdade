#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, maior, menor;

    cin >> a >> b >> c;

    menor = min({a, b, c});
    maior = max({a, b, c});

    cout << a+b+c - (menor+maior) << "\n";

    return 0;
}