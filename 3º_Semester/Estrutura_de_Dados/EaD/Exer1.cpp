#include <iostream>

using namespace std;

const int N = 10001;

void inserir(int num, int v[]) {
    if (num >= 0 && num < N) {
        v[num] = 1;
    } else {
        cout << "Valor fora do intervalo permitido." << endl;
    }
}

int buscar(int num, int v[]) {
    if (num >= 0 && num < N && v[num] == 1) {
        return 1;
    } else {
        return -1;
    }
}

void remover(int num, int v[]) {
    if (num >= 0 && num < N) {
        v[num] = 0;
    }
}

void printar(int v[]) {
    for (int i = 0; i < N; i++) {
        if (v[i] == 1) {
            cout << "Presente: " << i << endl;
        }
    }
}

int main() {
    int v[N] = {0};
    int entrada[] = {123, 457, 789, 9999, 42};
    int busca1[] = {123, 42, 555};
    int busca2[] = {42};
    int remove[] = {42};

    for (int num : entrada) {
        inserir(num, v);
    }

    printar(v);

    for (int num : busca1) {
        if (buscar(num, v) == -1) {
            cout << "O número " << num << " não está no vetor." << endl;
        } else {
            cout << "O número " << num << " está presente." << endl;
        }
    }

    for (int num : remove) {
        remover(num, v);
    }
    
    for (int num : busca2) {
        if (buscar(num, v) == -1) {
            cout << "O número " << num << " não está no vetor." << endl;
        } else {
            cout << "O número " << num << " está presente." << endl;
        }
    }

    printar(v);
    return 0;
}

//Presente: 42
//Presente: 123
//Presente: 457
//Presente: 789
//Presente: 9999

//O número 123 está presente.
//O número 42 está presente.
//O número 555 não está no vetor.

//O número 42 não está no vetor.

//Presente: 123
//Presente: 457
//Presente: 789
//Presente: 9999