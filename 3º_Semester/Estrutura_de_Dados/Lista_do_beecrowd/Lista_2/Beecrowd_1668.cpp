#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;

ull dfs(int u, const vector<pair<int,int>>& filhos, vector<long long>& f) {
    if (u < 0) return 0;
    ull sub_esq, sub_dir;

    sub_esq = dfs(filhos[u].first,  filhos, f);
    sub_dir = dfs(filhos[u].second, filhos, f);
    f[u] = sub_esq + sub_dir + 1;
    return sub_esq + sub_dir + f[u]; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, d, raiz;
    while (true) {
        cin >> n;
        if (n == 0) break;

        vector<pair<int,int>> filhos(n+1);
        vector<bool> e_filho(n+1, false);
        vector<long long> f(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            cin >> e >> d;

            filhos[i] = {e, d};

            if (e != -1) e_filho[e] = true;
            if (d != -1) e_filho[d] = true;
        }

        raiz = 1;
        while (e_filho[raiz]) raiz++;

        dfs(raiz, filhos, f);

        for (int i = 1; i <= n; i++) {
            cout << f[i] << (i < n ? ' ' : '\n');
        }
    }

    return 0;
}
