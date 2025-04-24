#include <iostream>
#include <string>

using namespace std;

void criar_arv_pos(string& arv_pre, string& arv_in, string& arv_pos) {
    if (arv_pre.empty()) return;

    string aux_pre1, aux_in1, aux_pre2, aux_in2;
    char raiz = arv_pre[0];
    int raiz_index = arv_in.find(raiz);

    if (arv_pre.size() != 1) {
        aux_pre1 = arv_pre.substr(1, raiz_index);
        aux_in1 = arv_in.substr(0, raiz_index);

        aux_pre2 = arv_pre.substr(raiz_index+1);
        aux_in2 = arv_in.substr(raiz_index+1);

        criar_arv_pos(aux_pre1, aux_in1, arv_pos); // E
        criar_arv_pos(aux_pre2, aux_in2, arv_pos); // D
    }

    arv_pos += raiz; // R
}


int main() {
    string arv_pre, arv_in, arv_pos;

    while (cin >> arv_pre >> arv_in) {
        arv_pos = ""; // ERD

        criar_arv_pos(arv_pre, arv_in, arv_pos);

        for (const char no : arv_pos) cout << no;
        cout << endl;
    }

    return 0;
}