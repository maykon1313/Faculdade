#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    double a, b, c;

    cin >> a >> b >> c;

    cout << fixed << setprecision(1);
    if (a >= b+c || b >= a+c || c >= a+b) {
        cout << "Area = " << (a+b)*c/2 << "\n";        
    } else {
        cout << "Perimetro = " << a + b + c << "\n";
    }

    return 0;
}