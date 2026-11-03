/*
 * ebnf_parser.c - Analisador sintatico descendente recursivo da notacao EBNF.
 *
 * Gramatica da propria notacao (escrita em EBNF):
 *
 *   gramatica    = [ secao_tokens ] secao_rules ;
 *   secao_tokens = "TOKENS" ( "EXTERN" LITERAL ";" | { def_token } ) ;
 *   def_token    = NOME_TERM "=" REGEX ";"
 *                | "SKIP" "=" REGEX ";" ;
 *   secao_rules  = "RULES" regra { regra } ;
 *   regra        = NAOTERM "=" expr ";" ;
 *   expr         = seq { "|" seq } ;
 *   seq          = { fator } ;
 *   fator        = NOME_TERM | LITERAL | NAOTERM
 *                | "(" expr ")" | "[" expr "]" | "{" expr "}" ;
 *
 * As secoes TOKENS e RULES e a regra completa (regra) ja estao prontas,
 * incluindo a recuperacao de erros por sincronizacao no ';'.
 *
 * TODO(aluno): implementar parse_expr, parse_seq e parse_fator, que
 * constroem a arvore Expr do lado direito das regras (ver gramatica.h).
 */
#include <stdlib.h>
#include <string.h>
#include "ebnf_parser.h"
#include "ebnf_lexer.h"
#include "util.h"

typedef struct {
    MetaLexer lx;
    MetaToken tok;      /* token corrente (lookahead) */
    Gramatica *g;
} Parser;

/* ------------------------------------------------------------------ */
/* Primitivas                                                         */
/* ------------------------------------------------------------------ */

/* Consome o token corrente. Tokens MT_ERRO (ja reportados pelo
 * lexer) sao descartados. */
static void avancar(Parser *p)
{
    mtok_liberar(&p->tok);
    p->tok = mlex_proximo(&p->lx);
    while (p->tok.tipo == MT_ERRO)
        p->tok = mlex_proximo(&p->lx);
}

static void erro_encontrado(Parser *p, const char *esperado)
{
    if (p->tok.texto != NULL)
        diag_erro(p->tok.linha, p->tok.coluna, "esperado %s, encontrado %s '%s'",
                  esperado, mtipo_nome(p->tok.tipo), p->tok.texto);
    else
        diag_erro(p->tok.linha, p->tok.coluna, "esperado %s, encontrado %s",
                  esperado, mtipo_nome(p->tok.tipo));
}

/* Se o token corrente for do tipo t, consome-o e retorna 1;
 * senao reporta o erro e retorna 0 (sem consumir). */
static int esperar(Parser *p, MetaTipo t)
{
    if (p->tok.tipo == t) {
        avancar(p);
        return 1;
    }
    erro_encontrado(p, mtipo_nome(t));
    return 0;
}

/* Recuperacao de erro: descarta tokens ate depois do proximo ';'
 * (ou ate RULES / fim de arquivo). */
static void sincronizar(Parser *p)
{
    while (p->tok.tipo != MT_PV && p->tok.tipo != MT_FIM && p->tok.tipo != MT_RULES)
        avancar(p);
    if (p->tok.tipo == MT_PV)
        avancar(p);
}

/* ------------------------------------------------------------------ */
/* Expressoes (lado direito das regras)                               */
/* ------------------------------------------------------------------ */

static Expr *parse_expr(Parser *p);

/*
 * TODO(aluno): implementar as funcoes abaixo seguindo a gramatica da
 * notacao (cabecalho deste arquivo), uma funcao por nao terminal:
 *
 *   static Expr *parse_expr(Parser *p);   expr  = seq { "|" seq } ;
 *   static Expr *parse_seq(Parser *p);    seq   = { fator } ;
 *   static Expr *parse_fator(Parser *p);  fator = NOME_TERM | LITERAL | ...
 *
 * Dicas:
 *   - O token corrente esta em p->tok (tipo, texto, linha, coluna);
 *     avancar(p) consome-o e esperar(p, MT_...) consome um token exigido.
 *   - Terminais: gram_terminal(p->g, texto, literal, linha, coluna)
 *     devolve o indice; crie o no com expr_simbolo(E_TERM, ...).
 *   - Nao terminais: gram_naoterminal(...) e expr_simbolo(E_NAOTERM, ...).
 *   - [ a ] e { a }: expr_unario(E_OPC, a, ...) e expr_unario(E_REP, a, ...).
 *   - ( a ) nao cria no: devolva a propria arvore de a.
 *   - Evite nos com um unico filho: uma sequencia com um so fator ou
 *     uma alternativa unica devem ser devolvidas diretamente.
 *   - Uma sequencia vazia (ex.: "a = ;" ou "b | ") vira E_VAZIO.
 *
 * O stub abaixo apenas descarta o lado direito da regra, para que o
 * gerador compile e execute de ponta a ponta. Substitua-o.
 */
