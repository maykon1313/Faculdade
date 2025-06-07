#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

const int INF = 0x3f3f3f3f;

int d_linha[] = {-1, 1, 0, 0};
int d_coluna[] = {0, 0, 1, -1};

struct Estado {
    int empurroes;
    int movimentos;
    int p_linha, p_coluna;
    int c_linha, c_coluna;

    bool operator>(const Estado& other) const {
        if (empurroes != other.empurroes) return empurroes > other.empurroes;
        return movimentos > other.movimentos;
    }
};

string solve(int r, int c) {
    vector<string> grid(r);
    int comeco_linha, comeco_coluna, caixa_linha, caixa_coluna, alvo_linha, alvo_coluna;

    cin.ignore();
    for (int i = 0; i < r; ++i) {
        getline(cin, grid[i]);
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == 'S') {
                comeco_linha = i;
                comeco_coluna = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'B') {
                caixa_linha = i;
                caixa_coluna = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'T') {
                alvo_linha = i;
                alvo_coluna = j;
                grid[i][j] = '.';
            }
        }
    }

    vector<vector<vector<vector<pair<int, int>>>>> dist(r,
        vector<vector<vector<pair<int, int>>>>(c,
            vector<vector<pair<int, int>>>(r,
                vector<pair<int, int>>(c, {INF, INF}))));

    priority_queue<Estado, vector<Estado>, greater<Estado>> pq;

    dist[comeco_linha][comeco_coluna][caixa_linha][caixa_coluna] = {0, 0};
    pq.push({0, 0, comeco_linha, comeco_coluna, caixa_linha, caixa_coluna});

    pair<int, int> solucao = {-1, -1};

    while (!pq.empty()) {
        Estado atual = pq.top();
        pq.pop();

        if (make_pair(atual.empurroes, atual.movimentos) > dist[atual.p_linha][atual.p_coluna][atual.c_linha][atual.c_coluna]) {
            continue;
        }

        if (atual.c_linha == alvo_linha && atual.c_coluna == alvo_coluna) {
            solucao = {atual.empurroes, atual.movimentos};
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int np_l = atual.p_linha + d_linha[i];
            int np_c = atual.p_coluna + d_coluna[i];

            if (np_l >= 0 && np_l < r && np_c >= 0 && np_c < c && grid[np_l][np_c] != '#' && !(np_l == atual.c_linha && np_c == atual.c_coluna)) {
                auto custo = make_pair(atual.empurroes, atual.movimentos + 1);
                if (custo < dist[np_l][np_c][atual.c_linha][atual.c_coluna]) {
                    dist[np_l][np_c][atual.c_linha][atual.c_coluna] = custo;
                    pq.push({custo.first, custo.second, np_l, np_c, atual.c_linha, atual.c_coluna});
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            int nc_l = atual.c_linha + d_linha[i];
            int nc_c = atual.c_coluna + d_coluna[i];
            int rp_l = atual.c_linha - d_linha[i];
            int rp_c = atual.c_coluna - d_coluna[i];

            if (atual.p_linha == rp_l && atual.p_coluna == rp_c && nc_l >= 0 && nc_l < r && nc_c >= 0 && nc_c < c && grid[nc_l][nc_c] != '#') {
                auto custo = make_pair(atual.empurroes + 1, atual.movimentos + 1);
                if (custo < dist[atual.c_linha][atual.c_coluna][nc_l][nc_c]) {
                    dist[atual.c_linha][atual.c_coluna][nc_l][nc_c] = custo;
                    pq.push({custo.first, custo.second, atual.c_linha, atual.c_coluna, nc_l, nc_c});
                }
            }
        }
    }

    string resultado;
    if (solucao.first != -1) {
        resultado = to_string(solucao.second) + " " + to_string(solucao.first);
    } else {
        resultado = "Impossivel";
    }
    return resultado;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, contador = 1;

    while (cin >> r >> c && (r != 0 || c != 0)) {
        if (contador > 1) {
            cout << "\n";
        }
        cout << "Instancia " << contador++ << "\n";
        cout << solve(r, c) << "\n";
    }

    return 0;
}
