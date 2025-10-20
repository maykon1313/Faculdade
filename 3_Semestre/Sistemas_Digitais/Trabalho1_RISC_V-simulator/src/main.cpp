#include <iostream>
#include "simulator.hpp"

using namespace std;

int main() {
    string arquivo_de_entrada;
    
    cout << "Digite o nome do arquivo de entrada (com .txt): ";
    cin >> arquivo_de_entrada;
    cout << endl;

    Simulator simulator = Simulator(arquivo_de_entrada);

    simulator.executar();

    simulator.estado(arquivo_de_entrada);

    return 0;
}