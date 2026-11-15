/*
 * Analisador sintatico descendente recursivo gerado a partir de testes/gramaticas/microc.ebnf.
 * Arquivo gerado automaticamente: nao edite.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microc.h"

#define SUPORTE_ARVORE 0

/* ---- conjuntos de tokens ---- */

static const int conj_0[] = { LBRACE, ID, SEMICOLON, IF, FOR, RETURN, PRINT, -1 };
static const int conj_1[] = { INT, CHAR, -1 };
static const int conj_2[] = { LPAREN, ID, INTEGERCONST, CHARCONST, NOT, -1 };
static const int conj_3[] = { LPAREN, ID, INTEGERCONST, STRINGCONST, CHARCONST, NOT, -1 };
static const int conj_4[] = { AND, OR, -1 };
static const int conj_5[] = { EQ, NEQ, LT, GT, LEQ, GEQ, -1 };
static const int conj_6[] = { PLUS, MINUS, -1 };
static const int conj_7[] = { MUL, DIV, MOD, -1 };

/* ---- estado do analisador ---- */

static Token tok;                  /* token corrente (lookahead) */
static int imprimir_arvore = 0;    /* opcao --tree */
static int nivel_arvore = 0;
static FILE *arquivo_tokens = NULL; /* opcao --tokens */
static FILE *arquivo_entrada = NULL;

static Token token_de_arquivo(void);

static void limpar_recursos(void)
{
    if (arquivo_tokens != NULL) {
        fclose(arquivo_tokens);
        arquivo_tokens = NULL;
    } else {
        scanner_finalizar();
        if (arquivo_entrada != NULL && arquivo_entrada != stdin) {
            fclose(arquivo_entrada);
            arquivo_entrada = NULL;
        }
    }
}

const char *nome_token(int tipo)
{
    switch (tipo) {
    case END_OF_FILE: return "fim de arquivo";
    case INT: return "'int'";
    case MAIN: return "'main'";
    case LPAREN: return "'('";
    case RPAREN: return "')'";
    case LBRACE: return "'{'";
    case RBRACE: return "'}'";
    case ID: return "ID";
    case LBRACKET: return "'['";
    case INTEGERCONST: return "INTEGERCONST";
    case RBRACKET: return "']'";
    case SEMICOLON: return "';'";
    case CHAR: return "'char'";
    case IF: return "'if'";
    case ELSE: return "'else'";
    case FOR: return "'for'";
    case RETURN: return "'return'";
    case PRINT: return "'print'";
    case ASSIGN: return "'='";
    case STRINGCONST: return "STRINGCONST";
    case AND: return "'&&'";
    case OR: return "'||'";
    case EQ: return "'=='";
    case NEQ: return "'!='";
    case LT: return "'<'";
    case GT: return "'>'";
    case LEQ: return "'<='";
    case GEQ: return "'>='";
    case PLUS: return "'+'";
    case MINUS: return "'-'";
    case MUL: return "'*'";
    case DIV: return "'/'";
    case MOD: return "'%'";
    case CHARCONST: return "CHARCONST";
    case NOT: return "'!'";
    default: return "token desconhecido";
    }
}

static void escrever_posicao(void)
{
    fprintf(stderr, "linha %d: ", tok.linha);
}

/* Le o proximo token para tok. */
void avancar(void)
{
    if (arquivo_tokens != NULL)
        tok = token_de_arquivo();
    else
        tok = proximo_token();
    if (tok.tipo == UNDEF) {
        fprintf(stderr, "linha %d: erro lexico: %s\n", tok.linha, tok.lexema);
        exit(EXIT_FAILURE);
    }
}

/* ---- primitivas ---- */

int pertence(int tipo, const int *conjunto)
{
    for (; *conjunto != -1; conjunto++)
        if (*conjunto == tipo)
            return 1;
    return 0;
}

