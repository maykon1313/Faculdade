/*
 * codegen.c - Geracao do analisador sintatico (etapa 5).
 *
 * Estrutura do arquivo .c gerado:
 *
 *   1. includes e conjuntos constantes (conj_0, conj_1, ...)
 *   2. estado e primitivas: avancar, match, erro_sintatico, arvore
 *   3. modo proprio: analisador lexico gerado a partir de TOKENS
 *      modo Micro C: tokens obtidos de proximo_token() (scanner do TP1)
 *   4. leitura de um arquivo de tokens (opcao --tokens do analisador)
 *   5. um procedimento parse_X() por nao terminal
 *   6. main
 *
 * Fornecido: toda a estrutura acima, os nomes dos tokens, os conjuntos,
 * as primitivas, o lexico (exceto o reconhecimento das expressoes
 * regulares) e a traducao de terminais e nao terminais.
 *
 * Implementado:
 *   - gen_expr: traducao de sequencia, alternativa, [ ] e { }
 *     (esquema da secao 4 do enunciado);
 *   - gen_casamento_regex: converter uma expressao regular de TOKENS em
 *     codigo C (automato finito) que reconhece o maior prefixo;
 *   - gen_token_de_arquivo: leitura do arquivo de tokens do TP1.
 */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "microc_mapa.h"
#include "util.h"

/* ------------------------------------------------------------------ */
/* Emissao de texto                                                   */
/* ------------------------------------------------------------------ */

typedef struct {
    FILE *f;
    int nivel;          /* nivel de indentacao (4 espacos por nivel) */
} Emissor;

/* Emite uma linha indentada; fmt segue printf. */
static void emit(Emissor *em, const char *fmt, ...)
{
    int i;
    va_list ap;
    for (i = 0; i < em->nivel; i++)
        fputs("    ", em->f);
    va_start(ap, fmt);
    vfprintf(em->f, fmt, ap);
    va_end(ap);
    fputc('\n', em->f);
}

/* Emite linhas fixas, sem interpretar '%'. A lista termina em NULL. */
static void emit_linhas(FILE *f, const char *const *linhas)
{
    for (; *linhas != NULL; linhas++) {
        fputs(*linhas, f);
        fputc('\n', f);
    }
}

/* Texto dentro de comentario C: evita fechar o comentario por engano. */
static void emitir_comentario(FILE *f, const char *s)
{
    for (; *s != '\0'; s++) {
        if (s[0] == '*' && s[1] == '/') {
            fputs("* /", f);
            s++;
        } else if (*s == '\n') {
            fputc(' ', f);
        } else {
            fputc(*s, f);
        }
    }
}

/* String C entre aspas, com escapes. */
static void emitir_string_c(FILE *f, const char *s)
{
    fputc('"', f);
    for (; *s != '\0'; s++) {
        unsigned char c = (unsigned char) *s;
        if (c == '"' || c == '\\')
            fprintf(f, "\\%c", c);
        else if (c == '\n')
            fputs("\\n", f);
        else if (c == '\t')
            fputs("\\t", f);
        else if (c < 32 || c > 126)
            fprintf(f, "\\%03o", c);
        else
            fputc(c, f);
    }
    fputc('"', f);
}

/* ------------------------------------------------------------------ */
/* Nomes dos tokens no codigo gerado                                  */
/* ------------------------------------------------------------------ */

static const char *const nomes_simbolos[][2] = {
    { "+", "MAIS" }, { "-", "MENOS" }, { "*", "VEZES" }, { "/", "BARRA" },
    { "%", "PORCENTO" }, { "(", "ABRE_PAR" }, { ")", "FECHA_PAR" },
    { "[", "ABRE_COL" }, { "]", "FECHA_COL" }, { "{", "ABRE_CHAVE" },
    { "}", "FECHA_CHAVE" }, { ";", "PV" }, { ",", "VIRGULA" },
    { ".", "PONTO" }, { ":", "DOIS_PONTOS" }, { "=", "IGUAL" },
    { "==", "IGUAL_IGUAL" }, { "!=", "DIFERENTE" }, { "<", "MENOR" },
    { ">", "MAIOR" }, { "<=", "MENOR_IGUAL" }, { ">=", "MAIOR_IGUAL" },
    { "&&", "E_LOGICO" }, { "||", "OU_LOGICO" }, { "!", "NAO" },
    { ":=", "ATRIBUICAO" }, { "->", "SETA" }
};

static int eh_palavra(const char *s)
{
    if (!isalpha((unsigned char) *s) && *s != '_')
        return 0;
    for (; *s != '\0'; s++)
        if (!isalnum((unsigned char) *s) && *s != '_')
            return 0;
    return 1;
}

static int nome_em_uso(const Gramatica *g, int ate, const char *nome)
{
    int i;
    for (i = 0; i < ate; i++)
        if (strcmp(g->terms[i].nome_c, nome) == 0)
            return 1;
    return 0;
}

/* Define g->terms[i].nome_c para todos os terminais. */
static void nomear_terminais(Gramatica *g, int microc)
{
    int i;
    size_t k;
    char buf[256];
    Terminal *t;

    for (i = 0; i < g->nterms; i++) {
        t = &g->terms[i];
        free(t->nome_c);
        if (i == TERM_FIM) {
            t->nome_c = xstrdup(microc ? "END_OF_FILE" : "T_FIM");
            continue;
        }
        if (microc) {
            t->nome_c = xstrdup(t->literal ? microc_nome_literal(t->nome) : t->nome);
            continue;
        }
        buf[0] = '\0';
        if (!t->literal) {
            sprintf(buf, "T_%.200s", t->nome);
        } else if (eh_palavra(t->nome) && strlen(t->nome) < 200) {
            sprintf(buf, "T_%s", t->nome);
            for (k = 2; buf[k] != '\0'; k++)
                buf[k] = (char) toupper((unsigned char) buf[k]);
        } else {
            for (k = 0; k < sizeof(nomes_simbolos) / sizeof(nomes_simbolos[0]); k++)
                if (strcmp(nomes_simbolos[k][0], t->nome) == 0)
                    sprintf(buf, "T_%s", nomes_simbolos[k][1]);
            if (buf[0] == '\0')
                sprintf(buf, "T_LIT_%d", i);
        }
        if (nome_em_uso(g, i, buf))
            sprintf(buf + strlen(buf), "_%d", i);
        t->nome_c = xstrdup(buf);
    }
}

