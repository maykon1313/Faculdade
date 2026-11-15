/*
 * Analisador sintatico descendente recursivo gerado a partir de testes/gramaticas/json.ebnf.
 * Arquivo gerado automaticamente: nao edite.
 */
#ifndef PARSER_GERADO_H
#define PARSER_GERADO_H

typedef enum {
    T_FIM,   /* $ */
    T_STRING,   /* STRING */
    T_NUMBER,   /* NUMBER */
    T_BOOLEAN,   /* BOOLEAN */
    T_NULO,   /* NULO */
    T_ABRE_CHAVE,   /* '{' */
    T_VIRGULA,   /* ',' */
    T_FECHA_CHAVE,   /* '}' */
    T_DOIS_PONTOS,   /* ':' */
    T_ABRE_COL,   /* '[' */
    T_FECHA_COL   /* ']' */
} TipoToken;

typedef struct {
    int tipo;
    char lexema[100];
    int linha;
    int coluna;
} Token;

#define TOKEN_FIM T_FIM

const char *nome_token(int tipo);
int  pertence(int tipo, const int *conjunto);
void avancar(void);
void match(int esperado);
void erro_sintatico(const int *esperados);
void arvore_entra(const char *nao_terminal);
void arvore_sai(void);

void parse_json(void);
void parse_valor(void);
void parse_objeto(void);
void parse_array(void);
void parse_par(void);

#endif
