#include <iostream>
#include <vector>

using namespace std;

int ta_na_media(vector<int> v, int n) {
    int i;
    double media = 0;

    for (i = 0; i < n; i++) {
        media += v[i];
    }

    media = media/n;

    if (media < 4.5) return 1;
    else return 0;
}

vector<int> substitui_menor(vector<int> v, int n) {
    int i, num, menor = 5, menor_index = 0;

    for (i = 0; i < n; i++) {
        num = v[i];

        if (num < menor) {
            menor = num;
            menor_index = i;
        }
    }

    v[menor_index] = 5;

    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, contador = 0, i;
    
    cin >> n;

    vector<int> v(n);

    for (i = 0; i < n; i++) {
        cin >> v[i];
    }

    while (ta_na_media(v, n)) {
        v = substitui_menor(v, n);
        contador++;
    }

    cout << contador << "\n";

    return 0;
}