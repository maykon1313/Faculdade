/*
 * microc.flex
 * Esqueleto do analisador lexico (scanner) para a linguagem Micro C.
 * Disciplina: Compiladores I - FACOM
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------
 * 1. VOCABULARIO DE TOKENS (equivalente a tokens.h)
 * ------------------------------------------------------------------- */

typedef enum {
    /* Tokens fundamentais */
    UNDEF,          /* token indefinido (usado para reportar erros) */
    ID,             /* identificador                                */
    END_OF_FILE,    /* fim de arquivo                               */

    /* Constantes literais */
    INTEGERCONST,
    CHARCONST,
    STRINGCONST,

    /* Operadores aritmeticos */
    PLUS, MINUS, MUL, DIV, MOD,

    /* Operadores relacionais e logicos */
    EQ, NEQ, LT, GT, LEQ, GEQ, AND, OR, NOT,

    /* Simbolos de atribuicao e pontuacao */
    ASSIGN, SEMICOLON, COMMA, LPAREN, RPAREN,
    LBRACE, RBRACE, LBRACKET, RBRACKET,

    /* Palavras reservadas */
    MAIN, IF, ELSE, FOR, RETURN, INT, CHAR, PRINT
} TokenType;

/* Melhor legibilidade, mesma sequencia do TokenType. */
static const char *nome_token[] = {
    "UNDEF", "ID", "END_OF_FILE",
    "INTEGERCONST", "CHARCONST", "STRINGCONST",
    "PLUS", "MINUS", "MUL", "DIV", "MOD",
    "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "AND", "OR", "NOT",
    "ASSIGN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN",
    "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
    "MAIN", "IF", "ELSE", "FOR", "RETURN", "INT", "CHAR", "PRINT"
};

/* Valor semantico do token corrente. */
typedef struct {
    char *symbol;      /* lexema para ID, INTEGERCONST, CHARCONST, STRINGCONST */
    char *error_msg;   /* mensagem de erro, usada apenas quando tipo == UNDEF   */
} YYSTYPE;

YYSTYPE microc_yylval;

int linha_atual = 1;

typedef struct Simbolo {
    char *texto;
    size_t tamanho;
    struct Simbolo *proximo;
} Simbolo;

static Simbolo *tabela_simbolos;

static char *adiciona_simbolo(const char *texto, size_t tamanho) {
    Simbolo *simbolo = tabela_simbolos;

    while (simbolo != NULL) {
        if (simbolo->tamanho == tamanho &&
            memcmp(simbolo->texto, texto, tamanho) == 0) {
            return simbolo->texto;
        }
        simbolo = simbolo->proximo;
    }

    simbolo = malloc(sizeof(Simbolo));
    simbolo->texto = malloc(tamanho + 1);
    memcpy(simbolo->texto, texto, tamanho);
    simbolo->texto[tamanho] = '\0';
    simbolo->tamanho = tamanho;
    simbolo->proximo = tabela_simbolos;
    tabela_simbolos = simbolo;
    return simbolo->texto;
}

static void guarda_lexema(void) {
    microc_yylval.symbol = adiciona_simbolo(yytext, strlen(yytext));
}

static char *literal_buffer;
static size_t literal_length;
static size_t literal_capacity;
static int pode_iniciar_inteiro_negativo = 1;

static int retorna_token(TokenType tipo) {
    switch (tipo) {
        case ID:
        case INTEGERCONST:
        case CHARCONST:
        case STRINGCONST:
        case RPAREN:
        case RBRACKET:
            pode_iniciar_inteiro_negativo = 0;
            break;
        default:
            pode_iniciar_inteiro_negativo = 1;
            break;
    }
    return tipo;
}

static void inicia_literal(void) {
    literal_length = 0;
    literal_capacity = 32;
    literal_buffer = realloc(literal_buffer, literal_capacity);
    literal_buffer[0] = '\0';
}

static void adiciona_literal(char caractere) {
    if (literal_length + 1 >= literal_capacity) {
        literal_capacity *= 2;
        literal_buffer = realloc(literal_buffer, literal_capacity);
    }
    literal_buffer[literal_length++] = caractere;
    literal_buffer[literal_length] = '\0';
}

