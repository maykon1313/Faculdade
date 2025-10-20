#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "instruction.hpp"
#include "memory.hpp"
#include "registers.hpp"
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class Simulator {
public:
    Simulator(const string& entrada);
    void executar();
    void estado(const string& entrada);

    Memory memoria;
    Registers registro;

private:
    vector<vector<string>> instrucoes;
    uint32_t PC_counter;
};

#endif // SIMULATOR_HPP