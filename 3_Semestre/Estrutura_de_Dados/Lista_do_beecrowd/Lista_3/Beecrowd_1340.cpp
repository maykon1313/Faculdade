#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, comando, x, aux, contador;

    while (cin >> n) {
        stack<int> pilha;
        queue<int> fila;
        priority_queue<int> fila_prioridade;

        bool bool_pilha = true;
        bool bool_fila = true;
        bool bool_fila_prioridade = true;

        for (int i = 0; i < n; ++i) {
            cin >> comando >> x;

            if (comando == 1) {
                if (bool_pilha) {
                    pilha.push(x);
                }
                if (bool_fila) {
                    fila.push(x);
                }
                if (bool_fila_prioridade) {
                    fila_prioridade.push(x);
                }
            } 
            
            else {
                aux = x;

                if (bool_pilha) {
                    if (pilha.empty() || pilha.top() != aux) {
                        bool_pilha = false;
                    } else {
                        pilha.pop();
                    }
                }

                if (bool_fila) {
                    if (fila.empty() || fila.front() != aux) {
                        bool_fila = false;
                    } else {
                        fila.pop();
                    }
                }

                if (bool_fila_prioridade) {
                    if (fila_prioridade.empty() || fila_prioridade.top() != aux) {
                        bool_fila_prioridade = false;
                    } else {
                        fila_prioridade.pop();
                    }
                }
            }
        }

        contador = 0;
        if (bool_pilha) contador++;
        if (bool_fila) contador++;
        if (bool_fila_prioridade) contador++;

        if (contador == 0) {
            cout << "impossible\n";
        } 
        
        else if (contador > 1) {
            cout << "not sure\n";
        } 
        
        else {
            if (bool_pilha) {
                cout << "stack\n";
            } 
            
            else if (bool_fila) {
                cout << "queue\n";
            } 
            
            else {
                cout << "priority queue\n";
            }
        }
    }

    return 0;
}