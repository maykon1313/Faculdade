#include <iostream>

using namespace std;
typedef long long ll;

ll maxEven(ll a, ll b) {
    if(a%2 != 0 && b%2 != 0) {
        return max(a+b, a*b +1);
    }

    else if(a%2 == 0 && b%2 != 0) {
        return -1;
    }

    else if(a%2 == 0 && b%2 == 0) {
        return max(a + b, a*b/2 + 2);
    }

    else {
        if (b%4 != 0) return -1;
        else return max(2*a + b/2, a*b/2 + 2);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int teste;
    ll a, b;

    cin >> teste;

    while(teste--) {
        cin >> a >> b;
        cout << maxEven(a, b) << '\n';
    }

    return 0;
}

/* 
par + par = par
ímpar + ímpar = ímpar

S = (ak) + (b/k)

1. I I
k ímpar
*/