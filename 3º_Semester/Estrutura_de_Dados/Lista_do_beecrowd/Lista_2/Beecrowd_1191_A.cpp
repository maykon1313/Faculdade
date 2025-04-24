#include <iostream>
#include <string>

using namespace std;

void criar_arv_pos(string& arv_pre, string& arv_in, string& arv_pos, int ini_pre, int fim_pre, int ini_in, int fim_in) {
    if (ini_pre > fim_pre || ini_in > fim_in) return;

    char raiz = arv_pre[ini_pre];
    int raiz_index = arv_in.find(raiz, ini_in);
    int tamanho_esq = raiz_index - ini_in;

    criar_arv_pos(arv_pre, arv_in, arv_pos, ini_pre+1, ini_pre+tamanho_esq, ini_in, raiz_index-1);
    criar_arv_pos(arv_pre, arv_in, arv_pos, ini_pre+tamanho_esq+1, fim_pre, raiz_index+1, fim_in);

    arv_pos += raiz;
}

int main() {
    string arv_pre, arv_in, arv_pos;

    while (cin >> arv_pre >> arv_in) {
        arv_pos = "";

        criar_arv_pos(arv_pre, arv_in, arv_pos, 0, arv_pre.size()-1, 0, arv_in.size()-1);

        for (const char no : arv_pos) cout << no;

        cout << endl;
    }

    return 0;
}