#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void somar(vector<int> &vec, vector<long long int> &soma) {
    soma[0] = 0;

    for (int i = 0; i < vec.size(); i++) {
        soma[i+1] = soma[i] + vec[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, i, x, y;
    long long int resu;

    cin >> n >> q;

    vector<int> v(n);
    vector<long long int> soma_acumulada(n+1);

    for (i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end(), greater<>());

    somar(v, soma_acumulada);

    for (i = 0; i < q; i++) {
        cin >> x >> y;
        
        resu = soma_acumulada[x] - soma_acumulada[x-y];

        cout << resu << "\n";
    }    

    return 0;
}