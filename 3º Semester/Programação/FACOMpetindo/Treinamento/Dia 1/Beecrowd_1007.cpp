#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c, d;

    cin >> a >> b >> c >> d;

    cout << "DIFERENCA = " << (a*b - c*d) << endl;

    return 0;
}