/* ------------------------------------------------------------------ */
/* Conjuntos constantes                                               */
/* ------------------------------------------------------------------ */

#define MAX_COMPARACOES 3   /* ate 3 tokens: tok.tipo == A || ...; acima: pertence */

static Bitset *conjuntos = NULL;
static int nconj = 0, capconj = 0;

static int bitset_igual(const Bitset *a, const Bitset *b)
{
    int i;
    for (i = 0; i < a->n; i++)
        if (bitset_tem(a, i) != bitset_tem(b, i))
            return 0;
    return 1;
}

/* Registra um conjunto e devolve seu numero N (emitido como conj_N).
 * Conjuntos iguais compartilham a mesma constante. */
static int registrar_conjunto(const Bitset *b)
{
    int i;
    for (i = 0; i < nconj; i++)
        if (bitset_igual(&conjuntos[i], b))
            return i;
    if (nconj == capconj) {
        capconj = capconj ? 2 * capconj : 16;
        conjuntos = (Bitset *) xrealloc(conjuntos, (size_t) capconj * sizeof(Bitset));
    }
    bitset_iniciar(&conjuntos[nconj], b->n);
    bitset_copiar(&conjuntos[nconj], b);
    return nconj++;
}

static void liberar_conjuntos(void)
{
    int i;
    for (i = 0; i < nconj; i++)
        bitset_liberar(&conjuntos[i]);
    free(conjuntos);
    conjuntos = NULL;
    nconj = capconj = 0;
}

static void emitir_conjuntos(FILE *f, const Gramatica *g)
{
    int i, t;
    for (i = 0; i < nconj; i++) {
        fprintf(f, "static const int conj_%d[] = { ", i);
        for (t = bitset_proximo(&conjuntos[i], 0); t >= 0;
             t = bitset_proximo(&conjuntos[i], t + 1))
            fprintf(f, "%s, ", g->terms[t].nome_c);
        fputs("-1 };\n", f);
    }
}

/* Escreve a condicao "o token corrente pertence a b":
 *   tok.tipo == T_A                     (um token)
 *   tok.tipo == T_A || tok.tipo == T_B  (ate MAX_COMPARACOES)
 *   pertence(tok.tipo, conj_N)          (mais tokens) */
static void emitir_teste(FILE *f, const Gramatica *g, const Bitset *b)
{
    int t, n = bitset_tamanho(b), primeiro = 1;
    if (n == 0) {
        fputs("0", f);
    } else if (n <= MAX_COMPARACOES) {
        for (t = bitset_proximo(b, 0); t >= 0; t = bitset_proximo(b, t + 1)) {
            fprintf(f, "%stok.tipo == %s", primeiro ? "" : " || ", g->terms[t].nome_c);
            primeiro = 0;
        }
    } else {
        fprintf(f, "pertence(tok.tipo, conj_%d)", registrar_conjunto(b));
    }
}

/* Linha "<antes><teste><depois>", ex.: emit_teste(em, "while (", g, b, ") {") */
static void emit_teste(Emissor *em, const char *antes, const Gramatica *g,
                       const Bitset *b, const char *depois)
{
    int i;
    for (i = 0; i < em->nivel; i++)
        fputs("    ", em->f);
    fputs(antes, em->f);
    emitir_teste(em->f, g, b);
    fputs(depois, em->f);
    fputc('\n', em->f);
}

/* Linha "erro_sintatico(conj_N);" com N = conjunto dos tokens esperados. */
static void emit_erro(Emissor *em, const Bitset *esperados)
{
    emit(em, "erro_sintatico(conj_%d);", registrar_conjunto(esperados));
}

/* ------------------------------------------------------------------ */
/* Traducao das expressoes (esquema da secao 4 do enunciado)          */
/* ------------------------------------------------------------------ */

static void gen_expr(Emissor *em, const Gramatica *g, const Expr *e)
{
    if (e == NULL)
        return;

    switch (e->tipo) {
    case E_TERM:
        emit(em, "match(%s);", g->terms[e->simbolo].nome_c);
        break;
    case E_NAOTERM:
        emit(em, "parse_%s();", g->nts[e->simbolo].nome);
        break;
    case E_VAZIO:
        break;
    case E_SEQ: {
        int i;
        for (i = 0; i < e->nfilhos; i++)
            gen_expr(em, g, e->filhos[i]);
        break;
    }
    case E_OPC:
        if (e->nfilhos > 0) {
            emit_teste(em, "if (", g, &e->filhos[0]->first, ") {");
            em->nivel++;
            gen_expr(em, g, e->filhos[0]);
            em->nivel--;
            emit(em, "}");
        }
        break;
    case E_REP:
        if (e->nfilhos > 0) {
            emit_teste(em, "while (", g, &e->filhos[0]->first, ") {");
            em->nivel++;
            gen_expr(em, g, e->filhos[0]);
            em->nivel--;
            emit(em, "}");
        }
        break;
    case E_ALT: {
        int i, primeiro = 1, idx_anulavel = -1;
        for (i = 0; i < e->nfilhos; i++) {
            if (e->filhos[i]->anulavel) {
                idx_anulavel = i;
                break;
            }
        }
        for (i = 0; i < e->nfilhos; i++) {
            if (i == idx_anulavel)
                continue;
            if (primeiro) {
                emit_teste(em, "if (", g, &e->filhos[i]->first, ") {");
                primeiro = 0;
            } else {
                emit_teste(em, "} else if (", g, &e->filhos[i]->first, ") {");
            }
            em->nivel++;
            gen_expr(em, g, e->filhos[i]);
            em->nivel--;
        }
        if (idx_anulavel >= 0) {
            if (!primeiro) {
                emit(em, "} else {");
                em->nivel++;
                gen_expr(em, g, e->filhos[idx_anulavel]);
                em->nivel--;
                emit(em, "}");
            } else {
                gen_expr(em, g, e->filhos[idx_anulavel]);
            }
        } else {
            if (!primeiro) {
                emit(em, "} else {");
                em->nivel++;
                emit_erro(em, &e->first);
                em->nivel--;
                emit(em, "}");
            } else {
                emit_erro(em, &e->first);
            }
        }
        break;
    }
    }
}

/* ------------------------------------------------------------------ */
/* Expressoes regulares de TOKENS (modo proprio)                      */
/* ------------------------------------------------------------------ */

#define MAX_NFA_STATES 512
#define MAX_DFA_STATES 128

