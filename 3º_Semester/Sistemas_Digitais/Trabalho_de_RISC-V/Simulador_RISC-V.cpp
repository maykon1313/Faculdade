#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;
namespace Constantes {const string WHITESPACE = " \t\n\r";}

// --- Definições globais de registradores e memória ---
static uint32_t regs[32] = {0};                  // 32 registradores x0–x31
static vector<uint8_t> memory(1024 * 1024, 0);   // 1 MiB de memória

string remover_espaco(const string& linha);
vector<vector<string>> lerInstrucoes(const string& nome_do_arquivo);
void executar(vector<string> linha);
vector<string> dividir_instrucao(const string& linha);
char identificarFormato(const string& opcode);
 
int main() {
    vector<vector<string>> instrucoes = lerInstrucoes("entrada2.txt");
    
    for (const vector<string>& linha : instrucoes) {
        //executar(linha);
        
        for (const string& inst : linha) {
            cout << "[" << inst << "]" << " ";
        }
        cout << endl;
    }
    
    return 0;
}

// Funções auxiliares:
vector<string> dividir_instrucao(const string& linha) {
    vector<string> partes;
    stringstream ss(linha);
    string palavra;

    while (ss >> palavra) {
        // Remove vírgula se existir no final da palavra
        if (!palavra.empty() && palavra.back() == ',') {
            palavra.pop_back(); // Remove a vírgula
        }
        partes.push_back(palavra);
    }

    return partes;
}

string remover_espaco(const string& linha) {
    size_t comeco = linha.find_first_not_of(Constantes::WHITESPACE);

    // string::npos = -1 = Não encontrado.
    if (comeco == string::npos) return "";

    size_t fim = linha.find_last_not_of(Constantes::WHITESPACE);

    return linha.substr(comeco, fim - comeco + 1);
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

// Converte "x5" → 5
int idxReg(const string& reg) {
    if (reg.size()>1 && reg[0]=='x')
        return stoi(reg.substr(1));
    cerr << "Formato inválido de registrador: " << reg << endl;
    exit(EXIT_FAILURE);
}

// Converte string de imediato (decimal ou 0xHEX) para int32_t
int32_t parseImm(const string& s) {
    int base = 10;
    size_t start = 0;
    if (s.size()>2 && s[0]=='0' && (s[1]=='x' || s[1]=='X')) {
        base = 16;
        start = 2;
    }
    return stoi(s.substr(start), nullptr, base);
}

// Parseia formato S: "offset(reg)" → {offset, idx_reg_base}
pair<int32_t,int> parseOffsetBase(const string& s) {
    auto p = s.find('(');
    auto q = s.find(')');
    int32_t off = parseImm(s.substr(0,p));
    string baseReg = s.substr(p+1, q-p-1);
    return { off, idxReg(baseReg) };
}

// Função de leitura de entrada:
vector<vector<string>> lerInstrucoes(const string& nome_do_arquivo) {
    ifstream arquivo(nome_do_arquivo);
    vector<vector<string>> instrucoes;
    vector<string> partes;
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o aquivo: " << nome_do_arquivo << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(arquivo, linha)) {
        size_t comentario = linha.find('#');

        // string::npos = -1 = Não encontrado.
        if (comentario != string::npos) { 
            linha = linha.substr(0, comentario);
        }

        linha = remover_espaco(linha);

        if (!linha.empty()) {
            partes = dividir_instrucao(linha);
            instrucoes.push_back(partes);
        }
    }

    arquivo.close();
    return instrucoes;
}

// Funções principais:
void formato_R(string opcode, string rd,  string rs1, string rs2) {
    if (opcode == "add") {
        
    } else if (opcode == "sub") {

    } else if (opcode == "xor") {

    } else if (opcode == "or") {

    } else if (opcode == "and") {

    } else if (opcode == "sll") {

    } else if (opcode == "srl") {

    } else if (opcode == "sra") {

    } else if (opcode == "slt") {

    } else if (opcode == "sltu") {

    } else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_U(string opcode, string rd,string imm) {
    if (opcode == "lui") {

    } else if (opcode == "auipc") {

    } else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_I(string opcode, string rd,string rs1, string imm) {
    if (opcode == "addi") {

    } else if (opcode == "xori") {

    } else if (opcode == "ori") {

    } else if (opcode == "andi") {

    } else if (opcode == "slli") {

    } else if (opcode == "srli") {

    } else if (opcode == "srai") {

    } else if (opcode == "slti") {

    } else if (opcode == "sltiu") {

    } else if (opcode == "lb") {

    } else if (opcode == "lh") {

    } else if (opcode == "lw") {

    } else if (opcode == "lbu") {

    } else if (opcode == "lhu") {

    } else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void formato_S(string opcode, string rs2,string offset_rs1) {
    if (opcode == "sb") {

    } else if (opcode == "sh") {

    } else if (opcode == "sw") {

    } else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}

void executar(vector<string> linha) {
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

        formato_R(opcode, rd, rs1, rs2);
    }

    // Formato U (upper immediate):
    else if (formato == 'U') {
        if (linha.size() < 3) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rd = linha[1];
        imm = linha[2];

        formato_U(opcode, rd, imm);
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

        formato_I(opcode, rd, rs1, imm);
    }

    // Formato S (armazenamento):
    else if (formato == 'S') {
        if (linha.size() < 3) {
            cerr << "Instrução incompleta." << endl;
            return;
        }

        rs2 = linha[1];
        offset_rs1 = linha[2];

        formato_S(opcode, rs2, offset_rs1);
    }

    // Instrução desconhecida:
    else {
        cerr << "Instrução não identificada: " << opcode << endl;
    }
}