/* Reporta o erro com os tokens esperados (lista terminada em -1) e encerra. */
void erro_sintatico(const int *esperados)
{
    int i;
    escrever_posicao();
    if ((int) tok.tipo == TOKEN_FIM)
        fprintf(stderr, "encontrado fim de arquivo, ");
    else
        fprintf(stderr, "encontrado '%s', ", tok.lexema);
    if (esperados[0] != -1 && esperados[1] == -1) {
        fprintf(stderr, "esperado %s\n", nome_token(esperados[0]));
    } else {
        fprintf(stderr, "esperado um de {");
        for (i = 0; esperados[i] != -1; i++)
            fprintf(stderr, "%s%s", i > 0 ? ", " : "", nome_token(esperados[i]));
        fprintf(stderr, "}\n");
    }
    exit(EXIT_FAILURE);
}

static void recuo(void)
{
    int i;
    for (i = 0; i < nivel_arvore; i++)
        fputs("  ", stdout);
}

void arvore_entra(const char *nao_terminal)
{
    if (imprimir_arvore) {
        recuo();
        printf("%s\n", nao_terminal);
    }
    nivel_arvore++;
}

void arvore_sai(void)
{
    nivel_arvore--;
}

/* Consome o token corrente se for do tipo esperado; senao, erro. */
void match(int esperado)
{
    int lista[2];
    if ((int) tok.tipo != esperado) {
        lista[0] = esperado;
        lista[1] = -1;
        erro_sintatico(lista);
    }
    if (SUPORTE_ARVORE && imprimir_arvore) {
        recuo();
        if (nome_token(tok.tipo)[0] == '\'')
            printf("%s\n", nome_token(tok.tipo));
        else
            printf("%s '%s'\n", nome_token(tok.tipo), tok.lexema);
    }
    avancar();
}

static int linha_arq_tokens = 0;

static Token token_de_arquivo(void)
{
    char buf[1024];
    Token t;
    memset(&t, 0, sizeof t);
    while (fgets(buf, sizeof buf, arquivo_tokens) != NULL) {
        char *p = buf, *lex_inicio, *lex_fim, *lin_str;
        int tipo_val, linha_val;
        linha_arq_tokens++;
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        if (*p == '\0') continue;
        if (strncmp(p, "Token:", 6) != 0) goto malformado;
        p = strstr(p + 6, "tipo =");
        if (p == NULL) goto malformado;
        if (sscanf(p + 6, "%d", &tipo_val) != 1) goto malformado;
        p = strstr(p, "lexema = '");
        if (p == NULL) goto malformado;
        lex_inicio = p + 10;
        lin_str = strstr(lex_inicio, "', linha =");
        if (lin_str == NULL) goto malformado;
        lex_fim = lin_str;
        if (sscanf(lin_str + 10, "%d", &linha_val) != 1) goto malformado;
        t.tipo = tipo_val;
        t.linha = linha_val;
        {
            size_t tam = (size_t)(lex_fim - lex_inicio);
            if (tam >= sizeof t.lexema) tam = sizeof t.lexema - 1;
            memcpy(t.lexema, lex_inicio, tam);
            t.lexema[tam] = '\0';
        }
        return t;
    malformado:
        fprintf(stderr, "linha %d do arquivo de tokens malformada\n", linha_arq_tokens);
        exit(EXIT_FAILURE);
    }
    t.tipo = TOKEN_FIM;
    return t;
}

/* ---- procedimentos (um por nao terminal) ---- */

/* programa = 'int' 'main' '(' ')' bloco ; */
void parse_programa(void)
{
    match(INT);
    match(MAIN);
    match(LPAREN);
    match(RPAREN);
    parse_bloco();
}

/* bloco = '{' { declaracao } { comando } '}' ; */
void parse_bloco(void)
{
    match(LBRACE);
    while (tok.tipo == INT || tok.tipo == CHAR) {
        parse_declaracao();
    }
    while (pertence(tok.tipo, conj_0)) {
        parse_comando();
    }
    match(RBRACE);
}

/* declaracao = tipo ID [ '[' INTEGERCONST ']' ] ';' ; */
void parse_declaracao(void)
{
    parse_tipo();
    match(ID);
    if (tok.tipo == LBRACKET) {
        match(LBRACKET);
        match(INTEGERCONST);
        match(RBRACKET);
    }
    match(SEMICOLON);
}