typedef struct {
    int trans_tipo; /* 0 = CHAR, 1 = EPSILON */
    int out1;
    int out2;
    unsigned char match[256];
} NFAEstado;

typedef struct {
    int start;
    int accept;
} Frag;

typedef struct {
    NFAEstado estados[MAX_NFA_STATES];
    int nestados;
    int erro;
} NFABuilder;

typedef struct {
    unsigned char nfa_set[64];
    int trans[256];
    int aceita;
} DFAEstado;

static void set_add(unsigned char *set, int s)
{
    set[s / 8] |= (unsigned char) (1 << (s % 8));
}

static int set_has(const unsigned char *set, int s)
{
    return (set[s / 8] & (1 << (s % 8))) != 0;
}

static int nfa_novo_estado(NFABuilder *b, int tipo)
{
    int s;
    if (b->nestados >= MAX_NFA_STATES) {
        b->erro = 1;
        return 0;
    }
    s = b->nestados++;
    b->estados[s].trans_tipo = tipo;
    b->estados[s].out1 = -1;
    b->estados[s].out2 = -1;
    memset(b->estados[s].match, 0, 256);
    return s;
}

static Frag nfa_char(NFABuilder *b, const unsigned char *match)
{
    Frag f;
    f.start = nfa_novo_estado(b, 0);
    f.accept = nfa_novo_estado(b, 1);
    memcpy(b->estados[f.start].match, match, 256);
    b->estados[f.start].out1 = f.accept;
    return f;
}

static Frag nfa_concat(NFABuilder *b, Frag f1, Frag f2)
{
    Frag f;
    b->estados[f1.accept].out1 = f2.start;
    f.start = f1.start;
    f.accept = f2.accept;
    return f;
}

static Frag nfa_alt(NFABuilder *b, Frag f1, Frag f2)
{
    Frag f;
    f.start = nfa_novo_estado(b, 1);
    f.accept = nfa_novo_estado(b, 1);
    b->estados[f.start].out1 = f1.start;
    b->estados[f.start].out2 = f2.start;
    b->estados[f1.accept].out1 = f.accept;
    b->estados[f2.accept].out1 = f.accept;
    return f;
}

static Frag nfa_star(NFABuilder *b, Frag f1)
{
    Frag f;
    f.start = nfa_novo_estado(b, 1);
    f.accept = nfa_novo_estado(b, 1);
    b->estados[f.start].out1 = f1.start;
    b->estados[f.start].out2 = f.accept;
    b->estados[f1.accept].out1 = f1.start;
    b->estados[f1.accept].out2 = f.accept;
    return f;
}

static Frag nfa_plus(NFABuilder *b, Frag f1)
{
    Frag f;
    f.start = nfa_novo_estado(b, 1);
    f.accept = nfa_novo_estado(b, 1);
    b->estados[f.start].out1 = f1.start;
    b->estados[f1.accept].out1 = f1.start;
    b->estados[f1.accept].out2 = f.accept;
    return f;
}

static Frag nfa_opt(NFABuilder *b, Frag f1)
{
    Frag f;
    f.start = nfa_novo_estado(b, 1);
    f.accept = nfa_novo_estado(b, 1);
    b->estados[f.start].out1 = f1.start;
    b->estados[f.start].out2 = f.accept;
    b->estados[f1.accept].out1 = f.accept;
    return f;
}

static int parse_escape(const char **ps)
{
    char c = **ps;
    if (c == '\0')
        return '\\';
    (*ps)++;
    switch (c) {
    case 'n': return '\n';
    case 't': return '\t';
    case 'r': return '\r';
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'v': return '\v';
    case '0': return '\0';
    default:  return (unsigned char) c;
    }
}

static void parse_class(const char **ps, unsigned char *match, int *erro)
{
    int neg = 0;
    memset(match, 0, 256);
    if (**ps == '^') {
        neg = 1;
        (*ps)++;
    }
    while (**ps != ']' && **ps != '\0') {
        int c1;
        if (**ps == '\\') {
            (*ps)++;
            c1 = parse_escape(ps);
        } else {
            c1 = (unsigned char) **ps;
            (*ps)++;
        }
        if (**ps == '-' && *(*ps + 1) != ']' && *(*ps + 1) != '\0') {
            int c2, k;
            (*ps)++; /* consome '-' */
            if (**ps == '\\') {
                (*ps)++;
                c2 = parse_escape(ps);
            } else {
                c2 = (unsigned char) **ps;
                (*ps)++;
            }
            if (c1 <= c2) {
                for (k = c1; k <= c2; k++)
                    match[k] = 1;
            } else {
                for (k = c2; k <= c1; k++)
                    match[k] = 1;
            }
        } else {
            match[c1] = 1;
        }
    }
    if (**ps == ']') {
        (*ps)++;
    } else {
        *erro = 1;
    }
    if (neg) {
        int k;
        for (k = 1; k < 256; k++)
            match[k] = (unsigned char) (!match[k]);
        match[0] = 0;
    }
}

static Frag parse_regex_expr(NFABuilder *b, const char **ps);

static Frag parse_base(NFABuilder *b, const char **ps)
{
    unsigned char m[256];
    Frag f;
    memset(&f, 0, sizeof(f));

    if (**ps == '(') {
        (*ps)++;
        f = parse_regex_expr(b, ps);
        if (**ps == ')')
            (*ps)++;
        else
            b->erro = 1;
        return f;
    }
    if (**ps == '.') {
        (*ps)++;
        memset(m, 1, 256);
        m[0] = 0;
        m['\n'] = 0;
        return nfa_char(b, m);
    }
    if (**ps == '[') {
        (*ps)++;
        parse_class(ps, m, &b->erro);
        return nfa_char(b, m);
    }
    if (**ps == '\\') {
        int c;
        (*ps)++;
        c = parse_escape(ps);
        memset(m, 0, 256);
        m[c] = 1;
        return nfa_char(b, m);
    }
    if (**ps != '\0' && **ps != '|' && **ps != ')' && **ps != '*' && **ps != '+' && **ps != '?') {
        int c = (unsigned char) **ps;
        (*ps)++;
        memset(m, 0, 256);
        m[c] = 1;
        return nfa_char(b, m);
    }
    b->erro = 1;
    return f;
}

