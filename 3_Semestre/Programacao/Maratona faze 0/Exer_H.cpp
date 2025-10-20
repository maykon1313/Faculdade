#include <bits/stdc++.h>

using namespace std;

bool palindromo(long long int num) {
    string bin = bitset<32>(num).to_string();
    bin = bin.substr(bin.find('1'));

    string reverso = bin;
    reverse(reverso.begin(), reverso.end());

    return bin == reverso;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long int N;
    cin >> N;

    for (long long i = N; i >= 0; i--) {
        if (palindromo(i)) {
            cout << i << '\n';
            break;
        }
    }

    return 0;
}