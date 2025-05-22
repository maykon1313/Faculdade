#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, i, j, aux, topo;

    while (cin >> n) {
        if (n == 0) break;

        vector<int> pilha;

        for (i = n; i > 0; i--) pilha.push_back(i);

        cout << "Discarded cards:";
        while (pilha.size() > 1) {
            if (pilha.size() != 2) cout << ' ' << pilha[pilha.size()-1] << ',';
            else cout << ' ' << pilha[pilha.size()-1];
            pilha.pop_back();

            topo = pilha[pilha.size()-1];
            for(j = pilha.size()-1; j > 0; j--) {
                pilha[j] = pilha[j-1];
            }

            pilha[0] = topo;
        }       
        
        cout << '\n';
        cout << "Remaining card: " << pilha[0] << '\n';
    }

    return 0;
}
