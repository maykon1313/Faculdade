#include <iostream>
#include <vector>

using namespace std;

int menor_caminho(vector<vector<int>>& matriz, int C, int K) {
    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C, K;
    int U, V, P;
    int i, j;
    int pedagio = 0;

    while (cin >> N >> M >> C >> K) {
        if (N == 0) break;

        vector<vector<int>> matriz(N, vector<int>(N, -1));


        for (i = 0; i < M; i++) {
            cin >> U >> V >> P;
            matriz[U][V] = P;
            matriz[V][U] = P;
        }

        pedagio = menor_caminho(matriz, C, K);

        cout << pedagio << '\n';
    }

    return 0;
}

//vector<int> rota;
//for (i = 0; i < C; i++) rota.push_back(i);




6 7 2 5

5 2 1
2 1 10
1 0 1
3 0 2
3 4 2
3 5 3
5 4 2


5 2 1
5 3 3
5 4 2

2 1 10

3 0 2
3 4 2

4 3 2

0 1 1


5 3 3
3 0 2
0 1 1