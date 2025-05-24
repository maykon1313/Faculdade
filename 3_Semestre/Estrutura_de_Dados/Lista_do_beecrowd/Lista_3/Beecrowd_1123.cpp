#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int dijkstra_corrigido(int N, const vector<vector<int>>& matriz, int C, int K) {
    int destino_final = C - 1;
    int d, u, v, p;
    vector<int> dist(N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[K] = 0;
    pq.push({0, K});

    while (!pq.empty()) {
        d = pq.top().first;
        u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        if (u >= 0 && u < destino_final) {
            v = u + 1;

            if (matriz[u][v] != -1) {
                p = matriz[u][v];
                if (dist[u] != INF && dist[u] + p < dist[v]) {
                    dist[v] = dist[u] + p;
                    pq.push({dist[v], v});
                }
            }
        }
        
        else {
            for (v = 0; v < N; ++v) {
                if (matriz[u][v] != -1) {
                    p = matriz[u][v];
                    if (dist[u] != INF && dist[u] + p < dist[v]) {
                        dist[v] = dist[u] + p;
                        pq.push({dist[v], v});
                    }
                }
            }
        }
    }

    return dist[destino_final];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C, K;
    int U, V, P;

    while (cin >> N >> M >> C >> K) {
        if (!N) break;

        vector<vector<int>> matriz(N, vector<int>(N, -1));

        for (int i = 0; i < M; i++) {
            cin >> U >> V >> P;
            if (U >= 0 && U < N && V >= 0 && V < N) {
                matriz[U][V] = P;
                matriz[V][U] = P;
            }
        }

        cout << dijkstra_corrigido(N, matriz, C, K) << '\n';
    }

    return 0;
}