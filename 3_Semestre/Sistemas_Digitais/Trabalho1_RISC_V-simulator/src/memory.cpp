#include <cstdint>
#include "memory.hpp"
#include <iostream>
#include <cstdlib>

uint8_t Memory::ler_na_memoria(size_t address) const {
    auto it = memory.find(address);
    if (it == memory.end()) {
        return 0; // Endereço não inicializado retorna 0
    }
    return it->second;
}

void Memory::escrever_na_memoria(size_t address, uint8_t value) {
    memory[address] = value; 
}