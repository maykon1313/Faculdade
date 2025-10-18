#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int teste;
    cin >> teste;

    while(teste--) {
        int n;
        cin >> n;
        
        vector<int> array(n);
        for(int i = 0; i < n; ++i) {
            cin >> array[i];
        }

        vector<int> aux1 = array;
        sort(aux1.begin(), aux1.end());

        vector<int> aux2 = aux1;
        reverse(aux2.begin(), aux2.end());

        unordered_map<int, vector<int>> value_to_indices;
        for (int i = 0; i < aux1.size(); ++i) {
            value_to_indices[aux1[i]].push_back(i);
        }

        unordered_map<int, int> usage_count;
        
        vector<int> result;
        for (int valor_original : array) {
            int count = usage_count[valor_original];
            int indice_no_ordenado = value_to_indices[valor_original][count];

            result.push_back(aux2[indice_no_ordenado]);

            usage_count[valor_original]++;
        }
        
        for (int i = 0; i < result.size(); ++i) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}