static void adiciona_escape(const char *texto) {
    switch (texto[1]) {
        case 'n': adiciona_literal('\n'); break;
        case 't': adiciona_literal('\t'); break;
        case '\\': adiciona_literal('\\'); break;
        case '"': adiciona_literal('"'); break;
        case '0': adiciona_literal('\0'); break;
    }
}

static void guarda_literal(void) {
    microc_yylval.symbol = adiciona_simbolo(literal_buffer, literal_length);
}

%}

/* -----------------------------------------------------------------------
 * 2. SECAO DE DEFINICOES
 * ------------------------------------------------------------------- */

DIGIT       [0-9]
LETRA       [a-zA-Z_]
ALFANUM     [a-zA-Z0-9_]

%x COMMENT STRING_LITERAL CHAR_LITERAL

%%

 /* -----------------------------------------------------------------------
  * 3. SECAO DE REGRAS
  * --------------------------------------------------------------------- */

 /* --- Fim de arquivo -------------------------------------------------- */
<INITIAL><<EOF>>    { return END_OF_FILE; }

 /* --- Espacos em branco e quebras de linha ---------------------------- */
\n                  { linha_atual++; }
[ \t\r]+            { /* ignora espacos em branco */ }

 /* --- Comentarios ----------------------------------------------------- */
"//".*              { /* comentario de linha: ignora ate o fim da linha */ }

