#include <math.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int expRapida(int base, int exp, int mod) {
    int resu = 1;
    while (exp > 0) {
        if (exp & 1)
            resu = (resu * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return resu;
}

int main() {
    int casos;
    cin >> casos;

    while (casos--) {
        int a, b;
        cin >> a >> b;

        if (a == 0) 
            cout << 0 << endl;
        else if (b == 0) 
            cout << 1 << endl;
        else 
            cout << expRapida(a, b, 10) << endl;
    }
    return 0;
}