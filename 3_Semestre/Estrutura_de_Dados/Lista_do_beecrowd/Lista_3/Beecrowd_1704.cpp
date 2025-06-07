#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Tarefa {
    int v;
    int t;
};

bool compararTarefas(const Tarefa& a, const Tarefa& b) {
    return a.v > b.v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    while (cin >> N >> H) {
        vector<Tarefa> tarefas(N);
        long long lucro_total = 0;

        for (int i = 0; i < N; ++i) {
            cin >> tarefas[i].v >> tarefas[i].t;
            lucro_total += tarefas[i].v;
        }

        sort(tarefas.begin(), tarefas.end(), compararTarefas);
        vector<bool> agenda(H + 1, false);

        long long lucro_maximizado = 0;

        for (const auto& tarefa : tarefas) {
            for (int dia = tarefa.t; dia >= 1; --dia) {
                if (!agenda[dia]) {
                    agenda[dia] = true;
                    lucro_maximizado += tarefa.v;
                    break;
                }
            }
        }

        long long dinheiro_perdido = lucro_total - lucro_maximizado;
        cout << dinheiro_perdido << '\n';
    }

    return 0;
}
