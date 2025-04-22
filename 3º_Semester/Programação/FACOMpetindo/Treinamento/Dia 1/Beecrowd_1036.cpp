#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double a, b, c, delta, x1, x2;
    
    cin >> a >> b >> c;

    if (a == 0) {
        cout << "Impossivel calcular" << endl;
        return 0;
    } else {

        delta = b*b - 4*a*c;

        if (delta < 0) {
            cout << "Impossivel calcular" << endl;
            return 0;
        }
        else {
            delta = sqrt(delta);

            x1 = (-b + delta)/(2*a);
            x2 = (-b - delta)/(2*a);
            
            cout << "R1 = " << fixed << setprecision(5) << x1 << "\n";
            cout << "R2 = " << fixed << setprecision(5) << x2 << "\n";

            return 0;
        }
    }
}