static Frag parse_factor(NFABuilder *b, const char **ps)
{
    Frag f = parse_base(b, ps);
    if (b->erro)
        return f;
    while (**ps == '*' || **ps == '+' || **ps == '?') {
        char op = **ps;
        (*ps)++;
        if (op == '*')
            f = nfa_star(b, f);
        else if (op == '+')
            f = nfa_plus(b, f);
        else if (op == '?')
            f = nfa_opt(b, f);
    }
    return f;
}

static Frag parse_term(NFABuilder *b, const char **ps)
{
    Frag f;
    int primeiro = 1;
    memset(&f, 0, sizeof(f));

    while (**ps != '\0' && **ps != '|' && **ps != ')') {
        Frag f2 = parse_factor(b, ps);
        if (b->erro)
            return f;
        if (primeiro) {
            f = f2;
            primeiro = 0;
        } else {
            f = nfa_concat(b, f, f2);
        }
    }
    if (primeiro) {
        f.start = nfa_novo_estado(b, 1);
        f.accept = nfa_novo_estado(b, 1);
        b->estados[f.start].out1 = f.accept;
    }
    return f;
}

static Frag parse_regex_expr(NFABuilder *b, const char **ps)
{
    Frag f = parse_term(b, ps);
    if (b->erro)
        return f;
    while (**ps == '|') {
        Frag f2;
        (*ps)++;
        f2 = parse_term(b, ps);
        if (b->erro)
            return f;
        f = nfa_alt(b, f, f2);
    }
    return f;
}

static void epsilon_closure(NFABuilder *b, unsigned char *set)
{
    int pilha[MAX_NFA_STATES], topo = 0, i;
    for (i = 0; i < b->nestados; i++) {
        if (set_has(set, i))
            pilha[topo++] = i;
    }
    while (topo > 0) {
        int u = pilha[--topo];
        if (b->estados[u].trans_tipo == 1) {
            int v1 = b->estados[u].out1;
            int v2 = b->estados[u].out2;
            if (v1 >= 0 && v1 < b->nestados && !set_has(set, v1)) {
                set_add(set, v1);
                pilha[topo++] = v1;
            }
            if (v2 >= 0 && v2 < b->nestados && !set_has(set, v2)) {
                set_add(set, v2);
                pilha[topo++] = v2;
            }
        }
    }
}

static void emitir_condicao_faixas(FILE *f, const unsigned char *match)
{
    int c, r_start = -1, primeiro = 1;
    for (c = 1; c <= 256; c++) {
        if (c < 256 && match[c]) {
            if (r_start < 0)
                r_start = c;
        } else {
            if (r_start >= 0) {
                int r_end = c - 1;
                if (!primeiro)
                    fputs(" || ", f);
                if (r_start == r_end) {
                    fprintf(f, "c == %d", r_start);
                } else if (r_end == 255) {
                    if (r_start == 0)
                        fputs("1", f);
                    else
                        fprintf(f, "c >= %d", r_start);
                } else if (r_start == 0) {
                    fprintf(f, "c <= %d", r_end);
                } else {
                    fprintf(f, "(c >= %d && c <= %d)", r_start, r_end);
                }
                primeiro = 0;
                r_start = -1;
            }
        }
    }
}

/* Emite a funcao
 *     static size_t <nome>(const char *s)
 * que devolve o comprimento do MAIOR prefixo de s reconhecido pela
 * expressao regular, ou 0 se nenhum prefixo for reconhecido.
 * Retorna 0 se a expressao for valida (senao reporte com diag_erro). */
static int gen_casamento_regex(FILE *f, const char *nome, const char *regex)
{
    NFABuilder b;
    Frag frag;
    const char *p;
    DFAEstado dfa[MAX_DFA_STATES];
    int ndfa = 0, i, c, u, k;

    if (regex == NULL || *regex == '\0') {
        fprintf(f, "static size_t %s(const char *s)\n{\n    (void) s;\n    return 0;\n}\n\n", nome);
        return 0;
    }

    memset(&b, 0, sizeof(b));
    p = regex;
    frag = parse_regex_expr(&b, &p);
    if (b.erro || *p != '\0') {
        diag_erro(0, 0, "expressao regular invalida '%s'", regex);
        return -1;
    }

    /* Constroi o DFA a partir do NFA */
    memset(&dfa[0], 0, sizeof(DFAEstado));
    set_add(dfa[0].nfa_set, frag.start);
    epsilon_closure(&b, dfa[0].nfa_set);
    dfa[0].aceita = set_has(dfa[0].nfa_set, frag.accept);
    for (c = 0; c < 256; c++)
        dfa[0].trans[c] = -1;
    ndfa = 1;

    for (i = 0; i < ndfa; i++) {
        for (c = 1; c < 256; c++) {
            unsigned char dest_set[64];
            int has_any = 0, d;
            memset(dest_set, 0, sizeof(dest_set));

            for (u = 0; u < b.nestados; u++) {
                if (set_has(dfa[i].nfa_set, u)) {
                    if (b.estados[u].trans_tipo == 0 && b.estados[u].match[c]) {
                        int v = b.estados[u].out1;
                        if (v >= 0) {
                            set_add(dest_set, v);
                            has_any = 1;
                        }
                    }
                }
            }
            if (!has_any) {
                dfa[i].trans[c] = -1;
                continue;
            }
            epsilon_closure(&b, dest_set);
            d = -1;
            for (k = 0; k < ndfa; k++) {
                if (memcmp(dfa[k].nfa_set, dest_set, sizeof(dest_set)) == 0) {
                    d = k;
                    break;
                }
            }
            if (d < 0) {
                if (ndfa >= MAX_DFA_STATES) {
                    diag_erro(0, 0, "automato da expressao regular '%s' excedeu o limite de estados", regex);
                    return -1;
                }
                d = ndfa++;
                memset(&dfa[d], 0, sizeof(DFAEstado));
                memcpy(dfa[d].nfa_set, dest_set, sizeof(dest_set));
                dfa[d].aceita = set_has(dfa[d].nfa_set, frag.accept);
                for (k = 0; k < 256; k++)
                    dfa[d].trans[k] = -1;
            }
            dfa[i].trans[c] = d;
        }
    }

    /* Emissao da funcao em codigo C */
    fprintf(f, "static size_t %s(const char *s)\n{\n", nome);
    fprintf(f, "    size_t i = 0, melhor = 0;\n");
    fprintf(f, "    int estado = 0;\n");
    fprintf(f, "    static const int aceita[%d] = {", ndfa);
    for (i = 0; i < ndfa; i++)
        fprintf(f, "%s%d", i > 0 ? ", " : " ", dfa[i].aceita);
    fprintf(f, " };\n");
    fprintf(f, "    if (aceita[0])\n        melhor = 0;\n");
    fprintf(f, "    while (s[i] != '\\0') {\n");
    fprintf(f, "        unsigned char c = (unsigned char) s[i];\n");
    fprintf(f, "        switch (estado) {\n");

    for (i = 0; i < ndfa; i++) {
        int alvos[MAX_DFA_STATES], nalvos = 0;
        for (c = 1; c < 256; c++) {
            int t = dfa[i].trans[c];
            if (t >= 0) {
                int ja = 0;
                for (k = 0; k < nalvos; k++) {
                    if (alvos[k] == t) { ja = 1; break; }
                }
                if (!ja)
                    alvos[nalvos++] = t;
            }
        }
        if (nalvos == 0) {
            fprintf(f, "        case %d:\n            goto fim;\n", i);
        } else {
            fprintf(f, "        case %d:\n", i);
            for (k = 0; k < nalvos; k++) {
                int target = alvos[k];
                unsigned char match_alvo[256];
                memset(match_alvo, 0, 256);
                for (c = 1; c < 256; c++) {
                    if (dfa[i].trans[c] == target)
                        match_alvo[c] = 1;
                }
                if (k == 0)
                    fputs("            if (", f);
                else
                    fputs(" else if (", f);
                emitir_condicao_faixas(f, match_alvo);
                fprintf(f, ") {\n                estado = %d;\n            }", target);
            }
            fputs(" else {\n                goto fim;\n            }\n            break;\n", f);
        }
    }

    fprintf(f, "        default:\n            goto fim;\n        }\n");
    fprintf(f, "        i++;\n");
    fprintf(f, "        if (aceita[estado])\n            melhor = i;\n");
    fprintf(f, "    }\nfim:\n    return melhor;\n}\n\n");

    return 0;
}

