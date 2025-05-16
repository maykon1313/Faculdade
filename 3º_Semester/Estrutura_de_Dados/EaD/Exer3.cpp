#include <iostream>

using namespace std;

const int N = 23;

void inserir(int num, int v[]) {
    int index = num%N;
    int i = 0;

    while (v[(index + i*i)%N] != 0 && v[(index + i*i)%N] != -1 && i < N) {
        i++;
    }

    if (i == N) {
        cout << "Vetor cheio." << endl;
        return;
    }

    v[(index + i*i)%N] = num;
}

int buscar(int num, int v[]) {
    int index = num%N;
    int i = 0;

    while (v[(index + i*i)%N] != 0 && i < N) {
        if (v[(index + i*i)%N] == num) {
            return (index + i*i)%N;;
        }
        
        i++;
    }

    return -1;
}

void remover(int num, int v[]) {
    int index = buscar(num, v);

    if (index != -1) {
        v[index] = -1;
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

//i(0) = 65
//i(5) = 88
//i(9) = 157
//i(12) = 111
//i(14) = 203
//i(19) = 19
//i(20) = 42
//i(21) = 134
//i(22) = 180

//O número 65 está no index: 0
//O número 134 está no index: 21
//O número 200 não está no vetor.

//O número 134 não está no vetor.
//O número 157 está no index: 9

//i(0) = 65
//i(5) = 88
//i(9) = 157
//i(12) = 111
//i(14) = 203
//i(19) = 19
//i(20) = 42
//i(21) = -1
//i(22) = 180