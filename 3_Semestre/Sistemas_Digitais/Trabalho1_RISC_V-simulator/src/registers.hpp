#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include <cstdint>

using namespace std;

class Registers {
public:
    Registers();
    
    // 32 registers (x0 to x31)
    array<uint32_t, 32> regs;
    
    uint32_t ler_no_registro (int index) const;
    void escrever_no_registro (int index, uint32_t value);

private:
    void erro_no_registro(int index) const;
};

#endif // REGISTERS_HPP