/* ------------------------------------------------------------------ */
/* Leitura do arquivo de tokens (opcao --tokens do analisador gerado) */
/* ------------------------------------------------------------------ */

/* Emite "static Token token_de_arquivo(void)", que le o proximo token
 * do arquivo aberto em arquivo_tokens, no formato gravado pelo lexer do
 * TP1 (livro-texto, secao 3.3.2):
 *
 *   Token: tipo = <numero>, lexema = '<texto>', linha = <numero>
 *
 * Ao chegar ao fim do arquivo devolve um token TOKEN_FIM. */
static void gen_token_de_arquivo(FILE *f, int microc)
{
    static const char *const linhas_antes[] = {
        "static int linha_arq_tokens = 0;",
        "",
        "static Token token_de_arquivo(void)",
        "{",
        "    char buf[1024];",
        "    Token t;",
        "    memset(&t, 0, sizeof t);",
        "    while (fgets(buf, sizeof buf, arquivo_tokens) != NULL) {",
        "        char *p = buf, *lex_inicio, *lex_fim, *lin_str;",
        "        int tipo_val, linha_val;",
        "        linha_arq_tokens++;",
        "        while (*p == ' ' || *p == '\\t' || *p == '\\r' || *p == '\\n') p++;",
        "        if (*p == '\\0') continue;",
        "        if (strncmp(p, \"Token:\", 6) != 0) goto malformado;",
        "        p = strstr(p + 6, \"tipo =\");",
        "        if (p == NULL) goto malformado;",
        "        if (sscanf(p + 6, \"%d\", &tipo_val) != 1) goto malformado;",
        "        p = strstr(p, \"lexema = '\");",
        "        if (p == NULL) goto malformado;",
        "        lex_inicio = p + 10;",
        "        lin_str = strstr(lex_inicio, \"', linha =\");",
        "        if (lin_str == NULL) goto malformado;",
        "        lex_fim = lin_str;",
        "        if (sscanf(lin_str + 10, \"%d\", &linha_val) != 1) goto malformado;",
        "        t.tipo = tipo_val;",
        "        t.linha = linha_val;",
        NULL
    };
    static const char *const linhas_depois[] = {
        "        {",
        "            size_t tam = (size_t)(lex_fim - lex_inicio);",
        "            if (tam >= sizeof t.lexema) tam = sizeof t.lexema - 1;",
        "            memcpy(t.lexema, lex_inicio, tam);",
        "            t.lexema[tam] = '\\0';",
        "        }",
        "        return t;",
        "    malformado:",
        "        fprintf(stderr, \"linha %d do arquivo de tokens malformada\\n\", linha_arq_tokens);",
        "        exit(EXIT_FAILURE);",
        "    }",
        "    t.tipo = TOKEN_FIM;",
        "    return t;",
        "}",
        "",
        NULL
    };
    emit_linhas(f, linhas_antes);
    if (!microc)
        fputs("        t.coluna = 1;\n", f);
    emit_linhas(f, linhas_depois);
}

/* ------------------------------------------------------------------ */
/* Partes fixas do codigo gerado                                      */
/* ------------------------------------------------------------------ */

static const char *const rt_estado[] = {
    "/* ---- estado do analisador ---- */",
    "",
    "static Token tok;                  /* token corrente (lookahead) */",
    "static int imprimir_arvore = 0;    /* opcao --tree */",
    "static int nivel_arvore = 0;",
    "static FILE *arquivo_tokens = NULL; /* opcao --tokens */",
    "static FILE *arquivo_entrada = NULL;",
    "",
    "static Token token_de_arquivo(void);",
    "",
    NULL
};

