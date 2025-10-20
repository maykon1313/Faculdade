#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "registers.hpp"
#include "memory.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <utility>

using namespace std;

void formato_R(string opcode, string rd,  string rs1, string rs2, Registers& registro);
void formato_U(string opcode, string rd,string imm, Registers& registro, uint32_t PC_counter);
void formato_I(string opcode, string rd,string rs1, string imm, Registers& registro, Memory& memoria);
void formato_S(string opcode, string rs2,string offset_rs1, Registers& registro, Memory& memoria);
char identificarFormato(const string& opcode);
void executarInstrucoes(vector<string> linha, Registers& registro, Memory& memoria, uint32_t PC_counter);

#endif // INSTRUCTION_HPP