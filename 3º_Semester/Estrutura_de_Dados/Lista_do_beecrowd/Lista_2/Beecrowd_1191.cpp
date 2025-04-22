#include <iostream>
#include <string>
#include <vector>

using namespace std;

void posfixo_recursivo(vector<char> arv_pre, vector<char> arv_in) {
    vector<char> aux1, aux2;
    char raiz = arv_pre[0];
    int i = 0, j = 1;
    
    if (arv_pre.empty()) return;
    
    while (arv_in[i] != raiz) {
        aux2.push_back(arv_in[i]);
        i++;
    }
    
    while (j != i) {
        aux1.push_back(arv_pre[j]);
        j++;
    }
    
    
}

int main() {
    string arv1, arv2;
    vector<char> arv_pre, arv_in;
    
    while (cin >> arv1 >> arv2) {
        arv_pre(arv1.begin(), arv1.end());
        arv_in(arv2.begin(), arv2.end());
        
        posfixo_recursivo(arv_pre, arv_in);
        
        cout << endl;
    }
    
    return 0;
}