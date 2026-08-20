#include "instruction.hpp"
#include "simulator.hpp"
#include "registers.hpp"
#include "memory.hpp"
#include <iostream>


using namespace std;

void validar_registrador(const string& reg) {
    if (reg.empty() || reg[0] != 't') {
        cerr << "Registrador inválido: " << reg << endl;
        exit(EXIT_FAILURE);
    }
    try {
        int idx = stoi(reg.substr(1));
        if (idx < 0 || idx >= 32) {
            cerr << "Índice de registrador fora do intervalo permitido (0 a 31): " << reg << endl;
            exit(EXIT_FAILURE);
        }
    } catch (const invalid_argument& e) {
        cerr << "Erro ao converter registrador: " << reg << endl;
        exit(EXIT_FAILURE);
    }
}

void validar_imediato(const string& imm) {
    if (imm.empty()) {
        cerr << "Imediato vazio." << endl;
        exit(EXIT_FAILURE);
    }
    try {
        stoi(imm);
    } catch (const invalid_argument& e) {
        cerr << "Erro ao converter imediato: " << imm << endl;
        exit(EXIT_FAILURE);
    }
}

void formato_R(string opcode, string rd, string rs1, string rs2, Registers& registro) {
    validar_registrador(rd);
    validar_registrador(rs1);
    validar_registrador(rs2);
    int rd_idx = stoi(rd.substr(1));
    int rs1_idx = stoi(rs1.substr(1));
    int rs2_idx = stoi(rs2.substr(1));

    if (opcode == "add") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) + registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "sub") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) - registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "xor") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) ^ registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "or") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) | registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "and") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) & registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "sll") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) << (registro.ler_no_registro(rs2_idx) & 0x1F));
    } 
    
    else if (opcode == "srl") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) >> (registro.ler_no_registro(rs2_idx) & 0x1F));
    } 
    
    else if (opcode == "sra") {
        registro.escrever_no_registro(rd_idx, (int32_t)registro.ler_no_registro(rs1_idx) >> (registro.ler_no_registro(rs2_idx) & 0x1F));
    } 
    
    else if (opcode == "slt") {
        registro.escrever_no_registro(rd_idx, (int32_t)registro.ler_no_registro(rs1_idx) < (int32_t)registro.ler_no_registro(rs2_idx));
    } 
    
    else if (opcode == "sltu") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) < registro.ler_no_registro(rs2_idx));
    } 
    
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_U(string opcode, string rd, string imm, Registers& registro, uint32_t PC_counter) {
    validar_registrador(rd);
    validar_imediato(imm);
    int rd_idx = stoi(rd.substr(1));
    int32_t imm_val = stoi(imm, nullptr, 0); // Hex para Dec

    uint32_t valor = static_cast<uint32_t>(imm_val) << 12;

    if (opcode == "lui") {
        registro.escrever_no_registro(rd_idx, valor);
    } 
    
    else if (opcode == "auipc") {
        registro.escrever_no_registro(rd_idx, valor + PC_counter);
    } 
    
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_I(string opcode, string rd, string rs1, string imm, Registers& registro, Memory& memoria) {
    validar_registrador(rd);    
    validar_imediato(imm);
    int rd_idx = stoi(rd.substr(1));
    
    int rs1_idx = 0;
    if (rs1 != "zero" && rs1 != "0") {
        rs1_idx = stoi(rs1.substr(1));
    }

    int32_t imm_val = stoi(imm);

    if (opcode == "addi") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) + imm_val);
    } 
    
    else if (opcode == "xori") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) ^ imm_val);
    } 
    
    else if (opcode == "ori") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) | imm_val);
    } 
    
    else if (opcode == "andi") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) & imm_val);
    } 
    
    else if (opcode == "slli") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) << (imm_val & 0x1F));
    } 
    
    else if (opcode == "srli") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) >> (imm_val & 0x1F));
    } 
    
    else if (opcode == "srai") {
        registro.escrever_no_registro(rd_idx, (int32_t)registro.ler_no_registro(rs1_idx) >> (imm_val & 0x1F));
    } 
    
    else if (opcode == "slti") {
        registro.escrever_no_registro(rd_idx, (int32_t)registro.ler_no_registro(rs1_idx) < imm_val);
    } 
    
    else if (opcode == "sltiu") {
        registro.escrever_no_registro(rd_idx, registro.ler_no_registro(rs1_idx) < (uint32_t)imm_val);
    } 
    
    else if (opcode == "lb") {
        registro.escrever_no_registro(rd_idx, (int8_t)memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val));
    } 
    
    else if (opcode == "lh") {
        uint16_t halfword = memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val) |
                            (memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 1) << 8);
        registro.escrever_no_registro(rd_idx, (int16_t)halfword);
    } 
    
    else if (opcode == "lw") {
        uint32_t word = memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val) |
                        (memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 1) << 8) |
                        (memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 2) << 16) |
                        (memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 3) << 24);
        registro.escrever_no_registro(rd_idx, word);
    } 
    
    else if (opcode == "lbu") {
        registro.escrever_no_registro(rd_idx, memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val));
    } 
    
    else if (opcode == "lhu") {
        uint16_t halfword = memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val) |
                            (memoria.ler_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 1) << 8);
        registro.escrever_no_registro(rd_idx, halfword);
    } 
    
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_S(string opcode, string rs2, string offset_rs1, Registers& registro, Memory& memoria) {
    validar_registrador(rs2);
    auto pos = offset_rs1.find('(');
    if (pos == string::npos || offset_rs1.back() != ')') {
        cerr << "Formato inválido para offset(rs1): " << offset_rs1 << endl;
        exit(EXIT_FAILURE);
    }
    string offset = offset_rs1.substr(0, pos);
    string rs1 = offset_rs1.substr(pos + 1, offset_rs1.size() - pos - 2);
    validar_imediato(offset);
    validar_registrador(rs1);

    int32_t imm_val = stoi(offset);
    int rs1_idx = stoi(rs1.substr(1));
    int rs2_idx = stoi(rs2.substr(1));

    if (opcode == "sb") {
        uint8_t byte = registro.ler_no_registro(rs2_idx) & 0xFF;
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val, byte);
    } 
    
    else if (opcode == "sh") {
        uint16_t halfword = registro.ler_no_registro(rs2_idx) & 0xFFFF;
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val, halfword & 0xFF);
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 1, (halfword >> 8) & 0xFF);
    } 
    
    else if (opcode == "sw") {
        uint32_t word = registro.ler_no_registro(rs2_idx);
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val, word & 0xFF);
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 1, (word >> 8) & 0xFF);
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 2, (word >> 16) & 0xFF);
        memoria.escrever_na_memoria(registro.ler_no_registro(rs1_idx) + imm_val + 3, (word >> 24) & 0xFF);
    } 
    
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