static const char *const rt_primitivas[] = {
    "/* ---- primitivas ---- */",
    "",
    "int pertence(int tipo, const int *conjunto)",
    "{",
    "    for (; *conjunto != -1; conjunto++)",
    "        if (*conjunto == tipo)",
    "            return 1;",
    "    return 0;",
    "}",
    "",
    "/* Reporta o erro com os tokens esperados (lista terminada em -1) e encerra. */",
    "void erro_sintatico(const int *esperados)",
    "{",
    "    int i;",
    "    escrever_posicao();",
    "    if ((int) tok.tipo == TOKEN_FIM)",
    "        fprintf(stderr, \"encontrado fim de arquivo, \");",
    "    else",
    "        fprintf(stderr, \"encontrado '%s', \", tok.lexema);",
    "    if (esperados[0] != -1 && esperados[1] == -1) {",
    "        fprintf(stderr, \"esperado %s\\n\", nome_token(esperados[0]));",
    "    } else {",
    "        fprintf(stderr, \"esperado um de {\");",
    "        for (i = 0; esperados[i] != -1; i++)",
    "            fprintf(stderr, \"%s%s\", i > 0 ? \", \" : \"\", nome_token(esperados[i]));",
    "        fprintf(stderr, \"}\\n\");",
    "    }",
    "    exit(EXIT_FAILURE);",
    "}",
    "",
    "static void recuo(void)",
    "{",
    "    int i;",
    "    for (i = 0; i < nivel_arvore; i++)",
    "        fputs(\"  \", stdout);",
    "}",
    "",
    "void arvore_entra(const char *nao_terminal)",
    "{",
    "    if (imprimir_arvore) {",
    "        recuo();",
    "        printf(\"%s\\n\", nao_terminal);",
    "    }",
    "    nivel_arvore++;",
    "}",
    "",
    "void arvore_sai(void)",
    "{",
    "    nivel_arvore--;",
    "}",
    "",
    "/* Consome o token corrente se for do tipo esperado; senao, erro. */",
    "void match(int esperado)",
    "{",
    "    int lista[2];",
    "    if ((int) tok.tipo != esperado) {",
    "        lista[0] = esperado;",
    "        lista[1] = -1;",
    "        erro_sintatico(lista);",
    "    }",
    "    if (SUPORTE_ARVORE && imprimir_arvore) {",
    "        recuo();",
    "        if (nome_token(tok.tipo)[0] == '\\'')",
    "            printf(\"%s\\n\", nome_token(tok.tipo));",
    "        else",
    "            printf(\"%s '%s'\\n\", nome_token(tok.tipo), tok.lexema);",
    "    }",
    "    avancar();",
    "}",
    "",
    NULL
};

/* Lexico proprio: partes fixas antes e depois das funcoes de regex. */
static const char *const rt_lexico_estado[] = {
    "/* ---- analisador lexico gerado a partir de TOKENS ---- */",
    "",
    "static char *fonte = NULL;",
    "static size_t pos = 0;",
    "static int linha = 1, coluna = 1;",
    "",
    "static char *ler_tudo(FILE *f)",
    "{",
    "    size_t cap = 4096, n = 0, lidos;",
    "    char *buf = (char *) malloc(cap), *novo;",
    "    if (buf == NULL) {",
    "        fprintf(stderr, \"memoria insuficiente\\n\");",
    "        exit(EXIT_FAILURE);",
    "    }",
    "    while ((lidos = fread(buf + n, 1, cap - n - 1, f)) > 0) {",
    "        n += lidos;",
    "        if (cap - n - 1 == 0) {",
    "            cap *= 2;",
    "            novo = (char *) realloc(buf, cap);",
    "            if (novo == NULL) {",
    "                fprintf(stderr, \"memoria insuficiente\\n\");",
    "                exit(EXIT_FAILURE);",
    "            }",
    "            buf = novo;",
    "        }",
    "    }",
    "    buf[n] = '\\0';",
    "    return buf;",
    "}",
    "",
    "static void consumir(size_t n)",
    "{",
    "    for (; n > 0 && fonte[pos] != '\\0'; n--, pos++) {",
    "        if (fonte[pos] == '\\n') {",
    "            linha++;",
    "            coluna = 1;",
    "        } else {",
    "            coluna++;",
    "        }",
    "    }",
    "}",
    "",
    NULL
};

static void escrever_cabecalho_c(FILE *f, const OpcoesGeracao *op)
{
    fputs("/*\n * Analisador sintatico descendente recursivo gerado a partir de ", f);
    emitir_comentario(f, op->origem);
    fputs(".\n * Arquivo gerado automaticamente: nao edite.\n */\n", f);
}

/* ------------------------------------------------------------------ */
/* Arquivo .h                                                         */
/* ------------------------------------------------------------------ */

static int gerar_h(const Gramatica *g, const OpcoesGeracao *op)
{
    char *caminho = (char *) xmalloc(strlen(op->prefixo) + 3);
    FILE *f;
    int i;

    sprintf(caminho, "%s.h", op->prefixo);
    f = fopen(caminho, "w");
    if (f == NULL) {
        diag_erro(0, 0, "nao foi possivel criar %s", caminho);
        free(caminho);
        return -1;
    }
    escrever_cabecalho_c(f, op);
    fputs("#ifndef PARSER_GERADO_H\n#define PARSER_GERADO_H\n\n", f);
    if (op->microc) {
        fputs("#include \"scanner.h\"   /* scanner do TP1: Token, TokenType, proximo_token */\n\n", f);
        fputs("#define TOKEN_FIM END_OF_FILE\n\n", f);
    } else {
        fputs("typedef enum {\n", f);
        for (i = 0; i < g->nterms; i++) {
            fprintf(f, "    %s%s   /* ", g->terms[i].nome_c, i + 1 < g->nterms ? "," : "");
            emitir_comentario(f, g->terms[i].exibicao);
            fputs(" */\n", f);
        }
        fputs("} TipoToken;\n\n", f);
        fputs("typedef struct {\n    int tipo;\n    char lexema[100];\n"
              "    int linha;\n    int coluna;\n} Token;\n\n", f);
        fputs("#define TOKEN_FIM T_FIM\n\n", f);
    }
    fputs("const char *nome_token(int tipo);\n", f);
    fputs("int  pertence(int tipo, const int *conjunto);\n", f);
    fputs("void avancar(void);\n", f);
    fputs("void match(int esperado);\n", f);
    fputs("void erro_sintatico(const int *esperados);\n", f);
    fputs("void arvore_entra(const char *nao_terminal);\n", f);
    fputs("void arvore_sai(void);\n\n", f);
    for (i = 0; i < g->nnts; i++)
        if (g->nts[i].regra != NULL)
            fprintf(f, "void parse_%s(void);\n", g->nts[i].nome);
    fputs("\n#endif\n", f);
    fclose(f);
    free(caminho);
    return 0;
}

/* ------------------------------------------------------------------ */
/* Arquivo .c                                                         */
/* ------------------------------------------------------------------ */

static void gerar_nome_token(FILE *f, const Gramatica *g)
{
    int i;
    fputs("const char *nome_token(int tipo)\n{\n    switch (tipo) {\n", f);
    for (i = 0; i < g->nterms; i++) {
        fprintf(f, "    case %s: return ", g->terms[i].nome_c);
        emitir_string_c(f, i == TERM_FIM ? "fim de arquivo" : g->terms[i].exibicao);
        fputs(";\n", f);
    }
    fputs("    default: return \"token desconhecido\";\n    }\n}\n\n", f);
}