/* comando = comando_if | comando_for | atribuicao | comando_return | comando_print | bloco | ';' ; */
void parse_comando(void)
{
    if (tok.tipo == IF) {
        parse_comando_if();
    } else if (tok.tipo == FOR) {
        parse_comando_for();
    } else if (tok.tipo == ID) {
        parse_atribuicao();
    } else if (tok.tipo == RETURN) {
        parse_comando_return();
    } else if (tok.tipo == PRINT) {
        parse_comando_print();
    } else if (tok.tipo == LBRACE) {
        parse_bloco();
    } else if (tok.tipo == SEMICOLON) {
        match(SEMICOLON);
    } else {
        erro_sintatico(conj_0);
    }
}

/* tipo = 'int' | 'char' ; */
void parse_tipo(void)
{
    if (tok.tipo == INT) {
        match(INT);
    } else if (tok.tipo == CHAR) {
        match(CHAR);
    } else {
        erro_sintatico(conj_1);
    }
}

/* comando_if = 'if' '(' expressao ')' comando [ 'else' comando ] ; */
void parse_comando_if(void)
{
    match(IF);
    match(LPAREN);
    parse_expressao();
    match(RPAREN);
    parse_comando();
    if (tok.tipo == ELSE) {
        match(ELSE);
        parse_comando();
    }
}

/* comando_for = 'for' '(' atribuicao_interna ';' expressao ';' atribuicao_interna ')' comando ; */
void parse_comando_for(void)
{
    match(FOR);
    match(LPAREN);
    parse_atribuicao_interna();
    match(SEMICOLON);
    parse_expressao();
    match(SEMICOLON);
    parse_atribuicao_interna();
    match(RPAREN);
    parse_comando();
}

/* atribuicao = atribuicao_interna ';' ; */
void parse_atribuicao(void)
{
    parse_atribuicao_interna();
    match(SEMICOLON);
}

/* comando_return = 'return' [ expressao ] ';' ; */
void parse_comando_return(void)
{
    match(RETURN);
    if (pertence(tok.tipo, conj_2)) {
        parse_expressao();
    }
    match(SEMICOLON);
}

/* comando_print = 'print' '(' conteudo_print ')' ';' ; */
void parse_comando_print(void)
{
    match(PRINT);
    match(LPAREN);
    parse_conteudo_print();
    match(RPAREN);
    match(SEMICOLON);
}

/* expressao = expressao_logica ; */
void parse_expressao(void)
{
    parse_expressao_logica();
}

/* atribuicao_interna = ID [ '[' expressao ']' ] '=' expressao ; */
void parse_atribuicao_interna(void)
{
    match(ID);
    if (tok.tipo == LBRACKET) {
        match(LBRACKET);
        parse_expressao();
        match(RBRACKET);
    }
    match(ASSIGN);
    parse_expressao();
}

/* conteudo_print = STRINGCONST | expressao ; */
void parse_conteudo_print(void)
{
    if (tok.tipo == STRINGCONST) {
        match(STRINGCONST);
    } else if (pertence(tok.tipo, conj_2)) {
        parse_expressao();
    } else {
        erro_sintatico(conj_3);
    }
}

/* expressao_logica = expressao_relacional { ( '&&' | '||' ) expressao_relacional } ; */
void parse_expressao_logica(void)
{
    parse_expressao_relacional();
    while (tok.tipo == AND || tok.tipo == OR) {
        if (tok.tipo == AND) {
            match(AND);
        } else if (tok.tipo == OR) {
            match(OR);
        } else {
            erro_sintatico(conj_4);
        }
        parse_expressao_relacional();
    }
}

/* expressao_relacional = expressao_aritmetica [ operador_relacional expressao_aritmetica ] ; */
void parse_expressao_relacional(void)
{
    parse_expressao_aritmetica();
    if (pertence(tok.tipo, conj_5)) {
        parse_operador_relacional();
        parse_expressao_aritmetica();
    }
}

