/*
 * Analisador sintatico descendente recursivo gerado a partir de testes/gramaticas/json.ebnf.
 * Arquivo gerado automaticamente: nao edite.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

#define SUPORTE_ARVORE 0

/* ---- conjuntos de tokens ---- */

static const int conj_0[] = { T_STRING, T_NUMBER, T_BOOLEAN, T_NULO, T_ABRE_CHAVE, T_ABRE_COL, -1 };

/* ---- estado do analisador ---- */

static Token tok;                  /* token corrente (lookahead) */
static int imprimir_arvore = 0;    /* opcao --tree */
static int nivel_arvore = 0;
static FILE *arquivo_tokens = NULL; /* opcao --tokens */
static FILE *arquivo_entrada = NULL;

static Token token_de_arquivo(void);

/* ---- analisador lexico gerado a partir de TOKENS ---- */

static char *fonte = NULL;
static size_t pos = 0;
static int linha = 1, coluna = 1;

static char *ler_tudo(FILE *f)
{
    size_t cap = 4096, n = 0, lidos;
    char *buf = (char *) malloc(cap), *novo;
    if (buf == NULL) {
        fprintf(stderr, "memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    while ((lidos = fread(buf + n, 1, cap - n - 1, f)) > 0) {
        n += lidos;
        if (cap - n - 1 == 0) {
            cap *= 2;
            novo = (char *) realloc(buf, cap);
            if (novo == NULL) {
                fprintf(stderr, "memoria insuficiente\n");
                exit(EXIT_FAILURE);
            }
            buf = novo;
        }
    }
    buf[n] = '\0';
    return buf;
}

static void consumir(size_t n)
{
    for (; n > 0 && fonte[pos] != '\0'; n--, pos++) {
        if (fonte[pos] == '\n') {
            linha++;
            coluna = 1;
        } else {
            coluna++;
        }
    }
}

/* SKIP: [ \t\r\n]+ */
static size_t casa_skip_0(const char *s)
{
    size_t i = 0, melhor = 0;
    int estado = 0;
    static const int aceita[2] = { 0, 1 };
    if (aceita[0])
        melhor = 0;
    while (s[i] != '\0') {
        unsigned char c = (unsigned char) s[i];
        switch (estado) {
        case 0:
            if ((c >= 9 && c <= 10) || c == 13 || c == 32) {
                estado = 1;
            } else {
                goto fim;
            }
            break;
        case 1:
            if ((c >= 9 && c <= 10) || c == 13 || c == 32) {
                estado = 1;
            } else {
                goto fim;
            }
            break;
        default:
            goto fim;
        }
        i++;
        if (aceita[estado])
            melhor = i;
    }
fim:
    return melhor;
}

/* STRING: "[^"\n]*" */
static size_t casa_T_STRING(const char *s)
{
    size_t i = 0, melhor = 0;
    int estado = 0;
    static const int aceita[4] = { 0, 0, 0, 1 };
    if (aceita[0])
        melhor = 0;
    while (s[i] != '\0') {
        unsigned char c = (unsigned char) s[i];
        switch (estado) {
        case 0:
            if (c == 34) {
                estado = 1;
            } else {
                goto fim;
            }
            break;
        case 1:
            if ((c >= 1 && c <= 9) || (c >= 11 && c <= 33) || c >= 35) {
                estado = 2;
            } else if (c == 34) {
                estado = 3;
            } else {
                goto fim;
            }
            break;
        case 2:
            if ((c >= 1 && c <= 9) || (c >= 11 && c <= 33) || c >= 35) {
                estado = 2;
            } else if (c == 34) {
                estado = 3;
            } else {
                goto fim;
            }
            break;
        case 3:
            goto fim;
        default:
            goto fim;
        }
        i++;
        if (aceita[estado])
            melhor = i;
    }
fim:
    return melhor;
}

/* NUMBER: -?[0-9]+ */
static size_t casa_T_NUMBER(const char *s)
{
    size_t i = 0, melhor = 0;
    int estado = 0;
    static const int aceita[3] = { 0, 0, 1 };
    if (aceita[0])
        melhor = 0;
    while (s[i] != '\0') {
        unsigned char c = (unsigned char) s[i];
        switch (estado) {
        case 0:
            if (c == 45) {
                estado = 1;
            } else if ((c >= 48 && c <= 57)) {
                estado = 2;
            } else {
                goto fim;
            }
            break;
        case 1:
            if ((c >= 48 && c <= 57)) {
                estado = 2;
            } else {
                goto fim;
            }
            break;
        case 2:
            if ((c >= 48 && c <= 57)) {
                estado = 2;
            } else {
                goto fim;
            }
            break;
        default:
            goto fim;
        }
        i++;
        if (aceita[estado])
            melhor = i;
    }
fim:
    return melhor;
}

/* BOOLEAN: true|false */
static size_t casa_T_BOOLEAN(const char *s)
{
    size_t i = 0, melhor = 0;
    int estado = 0;
    static const int aceita[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    if (aceita[0])
        melhor = 0;
    while (s[i] != '\0') {
        unsigned char c = (unsigned char) s[i];
        switch (estado) {
        case 0:
            if (c == 102) {
                estado = 1;
            } else if (c == 116) {
                estado = 2;
            } else {
                goto fim;
            }
            break;
        case 1:
            if (c == 97) {
                estado = 3;
            } else {
                goto fim;
            }
            break;
        case 2:
            if (c == 114) {
                estado = 4;
            } else {
                goto fim;
            }
            break;
        case 3:
            if (c == 108) {
                estado = 5;
            } else {
                goto fim;
            }
            break;
        case 4:
            if (c == 117) {
                estado = 6;
            } else {
                goto fim;
            }
            break;
        case 5:
            if (c == 115) {
                estado = 7;
            } else {
                goto fim;
            }
            break;
        case 6:
            if (c == 101) {
                estado = 8;
            } else {
                goto fim;
            }
            break;
        case 7:
            if (c == 101) {
                estado = 9;
            } else {
                goto fim;
            }
            break;
        case 8:
            goto fim;
        case 9:
            goto fim;
        default:
            goto fim;
        }
        i++;
        if (aceita[estado])
            melhor = i;
    }
fim:
    return melhor;
}

/* NULO: null */
static size_t casa_T_NULO(const char *s)
{
    size_t i = 0, melhor = 0;
    int estado = 0;
    static const int aceita[5] = { 0, 0, 0, 0, 1 };
    if (aceita[0])
        melhor = 0;
    while (s[i] != '\0') {
        unsigned char c = (unsigned char) s[i];
        switch (estado) {
        case 0:
            if (c == 110) {
                estado = 1;
            } else {
                goto fim;
            }
            break;
        case 1:
            if (c == 117) {
                estado = 2;
            } else {
                goto fim;
            }
            break;
        case 2:
            if (c == 108) {
                estado = 3;
            } else {
                goto fim;
            }
            break;
        case 3:
            if (c == 108) {
                estado = 4;
            } else {
                goto fim;
            }
            break;
        case 4:
            goto fim;
        default:
            goto fim;
        }
        i++;
        if (aceita[estado])
            melhor = i;
    }
fim:
    return melhor;
}

static const char *const texto_literais[] = {
    "{",
    ",",
    "}",
    ":",
    "[",
    "]",
    NULL
};

static const int tipo_literais[] = {
    T_ABRE_CHAVE,
    T_VIRGULA,
    T_FECHA_CHAVE,
    T_DOIS_PONTOS,
    T_ABRE_COL,
    T_FECHA_COL,
    -1
};

/* Reconhece o maior prefixo da entrada; em caso de empate vence
 * o literal (palavras reservadas tem prioridade sobre ID). */
static Token proximo_token_gerado(void)
{
    Token t;
    size_t n, melhor;
    int i, tipo, pulou;

    do {
        pulou = 0;
        if ((n = casa_skip_0(fonte + pos)) > 0) {
            consumir(n);
            pulou = 1;
        }
    } while (pulou);

    memset(&t, 0, sizeof t);
    t.linha = linha;
    t.coluna = coluna;
    if (fonte[pos] == '\0') {
        t.tipo = T_FIM;
        return t;
    }
    melhor = 0;
    tipo = -1;
    for (i = 0; texto_literais[i] != NULL; i++) {
        n = strlen(texto_literais[i]);
        if (n > melhor && strncmp(fonte + pos, texto_literais[i], n) == 0) {
            melhor = n;
            tipo = tipo_literais[i];
        }
    }
    if ((n = casa_T_STRING(fonte + pos)) > melhor) {
        melhor = n;
        tipo = T_STRING;
    }
    if ((n = casa_T_NUMBER(fonte + pos)) > melhor) {
        melhor = n;
        tipo = T_NUMBER;
    }
    if ((n = casa_T_BOOLEAN(fonte + pos)) > melhor) {
        melhor = n;
        tipo = T_BOOLEAN;
    }
    if ((n = casa_T_NULO(fonte + pos)) > melhor) {
        melhor = n;
        tipo = T_NULO;
    }
    if (melhor == 0) {
        fprintf(stderr, "linha %d, coluna %d: erro lexico: caractere invalido '%c'\n",
                linha, coluna, fonte[pos]);
        exit(EXIT_FAILURE);
    }
    n = melhor < sizeof t.lexema ? melhor : sizeof t.lexema - 1;
    memcpy(t.lexema, fonte + pos, n);
    t.lexema[n] = '\0';
    t.tipo = tipo;
    consumir(melhor);
    return t;
}

static void limpar_recursos(void)
{
    if (arquivo_tokens != NULL) {
        fclose(arquivo_tokens);
        arquivo_tokens = NULL;
    } else {
        if (fonte != NULL) {
            free(fonte);
            fonte = NULL;
        }
        if (arquivo_entrada != NULL && arquivo_entrada != stdin) {
            fclose(arquivo_entrada);
            arquivo_entrada = NULL;
        }
    }
}

const char *nome_token(int tipo)
{
    switch (tipo) {
    case T_FIM: return "fim de arquivo";
    case T_STRING: return "STRING";
    case T_NUMBER: return "NUMBER";
    case T_BOOLEAN: return "BOOLEAN";
    case T_NULO: return "NULO";
    case T_ABRE_CHAVE: return "'{'";
    case T_VIRGULA: return "','";
    case T_FECHA_CHAVE: return "'}'";
    case T_DOIS_PONTOS: return "':'";
    case T_ABRE_COL: return "'['";
    case T_FECHA_COL: return "']'";
    default: return "token desconhecido";
    }
}

static void escrever_posicao(void)
{
    fprintf(stderr, "linha %d, coluna %d: ", tok.linha, tok.coluna);
}

/* Le o proximo token para tok. */
void avancar(void)
{
    if (arquivo_tokens != NULL)
        tok = token_de_arquivo();
    else
        tok = proximo_token_gerado();
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
        t.coluna = 1;
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

/* json = valor ; */
void parse_json(void)
{
    parse_valor();
}

/* valor = objeto | array | STRING | NUMBER | BOOLEAN | NULO ; */
void parse_valor(void)
{
    if (tok.tipo == T_ABRE_CHAVE) {
        parse_objeto();
    } else if (tok.tipo == T_ABRE_COL) {
        parse_array();
    } else if (tok.tipo == T_STRING) {
        match(T_STRING);
    } else if (tok.tipo == T_NUMBER) {
        match(T_NUMBER);
    } else if (tok.tipo == T_BOOLEAN) {
        match(T_BOOLEAN);
    } else if (tok.tipo == T_NULO) {
        match(T_NULO);
    } else {
        erro_sintatico(conj_0);
    }
}

/* objeto = '{' [ par { ',' par } ] '}' ; */
void parse_objeto(void)
{
    match(T_ABRE_CHAVE);
    if (tok.tipo == T_STRING) {
        parse_par();
        while (tok.tipo == T_VIRGULA) {
            match(T_VIRGULA);
            parse_par();
        }
    }
    match(T_FECHA_CHAVE);
}

/* array = '[' [ valor { ',' valor } ] ']' ; */
void parse_array(void)
{
    match(T_ABRE_COL);
    if (pertence(tok.tipo, conj_0)) {
        parse_valor();
        while (tok.tipo == T_VIRGULA) {
            match(T_VIRGULA);
            parse_valor();
        }
    }
    match(T_FECHA_COL);
}

/* par = STRING ':' valor ; */
void parse_par(void)
{
    match(T_STRING);
    match(T_DOIS_PONTOS);
    parse_valor();
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
        fonte = ler_tudo(entrada);
        arquivo_entrada = entrada;
    }

    atexit(limpar_recursos);

    avancar();
    parse_json();
    if (tok.tipo != TOKEN_FIM) {
        fim[0] = TOKEN_FIM;
        fim[1] = -1;
        erro_sintatico(fim);
    }
    printf("entrada aceita\n");

    return 0;
}