static Expr *parse_expr(Parser *p)
{
    static int avisado = 0;
    int l = p->tok.linha, c = p->tok.coluna;
    if (!avisado) {
        diag_aviso(l, c, "parse_expr ainda nao implementado: regras lidas como vazias");
        avisado = 1;
    }
    while (p->tok.tipo != MT_PV && p->tok.tipo != MT_FIM)
        avancar(p);
    return expr_criar(E_VAZIO, l, c);
}

/* ------------------------------------------------------------------ */
/* Secoes e regras (fornecido)                                        */
/* ------------------------------------------------------------------ */

/* def_token = NOME_TERM "=" REGEX ";" | "SKIP" "=" REGEX ";" ; */
static void parse_def_token(Parser *p)
{
    int skip = p->tok.tipo == MT_SKIP, l = p->tok.linha, c = p->tok.coluna, i = -1;

    if (!skip) {
        i = gram_busca_terminal(p->g, p->tok.texto, 0);
        if (i >= 0 && p->g->terms[i].declarado) {
            diag_erro(l, c, "terminal %s declarado mais de uma vez (primeira declaracao "
                      "na linha %d)", p->tok.texto, p->g->terms[i].linha);
            sincronizar(p);
            return;
        }
        i = gram_terminal(p->g, p->tok.texto, 0, l, c);
    }
    avancar(p);
    if (!esperar(p, MT_IGUAL)) {
        sincronizar(p);
        return;
    }
    if (p->tok.tipo != MT_REGEX) {
        erro_encontrado(p, "expressao regular /.../");
        sincronizar(p);
        return;
    }
    if (skip) {
        gram_add_skip(p->g, p->tok.texto);
    } else {
        p->g->terms[i].regex = xstrdup(p->tok.texto);
        p->g->terms[i].declarado = 1;
    }
    avancar(p);
    if (!esperar(p, MT_PV))
        sincronizar(p);
}

/* secao_tokens = "TOKENS" ( "EXTERN" LITERAL ";" | { def_token } ) ; */
static void parse_secao_tokens(Parser *p)
{
    avancar(p); /* TOKENS */
    if (p->tok.tipo == MT_EXTERN) {
        avancar(p);
        if (p->tok.tipo != MT_LITERAL) {
            erro_encontrado(p, "caminho do cabecalho entre aspas (ex.: \"tokens.h\")");
            sincronizar(p);
            return;
        }
        p->g->tokens_externos = xstrdup(p->tok.texto);
        avancar(p);
        if (!esperar(p, MT_PV))
            sincronizar(p);
        return;
    }
    while (p->tok.tipo == MT_NOME_TERM || p->tok.tipo == MT_SKIP)
        parse_def_token(p);
}

/* regra = NAOTERM "=" expr ";" ; */
static void parse_regra(Parser *p)
{
    int l = p->tok.linha, c = p->tok.coluna, nt, erros_antes = diag_num_erros();
    Expr *e;

    nt = gram_naoterminal(p->g, p->tok.texto, l, c);
    avancar(p);
    if (!esperar(p, MT_IGUAL)) {
        sincronizar(p);
        return;
    }
    e = parse_expr(p);
    if (diag_num_erros() > erros_antes || !esperar(p, MT_PV)) {
        expr_liberar(e);
        sincronizar(p);
        return;
    }
    if (p->g->nts[nt].regra != NULL) {
        diag_erro(l, c, "nao terminal %s definido mais de uma vez (primeira definicao "
                  "na linha %d)", p->g->nts[nt].nome, p->g->nts[nt].linha_def);
        expr_liberar(e);
        return;
    }
    p->g->nts[nt].regra = e;
    p->g->nts[nt].linha_def = l;
    if (p->g->inicial < 0)
        p->g->inicial = nt;
}

/* secao_rules = "RULES" regra { regra } ; */
static void parse_secao_rules(Parser *p)
{
    if (!esperar(p, MT_RULES))
        return;
    if (p->tok.tipo != MT_NAOTERM)
        erro_encontrado(p, "ao menos uma regra (nao terminal)");
    while (p->tok.tipo != MT_FIM) {
        if (p->tok.tipo == MT_NAOTERM) {
            parse_regra(p);
        } else {
            erro_encontrado(p, "nao terminal no inicio de uma regra");
            avancar(p);
            sincronizar(p);
        }
    }
}

int ebnf_analisar(Gramatica *g, const char *fonte)
{
    Parser p;
    p.g = g;
    mlex_iniciar(&p.lx, fonte);
    p.tok.texto = NULL;
    avancar(&p);

    if (p.tok.tipo == MT_TOKENS)
        parse_secao_tokens(&p);
    if (p.tok.tipo != MT_RULES) {
        erro_encontrado(&p, "RULES (ou uma definicao de token)");
        while (p.tok.tipo != MT_RULES && p.tok.tipo != MT_FIM)
            avancar(&p);
    }
    parse_secao_rules(&p);
    mtok_liberar(&p.tok);
    return diag_num_erros() == 0;
}