"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>\n         { linha_atual++; }
<COMMENT><<EOF>>    {
                        microc_yylval.error_msg = "EOF em comentario";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<COMMENT>.          { /* consome qualquer outro caractere dentro do comentario */ }

 /* Fechamento de comentario sem abertura correspondente. */
"*/"                {
                        microc_yylval.error_msg = "Comentario nao iniciado";
                        return UNDEF;
                    }

 /* --- Palavras reservadas e identificadores ----------------------------
  * Foi implementado o reconhecimento das palavras reservadas usando
  * o strcmp(). Além de salvar o lexema, usanddo a 
  * função guarda_lexema() quando realmente seja um ID. */
{LETRA}{ALFANUM}*   {
                        if (strcmp(yytext, "main") == 0) return retorna_token(MAIN);
                        if (strcmp(yytext, "if") == 0) return retorna_token(IF);
                        if (strcmp(yytext, "else") == 0) return retorna_token(ELSE);
                        if (strcmp(yytext, "for") == 0) return retorna_token(FOR);
                        if (strcmp(yytext, "return") == 0) return retorna_token(RETURN);
                        if (strcmp(yytext, "int") == 0) return retorna_token(INT);
                        if (strcmp(yytext, "char") == 0) return retorna_token(CHAR);
                        if (strcmp(yytext, "print") == 0) return retorna_token(PRINT);
                        guarda_lexema();
                        return retorna_token(ID);
                    }

 /* --- Constantes inteiras -----------------------------------------------
  * Foi implementado o reconhecimento de números negativos, usando lookahead. */
[-]{DIGIT}+         {
                        if (!pode_iniciar_inteiro_negativo) {
                            yyless(1);
                            return retorna_token(MINUS);
                        }
                        guarda_lexema();
                        return retorna_token(INTEGERCONST);
                    }

{DIGIT}+            {
                        guarda_lexema();
                        return retorna_token(INTEGERCONST);
                    }

 /* --- Constantes de caractere --------------------------------------------
  * Aspas simples está sendo reconhecida, assim como seus erros.*/
\'                  { inicia_literal(); BEGIN(CHAR_LITERAL); }
<CHAR_LITERAL>\\[nt\\"0]    { adiciona_escape(yytext); }
<CHAR_LITERAL>[^\\'\n]      { adiciona_literal(yytext[0]); }
<CHAR_LITERAL>\'            {
                        if (literal_length != 1) {
                            microc_yylval.error_msg = "Caractere invalido";
                            BEGIN(INITIAL);
                            return UNDEF;
                        }
                        guarda_literal();
                        BEGIN(INITIAL);
                        return retorna_token(CHARCONST);
                    }
<CHAR_LITERAL>\\.           {
                        microc_yylval.error_msg = "Escape invalido";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<CHAR_LITERAL>\n            {
                        linha_atual++;
                        microc_yylval.error_msg = "Caractere nao terminado";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<CHAR_LITERAL><<EOF>>       {
                        microc_yylval.error_msg = "EOF em caractere";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }


 /* --- Constantes de string -------------------------------------------
  * O padrão de aspas dupla está sendo reconhecida, assim como os seguintes erros:
  *   - EOF antes do fechamento da string ("EOF em string")
  *   - quebra de linha nao escapada dentro da string ("String nao terminada")
  *   - caractere nulo dentro da string ("String contem caractere nulo")
  * Alem disso, está sendo convertido as sequencias de escape (\n, \t, \\, \", \0)
  * para os caracteres correspondentes antes de armazenar o lexema. */
\"                  { inicia_literal(); BEGIN(STRING_LITERAL); }
<STRING_LITERAL>\\[nt\\\"0] { adiciona_escape(yytext); }
<STRING_LITERAL>\0         {
                        microc_yylval.error_msg = "String contem caractere nulo";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<STRING_LITERAL>[^\\\"\n]   { adiciona_literal(yytext[0]); }
<STRING_LITERAL>\"          {
                        guarda_literal();
                        BEGIN(INITIAL);
                        return retorna_token(STRINGCONST);
                    }
<STRING_LITERAL>\\.         {
                        microc_yylval.error_msg = "Escape invalido";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<STRING_LITERAL>\n           {
                        linha_atual++;
                        microc_yylval.error_msg = "String nao terminada";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }
<STRING_LITERAL><<EOF>>      {
                        microc_yylval.error_msg = "EOF em string";
                        BEGIN(INITIAL);
                        return UNDEF;
                    }


 /* --- Operadores relacionais e logicos --------------------------------- */
"=="                { return retorna_token(EQ); }
"="                 { return retorna_token(ASSIGN); }
"!="                { return retorna_token(NEQ); }
"!"                 { return retorna_token(NOT); }
"<="                { return retorna_token(LEQ); }
"<"                 { return retorna_token(LT); }
">="                { return retorna_token(GEQ); }
">"                 { return retorna_token(GT); }
"&&"                { return retorna_token(AND); }
"||"                { return retorna_token(OR); }

 /* --- Operadores aritmeticos e simbolos de pontuacao (ja prontos) ------ */
"+"                 { return retorna_token(PLUS); }
"-"                 { return retorna_token(MINUS); }
"*"                 { return retorna_token(MUL); }
"/"                 { return retorna_token(DIV); }
"%"                 { return retorna_token(MOD); }
";"                 { return retorna_token(SEMICOLON); }
","                 { return retorna_token(COMMA); }
"("                 { return retorna_token(LPAREN); }
")"                 { return retorna_token(RPAREN); }
"{"                 { return retorna_token(LBRACE); }
"}"                 { return retorna_token(RBRACE); }
"["                 { return retorna_token(LBRACKET); }
"]"                 { return retorna_token(RBRACKET); }

 /* --- Caractere invalido ------------------------------------------------ */
.                   {
                        microc_yylval.error_msg = strdup(yytext);
                        return UNDEF;
                    }

%%

/* -----------------------------------------------------------------------
 * 4. SUB-ROTINAS DO USUARIO
 * ------------------------------------------------------------------- */

/* yywrap: Ao atingir o EOF, o flexe deve parar a leitura. */
int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.mc>\n", argv[0]);
        return 1;
    }

    FILE *arquivo_fonte = fopen(argv[1], "r");
    if (!arquivo_fonte) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }
    yyin = arquivo_fonte;

    int tipo;
    while ((tipo = yylex()) != END_OF_FILE) {
        if (tipo == UNDEF) {
            fprintf(stderr, "ERRO LEXICO (linha %d): %s\n",
                    linha_atual, microc_yylval.error_msg);
            continue;
        }
         const char *lexema = yytext;
         if (tipo == ID || tipo == INTEGERCONST ||
             tipo == CHARCONST || tipo == STRINGCONST) {
             lexema = microc_yylval.symbol;
         }
         printf("Token: tipo = %-13s lexema = '%s'  linha = %d\n",
             nome_token[tipo], lexema, linha_atual);
    }

    fclose(arquivo_fonte);
    return 0;
}
