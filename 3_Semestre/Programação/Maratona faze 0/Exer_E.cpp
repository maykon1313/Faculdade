#include <iostream>

using namespace std;

int gcd(long long int X,long long int Y) {
    while (true) {
        if (X == Y) return X;
        else if (X > Y) X = X-Y;
        else Y = Y-X;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long int Y, K, x = 2, aux = 1, mdc = 1;

    cin >> Y >> K;

    for (long long int i = 2; i <= 9; i++) {
        if (Y%i == 0) mdc = max(mdc, i);
    }
    
    for (long long int i = 1; i < K; i++) {
        if (x >= Y) {
            cout << x << ' ' << Y << " gcd = " << Y <<'\n';
            x += Y;
        }

        else {
            if (aux < mdc) aux = gcd(x,Y);
            else aux = mdc;

            cout << x << ' ' << Y << " gcd = " << aux <<'\n';
            x += aux;
        }
    }

    cout << x << '\n';

    return 0;
}

/*
 1 123 1
 2 123 1
 3 123 3
 6 123 3
 9 123 3
12 123 3
15 123 
*/