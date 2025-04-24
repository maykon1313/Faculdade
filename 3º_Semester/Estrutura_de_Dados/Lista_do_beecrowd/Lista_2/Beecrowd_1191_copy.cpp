#include <iostream>
#include <string>

using namespace std;

string criar_arv_pos(string& arv_pre, string& arv_in, string& arv_pos) {
    if (arv_pre.empty()) return "";

    string aux_arv_esq, aux_arv_dir, aux_arv_pos;
    char raiz = arv_pre[0], aux;
    int i = 0, j = 0;

    // DBACEGF      RED
    // ABCDEFG      ERD

    // ACBFGED      EDR

    aux = arv_in[0];
    while (aux != raiz) {
        aux_arv_esq += aux;
    }



}

int main() {
    string arv_pre, arv_in, arv_pos;

    while (cin >> arv_pre >> arv_in) {
        arv_pos = criar_arv_pos(arv_pre, arv_in, arv_pos);

        for (const char no : arv_pos) cout << no;

        cout << endl;
    }

    return 0;
}