char identificarFormato(const string& opcode) {
    // Formato R
    if (opcode == "add" || opcode == "sub" || opcode == "xor" || opcode == "or" || opcode == "and" ||
        opcode == "sll" || opcode == "srl" || opcode == "sra" || opcode == "slt" || opcode == "sltu") {
        return 'R';
    }
    // Formato U
    else if (opcode == "lui" || opcode == "auipc") {
        return 'U';
    }
    // Formato I
    else if (opcode == "addi" || opcode == "xori" || opcode == "ori" || opcode == "andi" ||
             opcode == "slli" || opcode == "srli" || opcode == "srai" || opcode == "slti" || opcode == "sltiu" ||
             opcode == "lb" || opcode == "lh" || opcode == "lw" || opcode == "lbu" || opcode == "lhu") {
        return 'I';
    }
    // Formato S
    else if (opcode == "sb" || opcode == "sh" || opcode == "sw") {
        return 'S';
    }
    // Instrução desconhecida
    else {
        return 'D';
    }
}

void executarInstrucoes(vector<string> linha, Registers& registro, Memory& memoria, uint32_t PC_counter) {
    if (linha.empty()) {
        cerr << "Linha vazia passada para execução." << endl;
        return;
    }

    string opcode = linha[0], rd, rs1, rs2, imm, offset_rs1;
    char formato = identificarFormato(opcode);

    // Formato R (aritméticas e lógicas registro→registro):
    if (formato == 'R') {
        if (linha.size() < 4) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rd = linha[1];
        rs1 = linha[2];
        rs2 = linha[3];

        formato_R(opcode, rd, rs1, rs2, registro);
    }

    // Formato U (upper immediate):
    else if (formato == 'U') {
        if (linha.size() < 3) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rd = linha[1];
        imm = linha[2];

        formato_U(opcode, rd, imm, registro, PC_counter);
    }

    // Formato I (imediato; inclui addi e cargas de memória):
    else if (formato == 'I') {
        if (linha.size() < 4) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rd = linha[1];
        rs1 = linha[2];
        imm = linha[3];

        formato_I(opcode, rd, rs1, imm, registro, memoria);
    }

    // Formato S (armazenamento):
    else if (formato == 'S') {
        if (linha.size() < 3) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rs2 = linha[1];
        offset_rs1 = linha[2];

        formato_S(opcode, rs2, offset_rs1, registro, memoria);
    }

    // Instrução desconhecida:
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}
