/*
 * conjuntos.c - Calculo de anulavel, FIRST e FOLLOW (etapa 3).
 *
 * Fornecido: conj_iniciar e conj_imprimir.
 *
 * Implementado: conj_anulavel, conj_first e conj_follow. Os tres sao
 * calculados por iteracao ate ponto fixo: repita uma passada sobre todas
 * as regras enquanto algum conjunto (ou flag) mudar. bitset_unir devolve
 * 1 quando o conjunto de destino muda, o que ajuda a detectar o ponto fixo.
 */
#include <stdio.h>
#include <string.h>
#include "conjuntos.h"
#include "util.h"

/* ------------------------------------------------------------------ */
/* Fornecido                                                          */
/* ------------------------------------------------------------------ */

static void iniciar_expr(Expr *e, void *ctx)
{
    int n = *(int *) ctx;
    bitset_liberar(&e->first);
    bitset_liberar(&e->follow);
    bitset_iniciar(&e->first, n);
    bitset_iniciar(&e->follow, n);
    e->anulavel = 0;
}

void conj_iniciar(Gramatica *g)
{
    int i, n = g->nterms;
    for (i = 0; i < g->nnts; i++) {
        bitset_liberar(&g->nts[i].first);
        bitset_liberar(&g->nts[i].follow);
        bitset_iniciar(&g->nts[i].first, n);
        bitset_iniciar(&g->nts[i].follow, n);
        g->nts[i].anulavel = 0;
        expr_percorrer(g->nts[i].regra, iniciar_expr, &n);
    }
}

void conj_imprimir(FILE *f, const Gramatica *g)
{
    int i;
    size_t largura = strlen("NAO TERMINAL");
    for (i = 0; i < g->nnts; i++)
        if (strlen(g->nts[i].nome) > largura)
            largura = strlen(g->nts[i].nome);
    fprintf(f, "%-*s  ANULAVEL  FIRST / FOLLOW\n", (int) largura, "NAO TERMINAL");
    for (i = 0; i < g->nnts; i++) {
        fprintf(f, "%-*s  %-8s  FIRST  = ", (int) largura, g->nts[i].nome,
                g->nts[i].anulavel ? "sim" : "nao");
        gram_imprimir_conjunto(f, g, &g->nts[i].first);
        fprintf(f, "\n%-*s            FOLLOW = ", (int) largura, "");
        gram_imprimir_conjunto(f, g, &g->nts[i].follow);
        fputc('\n', f);
    }
}

static int atualizar_anulavel_expr(Gramatica *g, Expr *e)
{
    int i, mudou = 0, novo = 0;
    if (e == NULL)
        return 0;

    for (i = 0; i < e->nfilhos; i++) {
        if (atualizar_anulavel_expr(g, e->filhos[i]))
            mudou = 1;
    }

    switch (e->tipo) {
    case E_TERM:
        novo = 0;
        break;
    case E_VAZIO:
        novo = 1;
        break;
    case E_NAOTERM:
        novo = g->nts[e->simbolo].anulavel;
        break;
    case E_SEQ:
        novo = 1;
        for (i = 0; i < e->nfilhos; i++) {
            if (!e->filhos[i]->anulavel) {
                novo = 0;
                break;
            }
        }
        break;
    case E_ALT:
        novo = 0;
        for (i = 0; i < e->nfilhos; i++) {
            if (e->filhos[i]->anulavel) {
                novo = 1;
                break;
            }
        }
        break;
    case E_OPC:
    case E_REP:
        novo = 1;
        break;
    }

    if (e->anulavel != novo) {
        e->anulavel = novo;
        mudou = 1;
    }

    return mudou;
}

/* Calcula e->anulavel para cada no Expr e g->nts[i].anulavel.
 * Repita ate nada mudar. */
void conj_anulavel(Gramatica *g)
{
    int mudou = 1;
    while (mudou) {
        int i;
        mudou = 0;
        for (i = 0; i < g->nnts; i++) {
            if (g->nts[i].regra != NULL) {
                if (atualizar_anulavel_expr(g, g->nts[i].regra))
                    mudou = 1;
                if (g->nts[i].anulavel != g->nts[i].regra->anulavel) {
                    g->nts[i].anulavel = g->nts[i].regra->anulavel;
                    mudou = 1;
                }
            }
        }
    }
}

