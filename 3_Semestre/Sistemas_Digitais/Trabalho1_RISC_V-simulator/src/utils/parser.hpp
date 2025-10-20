#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

using namespace std;

// Função para dividir uma instrução em partes
vector<string> dividir_instrucoes(const string& instruction);

// Remover virgulas e espaço
string remover_espaco(const string& linha);

// Função para analisar uma linha de instrução e retornar um vetor de strings
vector<vector<string>> lerInstrucoes(const string& line);

#endif // PARSER_HPP