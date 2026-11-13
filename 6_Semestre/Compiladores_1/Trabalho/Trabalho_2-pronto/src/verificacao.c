/*
 * verificacao.c - Verificacoes semanticas da gramatica (etapa 2).
 *
 * Ja implementados (use como modelo):
 *   - verif_indefinidos: nao terminais usados mas nao definidos;
 *   - verif_terminais:   terminais nomeados sem declaracao.
 *
 * Implementados:
 *   - verif_inalcancaveis      (aviso)
 *   - verif_improdutivos       (erro)
 *   - verif_recursao_esquerda  (erro; direta e indireta)
 *
 * A duplicidade de definicoes ja e detectada durante a leitura
 * (ebnf_parser.c).
 */
#include <stdlib.h>
#include <string.h>
#include "verificacao.h"
#include "microc_mapa.h"
#include "util.h"

/* ------------------------------------------------------------------ */
/* Fornecido                                                          */
/* ------------------------------------------------------------------ */

static int verif_indefinidos(Gramatica *g)
{
    int i, erros = 0;
    for (i = 0; i < g->nnts; i++) {
        if (g->nts[i].regra == NULL) {
            diag_erro(g->nts[i].linha, g->nts[i].coluna, 
                      "nao terminal %s usado mas nao definido", g->nts[i].nome);
            erros++;
        }
    }
    return erros;
}

static int verif_terminais(Gramatica *g, int modo_microc)
{
    int i, erros = 0, carregado = 0;
    Terminal *t;

    if (modo_microc)
        carregado = microc_carregar_tokens_h(g->tokens_externos) == 0;

    for (i = 1; i < g->nterms; i++) {
        t = &g->terms[i];
        if (modo_microc) {
            if (t->literal && microc_nome_literal(t->nome) == NULL) {
                diag_erro(t->linha, t->coluna, "literal %s nao corresponde a nenhum "
                          "token de Micro C", t->exibicao);
                erros++;
            } else if (!t->literal && carregado && !microc_token_existe(t->nome)) {
                diag_erro(t->linha, t->coluna, "terminal %s nao existe na enumeracao "
                          "TokenType de %s", t->nome, g->tokens_externos);
                erros++;
            }
        } else if (!t->declarado) {
            diag_erro(t->linha, t->coluna, "terminal %s nao declarado em TOKENS", t->nome);
            erros++;
        }
    }
    return erros;
}

/* Coleta todos os nao terminais usados em uma expressao */
static void coletar_nts(const Expr *e, int *usados)
{
    int i;
    if (e == NULL)
        return;
    if (e->tipo == E_NAOTERM)
        usados[e->simbolo] = 1;
    for (i = 0; i < e->nfilhos; i++)
        coletar_nts(e->filhos[i], usados);
}

/* Emite um AVISO para cada nao terminal que nao pode ser alcancado a partir
 * do simbolo inicial (g->inicial). Retorna 0 (avisos nao contam como erros). */

/* Sugestao: marque o inicial e, ate um ponto fixo, marque todo nao 
 * terminal que aparece na regra de um nao terminal ja marcado (expr_percorrer ajuda). */

static int verif_inalcancaveis(Gramatica *g)
{
    int i, ini = 0, fim = 0;
    int *fila, *alcancado;

    if (g->inicial < 0 || g->nnts == 0)
        return 0;

    fila = (int *) xmalloc((size_t) g->nnts * sizeof(int));
    alcancado = (int *) xcalloc((size_t) g->nnts, sizeof(int));

    fila[fim++] = g->inicial;
    alcancado[g->inicial] = 1;

    while (ini < fim) {
        int u = fila[ini++];
        int *usados = (int *) xcalloc((size_t) g->nnts, sizeof(int));
        coletar_nts(g->nts[u].regra, usados);
        for (i = 0; i < g->nnts; i++) {
            if (usados[i] && !alcancado[i]) {
                alcancado[i] = 1;
                fila[fim++] = i;
            }
        }
        free(usados);
    }

    for (i = 0; i < g->nnts; i++) {
        if (!alcancado[i] && g->nts[i].regra != NULL) {
            diag_aviso(g->nts[i].linha_def, 0,
                       "nao terminal %s nao e alcancavel a partir do simbolo inicial",
                       g->nts[i].nome);
        }
    }

    free(fila);
    free(alcancado);
    return 0;
}

/* Verifica se uma expressao deriva uma cadeia de terminais dado o vetor de produtivos */
static int expr_produtiva(const Expr *e, const int *produtivo)
{
    int i;
    if (e == NULL)
        return 1;
    switch (e->tipo) {
    case E_TERM:
    case E_VAZIO:
    case E_OPC:
    case E_REP:
        return 1;
    case E_NAOTERM:
        return produtivo[e->simbolo];
    case E_SEQ:
        for (i = 0; i < e->nfilhos; i++) {
            if (!expr_produtiva(e->filhos[i], produtivo))
                return 0;
        }
        return 1;
    case E_ALT:
        for (i = 0; i < e->nfilhos; i++) {
            if (expr_produtiva(e->filhos[i], produtivo))
                return 1;
        }
        return 0;
    }
    return 0;
}