static int atualizar_first_expr(Gramatica *g, Expr *e)
{
    int i, mudou = 0;
    if (e == NULL)
        return 0;

    for (i = 0; i < e->nfilhos; i++) {
        if (atualizar_first_expr(g, e->filhos[i]))
            mudou = 1;
    }

    switch (e->tipo) {
    case E_TERM:
        if (!bitset_tem(&e->first, e->simbolo)) {
            bitset_add(&e->first, e->simbolo);
            mudou = 1;
        }
        break;
    case E_NAOTERM:
        if (bitset_unir(&e->first, &g->nts[e->simbolo].first))
            mudou = 1;
        break;
    case E_VAZIO:
        break;
    case E_ALT:
    case E_OPC:
    case E_REP:
        for (i = 0; i < e->nfilhos; i++) {
            if (bitset_unir(&e->first, &e->filhos[i]->first))
                mudou = 1;
        }
        break;
    case E_SEQ:
        for (i = 0; i < e->nfilhos; i++) {
            if (bitset_unir(&e->first, &e->filhos[i]->first))
                mudou = 1;
            if (!e->filhos[i]->anulavel)
                break;
        }
        break;
    }

    return mudou;
}

/* Calcula e->first para cada no Expr e g->nts[i].first.
 * Repita ate nada mudar. */
void conj_first(Gramatica *g)
{
    int mudou = 1;
    while (mudou) {
        int i;
        mudou = 0;
        for (i = 0; i < g->nnts; i++) {
            if (g->nts[i].regra != NULL) {
                if (atualizar_first_expr(g, g->nts[i].regra))
                    mudou = 1;
                if (bitset_unir(&g->nts[i].first, &g->nts[i].regra->first))
                    mudou = 1;
            }
        }
    }
}

static int propagar_follow_expr(Gramatica *g, Expr *e)
{
    int i, j, mudou = 0;
    if (e == NULL)
        return 0;

    switch (e->tipo) {
    case E_NAOTERM:
        if (bitset_unir(&g->nts[e->simbolo].follow, &e->follow))
            mudou = 1;
        break;
    case E_ALT:
    case E_OPC:
        for (i = 0; i < e->nfilhos; i++) {
            if (bitset_unir(&e->filhos[i]->follow, &e->follow))
                mudou = 1;
        }
        break;
    case E_REP:
        for (i = 0; i < e->nfilhos; i++) {
            if (bitset_unir(&e->filhos[i]->follow, &e->follow))
                mudou = 1;
            if (bitset_unir(&e->filhos[i]->follow, &e->filhos[i]->first))
                mudou = 1;
        }
        break;
    case E_SEQ:
        for (i = 0; i < e->nfilhos; i++) {
            int todos_anulaveis = 1;
            for (j = i + 1; j < e->nfilhos; j++) {
                if (bitset_unir(&e->filhos[i]->follow, &e->filhos[j]->first))
                    mudou = 1;
                if (!e->filhos[j]->anulavel) {
                    todos_anulaveis = 0;
                    break;
                }
            }
            if (todos_anulaveis) {
                if (bitset_unir(&e->filhos[i]->follow, &e->follow))
                    mudou = 1;
            }
        }
        break;
    case E_TERM:
    case E_VAZIO:
        break;
    }

    for (i = 0; i < e->nfilhos; i++) {
        if (propagar_follow_expr(g, e->filhos[i]))
            mudou = 1;
    }

    return mudou;
}

/* Calcula e->follow e g->nts[i].follow.
 * Repita ate nada mudar. */
void conj_follow(Gramatica *g)
{
    int mudou = 1;

    if (g->inicial >= 0 && g->inicial < g->nnts)
        bitset_add(&g->nts[g->inicial].follow, TERM_FIM);

    while (mudou) {
        int i;
        mudou = 0;
        for (i = 0; i < g->nnts; i++) {
            if (g->nts[i].regra != NULL) {
                if (bitset_unir(&g->nts[i].regra->follow, &g->nts[i].follow))
                    mudou = 1;
                if (propagar_follow_expr(g, g->nts[i].regra))
                    mudou = 1;
            }
        }
    }
}
