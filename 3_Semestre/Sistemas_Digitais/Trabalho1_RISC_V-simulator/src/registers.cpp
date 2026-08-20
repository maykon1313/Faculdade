#include "registers.hpp"
#include <iostream>

// Implementação do construtor
Registers::Registers() {
    for (auto& reg : regs) {
        reg = 0;
    }
}

// Implementação da função para ler um registro
uint32_t Registers::ler_no_registro(int index) const {
    erro_no_registro(index);
    return regs[index];
}

// Implementação da função para escrever em um registro
void Registers::escrever_no_registro(int index, uint32_t value) {
    erro_no_registro(index);
    regs[index] = value;
}

// Função auxiliar para verificar erro de índice
void Registers::erro_no_registro(int index) const {
    if (index < 0 || index >= 32) {
        cerr << "Índice de registro fora do intervalo permitido (0 a 31)" << endl;
        exit(EXIT_FAILURE);
    }
}
