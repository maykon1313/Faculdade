#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <map>
#include <cstdint>

using namespace std;

class Memory {
public:
    Memory() = default;
    
    std::map<size_t, uint8_t> memory; // Mapeamento de endereços para valores

    uint8_t ler_na_memoria(size_t address) const;
    void escrever_na_memoria(size_t address, uint8_t value);
};

#endif // MEMORY_HPP