static void gerar_limpar_recursos(FILE *f, int microc)
{
    fputs("static void limpar_recursos(void)\n{\n", f);
    fputs("    if (arquivo_tokens != NULL) {\n", f);
    fputs("        fclose(arquivo_tokens);\n", f);
    fputs("        arquivo_tokens = NULL;\n", f);
    fputs("    } else {\n", f);
    if (microc)
        fputs("        scanner_finalizar();\n", f);
    else
        fputs("        if (fonte != NULL) {\n            free(fonte);\n            fonte = NULL;\n        }\n", f);
    fputs("        if (arquivo_entrada != NULL && arquivo_entrada != stdin) {\n", f);
    fputs("            fclose(arquivo_entrada);\n", f);
    fputs("            arquivo_entrada = NULL;\n", f);
    fputs("        }\n", f);
    fputs("    }\n}\n\n", f);
}

static void gerar_posicao_e_avancar(FILE *f, int microc)
{
    fputs("static void escrever_posicao(void)\n{\n", f);
    if (microc)
        fputs("    fprintf(stderr, \"linha %d: \", tok.linha);\n", f);
    else
        fputs("    fprintf(stderr, \"linha %d, coluna %d: \", tok.linha, tok.coluna);\n", f);
    fputs("}\n\n", f);

    fputs("/* Le o proximo token para tok. */\nvoid avancar(void)\n{\n", f);
    fputs("    if (arquivo_tokens != NULL)\n        tok = token_de_arquivo();\n    else\n", f);
    if (microc) {
        fputs("        tok = proximo_token();\n", f);
        fputs("    if (tok.tipo == UNDEF) {\n", f);
        fputs("        fprintf(stderr, \"linha %d: erro lexico: %s\\n\", tok.linha, tok.lexema);\n", f);
        fputs("        exit(EXIT_FAILURE);\n    }\n", f);
    } else {
        fputs("        tok = proximo_token_gerado();\n", f);
    }
    fputs("}\n\n", f);
}

static int gerar_lexico(FILE *f, const Gramatica *g)
{
    int i, nlit = 0, erros = 0;
    char nome[300];

    emit_linhas(f, rt_lexico_estado);

    for (i = 0; i < g->nskips; i++) {
        sprintf(nome, "casa_skip_%d", i);
        fputs("/* SKIP: ", f);
        emitir_comentario(f, g->skips[i]);
        fputs(" */\n", f);
        if (gen_casamento_regex(f, nome, g->skips[i]) != 0)
            erros++;
    }
    for (i = 1; i < g->nterms; i++) {
        if (g->terms[i].literal) {
            nlit++;
            continue;
        }
        sprintf(nome, "casa_%.250s", g->terms[i].nome_c);
        fprintf(f, "/* %s: ", g->terms[i].nome);
        emitir_comentario(f, g->terms[i].regex ? g->terms[i].regex : "");
        fputs(" */\n", f);
        if (gen_casamento_regex(f, nome, g->terms[i].regex ? g->terms[i].regex : "")
            != 0)
            erros++;
    }

    /* literais: comparacao direta, com prioridade em caso de empate */
    fputs("static const char *const texto_literais[] = {\n", f);
    for (i = 1; i < g->nterms; i++)
        if (g->terms[i].literal) {
            fputs("    ", f);
            emitir_string_c(f, g->terms[i].nome);
            fputs(",\n", f);
        }
    fputs("    NULL\n};\n\nstatic const int tipo_literais[] = {\n", f);
    for (i = 1; i < g->nterms; i++)
        if (g->terms[i].literal)
            fprintf(f, "    %s,\n", g->terms[i].nome_c);
    fputs("    -1\n};\n\n", f);

    fputs("/* Reconhece o maior prefixo da entrada; em caso de empate vence\n"
          " * o literal (palavras reservadas tem prioridade sobre ID). */\n", f);
    fputs("static Token proximo_token_gerado(void)\n{\n", f);
    fputs("    Token t;\n    size_t n, melhor;\n    int i, tipo, pulou;\n\n", f);
    fputs("    do {\n        pulou = 0;\n", f);
    for (i = 0; i < g->nskips; i++)
        fprintf(f, "        if ((n = casa_skip_%d(fonte + pos)) > 0) {\n"
                   "            consumir(n);\n            pulou = 1;\n        }\n", i);
    fputs("    } while (pulou);\n\n", f);
    fputs("    memset(&t, 0, sizeof t);\n", f);
    fputs("    t.linha = linha;\n    t.coluna = coluna;\n", f);
    fputs("    if (fonte[pos] == '\\0') {\n        t.tipo = T_FIM;\n        return t;\n    }\n", f);
    fputs("    melhor = 0;\n    tipo = -1;\n", f);
    fputs("    for (i = 0; texto_literais[i] != NULL; i++) {\n", f);
    fputs("        n = strlen(texto_literais[i]);\n", f);
    fputs("        if (n > melhor && strncmp(fonte + pos, texto_literais[i], n) == 0) {\n", f);
    fputs("            melhor = n;\n            tipo = tipo_literais[i];\n        }\n    }\n", f);
    for (i = 1; i < g->nterms; i++)
        if (!g->terms[i].literal)
            fprintf(f, "    if ((n = casa_%s(fonte + pos)) > melhor) {\n"
                       "        melhor = n;\n        tipo = %s;\n    }\n",
                    g->terms[i].nome_c, g->terms[i].nome_c);
    fputs("    if (melhor == 0) {\n", f);
    fputs("        fprintf(stderr, \"linha %d, coluna %d: erro lexico: caractere "
          "invalido '%c'\\n\",\n                linha, coluna, fonte[pos]);\n", f);
    fputs("        exit(EXIT_FAILURE);\n    }\n", f);
    fputs("    n = melhor < sizeof t.lexema ? melhor : sizeof t.lexema - 1;\n", f);
    fputs("    memcpy(t.lexema, fonte + pos, n);\n    t.lexema[n] = '\\0';\n", f);
    fputs("    t.tipo = tipo;\n    consumir(melhor);\n    return t;\n}\n\n", f);
    (void) nlit;
    return erros;
}

