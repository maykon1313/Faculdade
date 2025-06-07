#include <iostream>
using namespace std;

int para_minutos(int h, int m) {
    return h * 60 + m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, i, h, m, c, chegada, base, minutos, atendimento, espera, tempo_livre, recusados;

    while (cin >> n) {
        tempo_livre = 7 * 60;
        recusados = 0;

        for (i = 0; i < n; ++i) {
            cin >> h >> m >> c;
            chegada = para_minutos(h, m);
            base = max(chegada, tempo_livre);
            minutos = base % 60;

            if (minutos == 0) atendimento = base;
            else if (minutos <= 30) atendimento = base - minutos + 30;
            else atendimento = base - minutos + 60;

            espera = atendimento - chegada;
            if (espera > c) recusados++;

            tempo_livre = atendimento + 30;
        }

        cout << recusados << '\n';
    }

    return 0;
}
