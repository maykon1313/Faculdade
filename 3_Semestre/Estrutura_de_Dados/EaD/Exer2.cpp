#include <iostream>

using namespace std;

const int N = 23;

void inserir(int num, int v[]) {
    int index = num%N;
    int comeco = index;

    while (v[index] != 0) {
        index = (index + 1) % N;
        if (index == comeco) {
            cout << "Vetor cheio." << endl;
            return;
        }
    }

    v[index] = num;
}

int buscar(int num, int v[]) {
    int index = num%N;
    int comeco = index;

    while (v[index] != 0) {
        if (v[index] == num) {
            return index;
        } else {
            index = (index + 1)%N;

            if (index == comeco) break;
        }
    }

    return -1;
}

void remover(int num, int v[]) {
    int index = buscar(num, v);
    int comeco = index;

    while (v[index] != 0) {
        if (v[index] == num) {
            v[index] = -1;
            return;
        }

        index = (index + 1)%N;
        if (index == comeco) break;
    }
}

void printar(int v[]) {
    for (int i = 0; i < N; i++) {
        if (v[i]) {
            cout << "i(" << i << ") = " << v[i] << endl;
        }
    }
}

int main() {
    int i, index;
    int v[23] = {0};
    int entrada[] = {19, 42, 65, 88, 111, 134, 157, 180, 203};
    int busca1[] = {65, 134, 200};
    int busca2[] = {134, 157};
    int remove[] = {134};

    for (int num : entrada) {
        inserir(num, v);
    }

    printar(v);

    for (int num : busca1) {
        index = buscar(num, v);
        if (index == -1) {
            cout << "O número " << num << " não está no vetor." << endl;
        } 
        
        else {
            cout << "O número " << num << " está no index: " << index << endl;
        }
    }

    for (int num : remove) {
        remover(num, v);
    }
    
    for (int num : busca2) {
        index = buscar(num, v);
        if (index == -1) {
            cout << "O número " << num << " não está no vetor." << endl;
        } 
        
        else {
            cout << "O número " << num << " está no index: " << index << endl;
        }
    }

    printar(v);
    return 0;
}

//i(0) = 111
//i(1) = 134
//i(2) = 157
//i(3) = 180
//i(4) = 203
//i(19) = 19
//i(20) = 42
//i(21) = 65
//i(22) = 88

//O número 65 está no index: 21
//O número 134 está no index: 1
//O número 200 não está no vetor.

//O número 134 não está no vetor.
//O número 157 está no index: 2

//i(0) = 111
//i(1) = -1
//i(2) = 157
//i(3) = 180
//i(4) = 203
//i(19) = 19
//i(20) = 42
//i(21) = 65
//i(22) = 88