static void gerar_procedimentos(FILE *f, const Gramatica *g, const OpcoesGeracao *op)
{
    int i;
    Emissor em;
    em.f = f;
    em.nivel = 0;

    fputs("/* ---- procedimentos (um por nao terminal) ---- */\n\n", f);
    for (i = 0; i < g->nnts; i++) {
        if (g->nts[i].regra == NULL)
            continue;
        fprintf(f, "/* %s = ", g->nts[i].nome);
        {
            /* a regra em EBNF, sem "* /" */
            FILE *tmp = tmpfile();
            int c;
            if (tmp != NULL) {
                char buf[2] = { 0, 0 };
                expr_imprimir(tmp, g, g->nts[i].regra);
                rewind(tmp);
                while ((c = fgetc(tmp)) != EOF) {
                    buf[0] = (char) c;
                    emitir_comentario(f, buf);
                }
                fclose(tmp);
            }
        }
        fputs(" ; */\n", f);
        fprintf(f, "void parse_%s(void)\n{\n", g->nts[i].nome);
        em.nivel = 1;
        if (op->arvore)
            emit(&em, "arvore_entra(\"%s\");", g->nts[i].nome);
        gen_expr(&em, g, g->nts[i].regra);
        if (op->arvore)
            emit(&em, "arvore_sai();");
        fputs("}\n\n", f);
    }
}

static void gerar_main(FILE *f, const Gramatica *g, const OpcoesGeracao *op)
{
    fputs("/* ---- programa principal ---- */\n\n", f);
    fputs("int main(int argc, char **argv)\n{\n", f);
    fputs("    int i, fim[2];\n    const char *arquivo = NULL, *tokens = NULL;\n", f);
    fputs("    FILE *entrada = stdin;\n\n", f);
    fputs("    for (i = 1; i < argc; i++) {\n", f);
    fputs("        if (strcmp(argv[i], \"--tree\") == 0) {\n", f);
    fputs("            imprimir_arvore = 1;\n", f);
    fputs("        } else if (strcmp(argv[i], \"--tokens\") == 0 && i + 1 < argc) {\n", f);
    fputs("            tokens = argv[++i];\n", f);
    fputs("        } else if (argv[i][0] == '-' && argv[i][1] != '\\0') {\n", f);
    fputs("            fprintf(stderr, \"uso: %s [--tree] [--tokens arquivo.tok | "
          "programa]\\n\", argv[0]);\n", f);
    fputs("            return 2;\n        } else {\n            arquivo = argv[i];\n"
          "        }\n    }\n", f);
    fputs("    if (imprimir_arvore && !SUPORTE_ARVORE)\n", f);
    fputs("        fprintf(stderr, \"aviso: gere o analisador com --tree para "
          "imprimir a arvore\\n\");\n\n", f);
    fputs("    if (tokens != NULL) {\n", f);
    fputs("        arquivo_tokens = fopen(tokens, \"r\");\n", f);
    fputs("        if (arquivo_tokens == NULL) {\n", f);
    fputs("            fprintf(stderr, \"nao foi possivel abrir %s\\n\", tokens);\n", f);
    fputs("            return 2;\n        }\n    } else {\n", f);
    fputs("        if (arquivo != NULL && (entrada = fopen(arquivo, \"r\")) == NULL) {\n", f);
    fputs("            fprintf(stderr, \"nao foi possivel abrir %s\\n\", arquivo);\n", f);
    fputs("            return 2;\n        }\n", f);
    if (op->microc)
        fputs("        scanner_iniciar(entrada);\n", f);
    else
        fputs("        fonte = ler_tudo(entrada);\n", f);
    fputs("        arquivo_entrada = entrada;\n", f);
    fputs("    }\n\n", f);
    fputs("    atexit(limpar_recursos);\n\n", f);
    fputs("    avancar();\n", f);
    fprintf(f, "    parse_%s();\n", g->nts[g->inicial].nome);
    fputs("    if (tok.tipo != TOKEN_FIM) {\n", f);
    fputs("        fim[0] = TOKEN_FIM;\n        fim[1] = -1;\n", f);
    fputs("        erro_sintatico(fim);\n    }\n", f);
    fputs("    printf(\"entrada aceita\\n\");\n\n", f);
    fputs("    return 0;\n}\n", f);
}

static const char *nome_base(const char *caminho)
{
    const char *b = strrchr(caminho, '/');
    return b != NULL ? b + 1 : caminho;
}

static int gerar_c(const Gramatica *g, const OpcoesGeracao *op)
{
    char *caminho = (char *) xmalloc(strlen(op->prefixo) + 3);
    FILE *f, *corpo;
    int c, erros = 0;

    /* Os procedimentos sao gerados primeiro num arquivo temporario porque
     * registram os conjuntos (conj_N), que precisam vir antes no .c. */
    corpo = tmpfile();
    if (corpo == NULL) {
        diag_erro(0, 0, "nao foi possivel criar arquivo temporario");
        free(caminho);
        return -1;
    }
    gerar_procedimentos(corpo, g, op);

    sprintf(caminho, "%s.c", op->prefixo);
    f = fopen(caminho, "w");
    if (f == NULL) {
        diag_erro(0, 0, "nao foi possivel criar %s", caminho);
        fclose(corpo);
        free(caminho);
        return -1;
    }
    escrever_cabecalho_c(f, op);
    fputs("#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n", f);
    fprintf(f, "#include \"%s.h\"\n\n", nome_base(op->prefixo));
    fprintf(f, "#define SUPORTE_ARVORE %d\n\n", op->arvore ? 1 : 0);

    fputs("/* ---- conjuntos de tokens ---- */\n\n", f);
    emitir_conjuntos(f, g);
    fputc('\n', f);

    emit_linhas(f, rt_estado);
    if (!op->microc)
        erros += gerar_lexico(f, g);
    gerar_limpar_recursos(f, op->microc);
    gerar_nome_token(f, g);
    gerar_posicao_e_avancar(f, op->microc);
    emit_linhas(f, rt_primitivas);
    gen_token_de_arquivo(f, op->microc);

    rewind(corpo);
    while ((c = fgetc(corpo)) != EOF)
        fputc(c, f);
    fclose(corpo);

    gerar_main(f, g, op);
    fclose(f);
    free(caminho);
    return erros == 0 ? 0 : -1;
}

int codegen_gerar(Gramatica *g, const OpcoesGeracao *op)
{
    int r;
    nomear_terminais(g, op->microc);
    r = gerar_h(g, op);
    if (r == 0)
        r = gerar_c(g, op);
    liberar_conjuntos();
    return r;
}