/* Emite um ERRO para cada nao terminal que nao deriva nenhuma cadeia de terminais */

/* Ponto fixo: um nao terminal e produtivo se sua regra for produtiva, 
 * onde terminais, E_VAZIO, [..] e {..} sao produtivos, uma sequencia 
 * exige todos os filhos produtivos e uma alternativa exige ao menos um. 
 * Retorne o numero de erros. */

static int verif_improdutivos(Gramatica *g)
{
    int i, mudou, erros = 0;
    int *produtivo;

    if (g->nnts == 0)
        return 0;

    produtivo = (int *) xcalloc((size_t) g->nnts, sizeof(int));
    mudou = 1;

    while (mudou) {
        mudou = 0;
        for (i = 0; i < g->nnts; i++) {
            if (!produtivo[i] && g->nts[i].regra != NULL) {
                if (expr_produtiva(g->nts[i].regra, produtivo)) {
                    produtivo[i] = 1;
                    mudou = 1;
                }
            }
        }
    }

    for (i = 0; i < g->nnts; i++) {
        if (!produtivo[i] && g->nts[i].regra != NULL) {
            diag_erro(g->nts[i].linha_def, 0,
                      "nao terminal %s e improdutivo (nao deriva nenhuma cadeia de terminais)",
                      g->nts[i].nome);
            erros++;
        }
    }

    free(produtivo);
    return erros;
}

/* Verifica se uma subexpressao pode derivar a cadeia vazia */
static int eh_anulavel(const Gramatica *g, const Expr *e)
{
    if (e == NULL)
        return 1;
    if (e->anulavel)
        return 1;
    if (e->tipo == E_VAZIO || e->tipo == E_OPC || e->tipo == E_REP)
        return 1;
    if (e->tipo == E_NAOTERM && g->nts[e->simbolo].anulavel)
        return 1;
    return 0;
}

/* Coleta os nao terminais que podem aparecer no inicio da derivacao de e */
static void coletar_inicios(const Gramatica *g, const Expr *e, int *direto)
{
    int i;
    if (e == NULL)
        return;
    switch (e->tipo) {
    case E_NAOTERM:
        direto[e->simbolo] = 1;
        break;
    case E_TERM:
    case E_VAZIO:
        break;
    case E_ALT:
    case E_OPC:
    case E_REP:
        for (i = 0; i < e->nfilhos; i++)
            coletar_inicios(g, e->filhos[i], direto);
        break;
    case E_SEQ:
        for (i = 0; i < e->nfilhos; i++) {
            coletar_inicios(g, e->filhos[i], direto);
            if (!eh_anulavel(g, e->filhos[i]))
                break;
        }
        break;
    }
}

/* Detecta recursao a esquerda direta (a = a ...) e
 * indireta (a = b ... ; b = a ...), inclusive atraves de prefixos
 * anulaveis (a = [ x ] a ...). Use o campo anulavel de Expr, ja
 * calculado quando esta funcao e chamada. Reporte um erro por nao
 * terminal recursivo e retorne o numero de erros. */

int verif_recursao_esquerda(Gramatica *g)
{
    int n = g->nnts, i, j, k, erros = 0;
    int **direto, **alcanca;

    if (n == 0)
        return 0;

    direto = (int **) xmalloc((size_t) n * sizeof(int *));
    alcanca = (int **) xmalloc((size_t) n * sizeof(int *));
    for (i = 0; i < n; i++) {
        direto[i] = (int *) xcalloc((size_t) n, sizeof(int));
        alcanca[i] = (int *) xcalloc((size_t) n, sizeof(int));
    }

    for (i = 0; i < n; i++) {
        if (g->nts[i].regra != NULL)
            coletar_inicios(g, g->nts[i].regra, direto[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            alcanca[i][j] = direto[i][j];
        }
    }

    /* Fecho transitivo (Floyd-Warshall) */
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (alcanca[i][k] && alcanca[k][j])
                    alcanca[i][j] = 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (g->nts[i].regra == NULL)
            continue;
        if (direto[i][i]) {
            diag_erro(g->nts[i].linha_def, 0,
                      "nao terminal %s tem recursao a esquerda direta",
                      g->nts[i].nome);
            erros++;
        } else if (alcanca[i][i]) {
            diag_erro(g->nts[i].linha_def, 0,
                      "nao terminal %s tem recursao a esquerda indireta",
                      g->nts[i].nome);
            erros++;
        }
    }

    for (i = 0; i < n; i++) {
        free(direto[i]);
        free(alcanca[i]);
    }
    free(direto);
    free(alcanca);

    return erros;
}

int verif_basica(Gramatica *g, int modo_microc)
{
    int erros = 0;
    if (g->inicial < 0) {
        diag_erro(0, 0, "a gramatica nao tem nenhuma regra");
        return 1;
    }
    erros += verif_indefinidos(g);
    erros += verif_terminais(g, modo_microc);
    erros += verif_inalcancaveis(g);
    if (erros == 0)
        erros += verif_improdutivos(g);
    return erros;
}