/* expressao_aritmetica = termo { ( '+' | '-' ) termo } ; */
void parse_expressao_aritmetica(void)
{
    parse_termo();
    while (tok.tipo == PLUS || tok.tipo == MINUS) {
        if (tok.tipo == PLUS) {
            match(PLUS);
        } else if (tok.tipo == MINUS) {
            match(MINUS);
        } else {
            erro_sintatico(conj_6);
        }
        parse_termo();
    }
}

/* operador_relacional = '==' | '!=' | '<' | '>' | '<=' | '>=' ; */
void parse_operador_relacional(void)
{
    if (tok.tipo == EQ) {
        match(EQ);
    } else if (tok.tipo == NEQ) {
        match(NEQ);
    } else if (tok.tipo == LT) {
        match(LT);
    } else if (tok.tipo == GT) {
        match(GT);
    } else if (tok.tipo == LEQ) {
        match(LEQ);
    } else if (tok.tipo == GEQ) {
        match(GEQ);
    } else {
        erro_sintatico(conj_5);
    }
}

/* termo = fator { ( '*' | '/' | '%' ) fator } ; */
void parse_termo(void)
{
    parse_fator();
    while (tok.tipo == MUL || tok.tipo == DIV || tok.tipo == MOD) {
        if (tok.tipo == MUL) {
            match(MUL);
        } else if (tok.tipo == DIV) {
            match(DIV);
        } else if (tok.tipo == MOD) {
            match(MOD);
        } else {
            erro_sintatico(conj_7);
        }
        parse_fator();
    }
}

/* fator = '(' expressao ')' | ID [ '[' expressao ']' ] | INTEGERCONST | CHARCONST | '!' fator ; */
void parse_fator(void)
{
    if (tok.tipo == LPAREN) {
        match(LPAREN);
        parse_expressao();
        match(RPAREN);
    } else if (tok.tipo == ID) {
        match(ID);
        if (tok.tipo == LBRACKET) {
            match(LBRACKET);
            parse_expressao();
            match(RBRACKET);
        }
    } else if (tok.tipo == INTEGERCONST) {
        match(INTEGERCONST);
    } else if (tok.tipo == CHARCONST) {
        match(CHARCONST);
    } else if (tok.tipo == NOT) {
        match(NOT);
        parse_fator();
    } else {
        erro_sintatico(conj_2);
    }
}

/* ---- programa principal ---- */

int main(int argc, char **argv)
{
    int i, fim[2];
    const char *arquivo = NULL, *tokens = NULL;
    FILE *entrada = stdin;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--tree") == 0) {
            imprimir_arvore = 1;
        } else if (strcmp(argv[i], "--tokens") == 0 && i + 1 < argc) {
            tokens = argv[++i];
        } else if (argv[i][0] == '-' && argv[i][1] != '\0') {
            fprintf(stderr, "uso: %s [--tree] [--tokens arquivo.tok | programa]\n", argv[0]);
            return 2;
        } else {
            arquivo = argv[i];
        }
    }
    if (imprimir_arvore && !SUPORTE_ARVORE)
        fprintf(stderr, "aviso: gere o analisador com --tree para imprimir a arvore\n");

    if (tokens != NULL) {
        arquivo_tokens = fopen(tokens, "r");
        if (arquivo_tokens == NULL) {
            fprintf(stderr, "nao foi possivel abrir %s\n", tokens);
            return 2;
        }
    } else {
        if (arquivo != NULL && (entrada = fopen(arquivo, "r")) == NULL) {
            fprintf(stderr, "nao foi possivel abrir %s\n", arquivo);
            return 2;
        }
        scanner_iniciar(entrada);
        arquivo_entrada = entrada;
    }

    atexit(limpar_recursos);

    avancar();
    parse_programa();
    if (tok.tipo != TOKEN_FIM) {
        fim[0] = TOKEN_FIM;
        fim[1] = -1;
        erro_sintatico(fim);
    }
    printf("entrada aceita\n");

    return 0;
}
