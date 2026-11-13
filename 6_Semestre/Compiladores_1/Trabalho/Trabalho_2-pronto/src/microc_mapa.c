/*
 * microc_mapa.c - Correspondencia com os tokens de Micro C (ver microc_mapa.h).
 *
 * A tabela de literais segue o tokens.h do livro-texto (secao 2.3.1):
 *
 *   UNDEF, ID, END_OF_FILE, INTEGERCONST, CHARCONST, STRINGCONST,
 *   PLUS, MINUS, MUL, DIV, MOD, EQ, NEQ, LT, GT, LEQ, GEQ, AND, OR, NOT,
 *   ASSIGN, SEMICOLON, COMMA, LPAREN, RPAREN, LBRACE, RBRACE,
 *   LBRACKET, RBRACKET, MAIN, IF, ELSE, FOR, RETURN, INT, CHAR, PRINT
 *
 * Se o seu tokens.h do TP1 usar outros nomes, ajuste a tabela.
 *
 * Implementado: implementar microc_carregar_tokens_h.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microc_mapa.h"
#include "util.h"

static const char *const literais[][2] = {
    { "+",  "PLUS" },      { "-",  "MINUS" },     { "*",  "MUL" },
    { "/",  "DIV" },       { "%",  "MOD" },
    { "==", "EQ" },        { "!=", "NEQ" },       { "<",  "LT" },
    { ">",  "GT" },        { "<=", "LEQ" },       { ">=", "GEQ" },
    { "&&", "AND" },       { "||", "OR" },        { "!",  "NOT" },
    { "=",  "ASSIGN" },    { ";",  "SEMICOLON" }, { ",",  "COMMA" },
    { "(",  "LPAREN" },    { ")",  "RPAREN" },    { "{",  "LBRACE" },
    { "}",  "RBRACE" },    { "[",  "LBRACKET" },  { "]",  "RBRACKET" },
    { "main", "MAIN" },    { "if", "IF" },        { "else", "ELSE" },
    { "for", "FOR" },      { "return", "RETURN" },{ "int", "INT" },
    { "char", "CHAR" },    { "print", "PRINT" }
};

static char **nomes = NULL;
static int nnomes = 0, capnomes = 0;

const char *microc_nome_literal(const char *literal)
{
    size_t i;
    for (i = 0; i < sizeof(literais) / sizeof(literais[0]); i++)
        if (strcmp(literais[i][0], literal) == 0)
            return literais[i][1];
    return NULL;
}

static void adicionar_nome(const char *s, size_t n)
{
    if (nnomes == capnomes) {
        capnomes = capnomes ? 2 * capnomes : 64;
        nomes = (char **) xrealloc(nomes, (size_t) capnomes * sizeof(char *));
    }
    nomes[nnomes++] = xstrndup(s, n);
}

/* Abre o arquivo de tokens, localiza a enumeracao
 * "typedef enum { ... } TokenType;" e adiciona cada identificador a lista.
 * Ignora comentarios e valores explicitos ("X = 3"). Retorna 0 em caso de sucesso. */
int microc_carregar_tokens_h(const char *caminho)
{
    char *fonte, *p, *fim;

    if (nnomes > 0)
        return 0;

    if (caminho == NULL)
        return -1;

    fonte = ler_arquivo(caminho);
    if (fonte == NULL)
        return -1;

    p = strstr(fonte, "enum");
    if (p == NULL) {
        free(fonte);
        return -1;
    }

    p = strchr(p, '{');
    if (p == NULL) {
        free(fonte);
        return -1;
    }

    fim = strchr(p, '}');
    if (fim == NULL) {
        free(fonte);
        return -1;
    }

    p++; /* passa '{' */

    while (p < fim) {
        /* Pula espacos em branco */
        if (isspace((unsigned char) *p)) {
            p++;
            continue;
        }

        /* Pula comentarios estilo C */
        if (p[0] == '/' && p[1] == '*') {
            p += 2;
            while (p < fim && !(p[0] == '*' && p[1] == '/'))
                p++;
            if (p < fim)
                p += 2;
            continue;
        }

        /* Pula comentarios de linha: // ... */
        if (p[0] == '/' && p[1] == '/') {
            p += 2;
            while (p < fim && *p != '\n')
                p++;
            continue;
        }

        /* Identificador (nome do token) */
        if (isalpha((unsigned char) *p) || *p == '_') {
            const char *inicio = p;
            while (p < fim && (isalnum((unsigned char) *p) || *p == '_'))
                p++;
            adicionar_nome(inicio, (size_t) (p - inicio));

            /* Pula possivel valor explicito '= <valor>' antes da virgula */
            while (p < fim && *p != ',' && *p != '}') {
                if (isspace((unsigned char) *p)) {
                    p++;
                } else if (p[0] == '/' && p[1] == '*') {
                    p += 2;
                    while (p < fim && !(p[0] == '*' && p[1] == '/'))
                        p++;
                    if (p < fim)
                        p += 2;
                } else if (p[0] == '/' && p[1] == '/') {
                    p += 2;
                    while (p < fim && *p != '\n')
                        p++;
                } else {
                    p++;
                }
            }
            if (p < fim && *p == ',')
                p++;
            continue;
        }

        p++;
    }

    free(fonte);
    return 0;
}

int microc_token_existe(const char *nome)
{
    int i;
    for (i = 0; i < nnomes; i++)
        if (strcmp(nomes[i], nome) == 0)
            return 1;
    return 0;
}

void microc_liberar(void)
{
    int i;
    for (i = 0; i < nnomes; i++)
        free(nomes[i]);
    free(nomes);
    nomes = NULL;
    nnomes = capnomes = 0;
}
