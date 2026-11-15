# Relatório de Diferenças de Código: `Trabalho_2-esqueleto` vs `Trabalho_2-pronto`

Este documento registra todas as diferenças encontradas entre os diretórios `Trabalho_2-esqueleto/` (código-base entregue para o Trabalho 2, contendo ainda o scanner do Trabalho 1 em `microc/`) e `Trabalho_2-pronto/` (versão concluída, compilada e testada).

---

## 1. Resumo executivo e inventário do que mudou vs o que permaneceu idêntico

A comparação recursiva (`diff -rq Trabalho_2-esqueleto Trabalho_2-pronto`) mostra que todos os `TODO(aluno)` do esqueleto foram implementados, o scanner do Trabalho 1 (`microc/`) foi adaptado e integrado ao gerador com correção de bug na contagem de linha de literais não terminados, o código C gerado recebeu gerenciamento automático de recursos via `atexit(limpar_recursos)`, e foi adicionada uma nova suíte de testes para JSON (`testes/gramaticas/json.ebnf`, `testes/esperado/json.gerador`, `testes/programas/json/*`) além de arquivos auxiliares de teste (`testes/txt/*`) e anotações temporárias (`TEMP1.md`–`TEMP3.md`).

### 1.1. O que mudou ou foi adicionado em `Trabalho_2-pronto`

| Categoria | Arquivo / Diretório | Tipo de alteração | Resumo |
| :--- | :--- | :--- | :--- |
| Scanner Micro C (TP1 -> TP2) | `microc/tokens.h` | **Adicionado** | Cabeçalho extraído com `enum TokenType` e `struct Token` (40 linhas). |
| Scanner Micro C (TP1 -> TP2) | `microc/microc.flex` | **Modificado** | Conversão CRLF -> LF (370 -> 319 linhas), `#include "tokens.h"`, `%option prefix="microc_yy" noyywrap`, remoção de `linha_atual++` em erros de `\n` dentro de literais, remoção de `yywrap`/`main` e adição de `libera_tabela_simbolos`. |
| Scanner Micro C (TP1 -> TP2) | `microc/scanner.c` | **Modificado** | Declaração de `YYSTYPE`/`microc_yylval`/`libera_tabela_simbolos`, implementação de `texto_do_lexema` e chamada de `libera_tabela_simbolos()` em `scanner_finalizar` (100 -> 110 linhas). |
| Scanner Micro C (TP1 -> TP2) | `microc/LEIAME.md` | **Modificado** | Remoção da nota `Procure os TODO(aluno).` na descrição de `scanner.c`. |
| Gerador (`src/`) | `src/ebnf_parser.c` | **Modificado** | Implementação de `parse_expr`, `eh_inicio_fator`, `parse_seq` e `parse_fator` (250 -> 321 linhas). |
| Gerador (`src/`) | `src/verificacao.c` | **Modificado** | Implementação de `verif_inalcancaveis` (+`coletar_nts`), `verif_improdutivos` (+`expr_produtiva`) e `verif_recursao_esquerda` (+`eh_anulavel`, `coletar_inicios`, Floyd-Warshall) (116 -> 322 linhas). |
| Gerador (`src/`) | `src/conjuntos.c` | **Modificado** | Implementação de `conj_anulavel` (+`atualizar_anulavel_expr`), `conj_first` (+`atualizar_first_expr`) e `conj_follow` (+`propagar_follow_expr`) (99 -> 276 linhas). |
| Gerador (`src/`) | `src/ll1.c` | **Modificado** | Implementação de `verificar_expr` e `ll1_verificar` para as 3 condições LL(1) (60 -> 145 linhas). |
| Gerador (`src/`) | `src/codegen.c` | **Modificado** | Implementação de `gen_expr`, motor NFA->DFA e `gen_casamento_regex`, `gen_token_de_arquivo` (`--tokens`), além de `gerar_limpar_recursos` + `atexit(limpar_recursos)` (832 -> 1392 linhas). |
| Gerador (`src/`) | `src/microc_mapa.c` | **Modificado** | Implementação de `microc_carregar_tokens_h` com leitura do `enum` de `tokens.h` (91 -> 173 linhas). |
| Testes | `testes/gramaticas/json.ebnf` | **Adicionado** | Nova gramática LL(1) de JSON para o modo léxico próprio (15 linhas). |
| Testes | `testes/esperado/json.gerador` | **Adicionado** | Saída esperada de `--sets` para `json.ebnf` (12 linhas). |
| Testes | `testes/programas/json/*` | **Adicionado** | 12 arquivos (3 programas aceitos e 3 rejeitados, com pares `.json` e `.esperado`). |
| Testes | `testes/txt/*` | **Adicionado** | `exemplo.txt` (expressão de teste) e `tokens.txt` (30 tokens pré-extraídos para `--tokens`). |
| Documentação auxiliar | `TEMP1.md`, `TEMP2.md`, `TEMP3.md` | **Adicionado** | Guias de visão geral, explicação dos módulos e roteiro de execução/testes. |
| Build / Executável | `gerador`, `build/` | **Adicionado** | Binário do gerador, objetos em `build/obj/`, parser `expr` manual, parser `microc` compilado e saídas em `build/testes/`. |

### 1.2. O que permaneceu idêntico entre os dois diretórios

Todos os arquivos abaixo não sofreram nenhuma alteração entre `Trabalho_2-esqueleto` e `Trabalho_2-pronto`:

- **Raiz:** `Makefile`, `README.md`, `USO_IA.md`.
- **Micro C (`microc/`):** `microc/scanner.h` (27 linhas).
- **Código-fonte e cabeçalhos do gerador (`src/`):**
  - Todos os cabeçalhos (`.h`): `src/bitset.h`, `src/codegen.h`, `src/conjuntos.h`, `src/ebnf_lexer.h`, `src/ebnf_parser.h`, `src/gramatica.h`, `src/ll1.h`, `src/microc_mapa.h`, `src/util.h`, `src/verificacao.h`.
  - Módulos `.c` não modificados: `src/bitset.c` (118 linhas), `src/ebnf_lexer.c` (248 linhas), `src/gramatica.c` (271 linhas), `src/main.c` (154 linhas), `src/util.c` (133 linhas).
- **Suíte de testes pré-existente (`testes/`):**
  - Script `testes/executar.sh`.
  - Gramáticas `conflito_ll1.ebnf`, `expr.ebnf`, `microc.ebnf`, `recursao_esquerda.ebnf` e suas saídas esperadas em `testes/esperado/` (`conflito_ll1.gerador`, `expr.gerador`, `microc.gerador`, `recursao_esquerda.gerador`).
  - Todos os casos em `testes/programas/expr/` (`aceito_1`–`3` e `rejeitado_1`–`4`, `.txt` e `.esperado`) e `testes/programas/microc/` (`bubble`, `else_pendente`, `soma`, `rejeitado_declaracao`, `rejeitado_lexico`, `rejeitado_sintaxe`, `.mc` e `.esperado`).

---

## 2. Trabalho 1 / Scanner Micro C (`microc/`)

Esta seção documenta a evolução do scanner herdado do Trabalho 1 (`microc/`) para funcionar como biblioteca integrada ao parser gerado pelo Trabalho 2 (`--scanner microc`).

### 2.1. `microc/tokens.h` (arquivo novo)

Em `Trabalho_2-esqueleto`, o `enum TokenType` estava embutido diretamente em `microc/microc.flex` (linhas 16–39). Em `Trabalho_2-pronto`, foi criado `microc/tokens.h` (40 linhas), contendo `TokenType` (linhas 8–31) e a `struct Token` (linhas 33–37). Esse arquivo é incluído por `microc/scanner.h` (linha 15), por `microc/microc.flex` (linha 12) e lido em tempo de geração por `microc_carregar_tokens_h` (`src/microc_mapa.c`).

```c
#ifndef TOKENS_H
#define TOKENS_H

/*
 * tokens.h - Definicao da enumeracao TokenType para Micro C (TP1).
 */

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

typedef struct {
    TokenType tipo;
    char lexema[100];
    int linha;
} Token;

#endif

```

### 2.2. `microc/microc.flex` (modificado)

Principais mudanças em `microc/microc.flex`:
- **Conversão de fim de linha (`CRLF` -> `LF`):** `Trabalho_2-esqueleto/microc/microc.flex` possuía terminadores `CRLF` (`370` linhas), enquanto `Trabalho_2-pronto/microc/microc.flex` utiliza terminadores `LF` (`319` linhas). Para isolar apenas as mudanças lógicas de código no diff unificado abaixo, foi usado `diff -u --strip-trailing-cr`.
- **Reuso de `tokens.h`:** remove a definição local de `TokenType` (esqueleto linhas 12–39) e adiciona `#include "tokens.h"` (pronto linha 12).
- **Opções do Flex para integração:** adiciona `%option prefix="microc_yy" noyywrap` (pronto linha 122), expondo `microc_yylex`, `microc_yyin`, `microc_yytext` e `microc_yylex_destroy` sem necessidade de `yywrap`.
- **Correção de bug em `linha_atual++` dentro de `<CHAR_LITERAL>\n` e `<STRING_LITERAL>\n`:** remove `linha_atual++;` antes de `return UNDEF;` nas duas regras (esqueleto linhas 245 e 283 -> pronto linhas 219–223 e 256–260). Como `proximo_token()` em `microc/scanner.c` grava `t.linha = linha_atual;` *depois* que `microc_yylex()` retorna, incrementar `linha_atual` antes de retornar `UNDEF` fazia o erro léxico de caractere/string não terminado ser reportado na linha seguinte em vez da linha onde o literal foi aberto.
- **Remoção do driver do TP1 e adição de limpeza de memória:** remove `int yywrap(void)` (esqueleto linhas 335–337) e `int main(int argc, char **argv)` (esqueleto linhas 339–370), e adiciona `void libera_tabela_simbolos(void)` (pronto linhas 307–319) para liberar toda a lista encadeada `tabela_simbolos` e `literal_buffer`.

Diff completo (`diff -u --strip-trailing-cr`):

```diff
--- Trabalho_2-esqueleto/microc/microc.flex	2026-09-13 19:28:39.810395500 -0400
+++ Trabalho_2-pronto/microc/microc.flex	2026-11-03 10:21:19.997659400 -0400
@@ -9,34 +9,7 @@
 #include <stdlib.h>
 #include <string.h>
 
-/* ---------------------------------------------------------------------
- * 1. VOCABULARIO DE TOKENS (equivalente a tokens.h)
- * ------------------------------------------------------------------- */
-
-typedef enum {
-    /* Tokens fundamentais */
-    UNDEF,          /* token indefinido (usado para reportar erros) */
-    ID,             /* identificador                                */
-    END_OF_FILE,    /* fim de arquivo                               */
-
-    /* Constantes literais */
-    INTEGERCONST,
-    CHARCONST,
-    STRINGCONST,
-
-    /* Operadores aritmeticos */
-    PLUS, MINUS, MUL, DIV, MOD,
-
-    /* Operadores relacionais e logicos */
-    EQ, NEQ, LT, GT, LEQ, GEQ, AND, OR, NOT,
-
-    /* Simbolos de atribuicao e pontuacao */
-    ASSIGN, SEMICOLON, COMMA, LPAREN, RPAREN,
-    LBRACE, RBRACE, LBRACKET, RBRACKET,
-
-    /* Palavras reservadas */
-    MAIN, IF, ELSE, FOR, RETURN, INT, CHAR, PRINT
-} TokenType;
+#include "tokens.h"
 
 /* Melhor legibilidade, mesma sequencia do TokenType. */
 static const char *nome_token[] = {
@@ -146,6 +119,8 @@
 
 %}
 
+%option prefix="microc_yy" noyywrap
+
 /* -----------------------------------------------------------------------
  * 2. SECAO DE DEFINICOES
  * ------------------------------------------------------------------- */
@@ -242,7 +217,6 @@
                         return UNDEF;
                     }
 <CHAR_LITERAL>\n            {
-                        linha_atual++;
                         microc_yylval.error_msg = "Caractere nao terminado";
                         BEGIN(INITIAL);
                         return UNDEF;
@@ -280,7 +254,6 @@
                         return UNDEF;
                     }
 <STRING_LITERAL>\n           {
-                        linha_atual++;
                         microc_yylval.error_msg = "String nao terminada";
                         BEGIN(INITIAL);
                         return UNDEF;
@@ -331,40 +304,16 @@
  * 4. SUB-ROTINAS DO USUARIO
  * ------------------------------------------------------------------- */
 
-/* yywrap: Ao atingir o EOF, o flexe deve parar a leitura. */
-int yywrap(void) {
-    return 1;
-}
-
-int main(int argc, char **argv) {
-    if (argc < 2) {
-        fprintf(stderr, "Uso: %s <arquivo.mc>\n", argv[0]);
-        return 1;
+void libera_tabela_simbolos(void) {
+    Simbolo *s = tabela_simbolos;
+    while (s != NULL) {
+        Simbolo *prox = s->proximo;
+        free(s->texto);
+        free(s);
+        s = prox;
     }
-
-    FILE *arquivo_fonte = fopen(argv[1], "r");
-    if (!arquivo_fonte) {
-        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'\n", argv[1]);
-        return 1;
-    }
-    yyin = arquivo_fonte;
-
-    int tipo;
-    while ((tipo = yylex()) != END_OF_FILE) {
-        if (tipo == UNDEF) {
-            fprintf(stderr, "ERRO LEXICO (linha %d): %s\n",
-                    linha_atual, microc_yylval.error_msg);
-            continue;
-        }
-         const char *lexema = yytext;
-         if (tipo == ID || tipo == INTEGERCONST ||
-             tipo == CHARCONST || tipo == STRINGCONST) {
-             lexema = microc_yylval.symbol;
-         }
-         printf("Token: tipo = %-13s lexema = '%s'  linha = %d\n",
-             nome_token[tipo], lexema, linha_atual);
-    }
-
-    fclose(arquivo_fonte);
-    return 0;
+    tabela_simbolos = NULL;
+    free(literal_buffer);
+    literal_buffer = NULL;
+    literal_length = literal_capacity = 0;
 }
```

### 2.3. `microc/scanner.c` (modificado)

Principais mudanças em `microc/scanner.c` (100 -> 110 linhas):
- **Comentário atualizado:** troca `TODO(aluno):` por `Implementado:` (linha 10).
- **Declarações externas do TP1 (linhas 28–33):** declara `YYSTYPE`, `extern YYSTYPE microc_yylval;` e `void libera_tabela_simbolos(void);`.
- **`TODO(aluno)` resolvido em `texto_do_lexema(int tipo)` (linhas 37–47):** retorna `microc_yylval.error_msg` para `UNDEF`, `microc_yylval.symbol` (quando não `NULL`) para `ID`, `INTEGERCONST`, `CHARCONST` e `STRINGCONST` (preservando sequências de escape convertidas), e `microc_yytext` nos demais casos.
- **`TODO(aluno)` resolvido em `scanner_finalizar(void)` (linhas 106–110):** invoca `libera_tabela_simbolos()` antes de `microc_yylex_destroy()`.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/microc/scanner.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/microc/scanner.c	2026-11-03 10:21:19.986658700 -0400
@@ -7,7 +7,7 @@
  * que mantenha a variavel global linha_atual (TP1, secao 4.4). Sem
  * alteracoes, o lexema de cada token e o texto reconhecido (microc_yytext).
  *
- * TODO(aluno): adaptar os pontos marcados ao seu TP1, para que
+ * Implementado: adaptar os pontos marcados ao seu TP1, para que
  *   - ID e constantes usem o texto do Symbol (microc_yylval.symbol), ja
  *     com as sequencias de escape convertidas (TP1, secao 4.3);
  *   - UNDEF traga a mensagem de microc_yylval.error_msg
@@ -25,14 +25,24 @@
 extern int   linha_atual;
 extern int   microc_yylex_destroy(void);
 
+typedef struct {
+    char *symbol;
+    char *error_msg;
+} YYSTYPE;
+extern YYSTYPE microc_yylval;
+void libera_tabela_simbolos(void);
+
 /* Texto a guardar em Token.lexema para o token que microc_yylex acabou
  * de devolver. */
 static const char *texto_do_lexema(int tipo)
 {
-    /* TODO(aluno): para ID, INTEGERCONST, CHARCONST e STRINGCONST, devolva
-     * o texto do Symbol em microc_yylval.symbol; para UNDEF, devolva
-     * microc_yylval.error_msg. */
-    (void) tipo;
+    if (tipo == (int) UNDEF)
+        return microc_yylval.error_msg;
+    if (tipo == (int) ID || tipo == (int) INTEGERCONST ||
+        tipo == (int) CHARCONST || tipo == (int) STRINGCONST) {
+        if (microc_yylval.symbol != NULL)
+            return microc_yylval.symbol;
+    }
     return microc_yytext;
 }
 
@@ -95,6 +105,6 @@
 
 void scanner_finalizar(void)
 {
-    /* TODO(aluno): liberar tambem a tabela de strings do TP1. */
+    libera_tabela_simbolos();
     microc_yylex_destroy();
 }
```

### 2.4. `microc/LEIAME.md` (modificado)

Remove a instrução `Procure os TODO(aluno).` da descrição de `scanner.c` na linha 8.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/microc/LEIAME.md	2026-10-19 18:56:22.000000000 -0400
+++ Trabalho_2-pronto/microc/LEIAME.md	2026-11-03 10:21:19.972910500 -0400
@@ -5,7 +5,7 @@
 Já fornecidos:
 
 - `scanner.h`: interface usada pelo analisador gerado (`scanner_iniciar`, `proximo_token`, `scanner_finalizar`).
-- `scanner.c`: adaptador entre `microc_yylex()` e `Token`. Procure os `TODO(aluno)`.
+- `scanner.c`: adaptador entre `microc_yylex()` e `Token`.
 
 Copie do seu TP1:
 
```

---

## 3. Implementação do Gerador e correções (`src/`)

Esta seção detalha todas as implementações dos `TODO(aluno)` e correções nos seis arquivos modificados de `src/`.

### 3.1. `src/ebnf_parser.c` (250 -> 321 linhas)

- **TODOs resolvidos:** `parse_expr`, `parse_seq` e `parse_fator` (comentários atualizados em `L20` e `L90`; removido comentário do stub).
- **Código removido:** stub de `parse_expr` (`esqueleto` L107–121) que emitia `diag_aviso("parse_expr ainda nao implementado: regras lidas como vazias")`, consumia tokens até `MT_PV`/`MT_FIM` e retornava `E_VAZIO`.
- **Funções implementadas e adicionadas:**
  - Protótipos `static Expr *parse_seq(Parser *p);` (`L86`) e `static Expr *parse_fator(Parser *p);` (`L87`).
  - `parse_expr(Parser *p)` (`L109–123`): implementa `expr = seq { "|" seq } ;`, criando nó `E_ALT` apenas se houver ao menos um `MT_BARRA` (evitando nós `E_ALT` com filho único).
  - `eh_inicio_fator(MetaTipo t)` (`L125–127`, nova): reconhece `MT_NOME_TERM`, `MT_LITERAL`, `MT_NAOTERM`, `MT_ABRE_PAR`, `MT_ABRE_COL` e `MT_ABRE_CHAVE`.
  - `parse_seq(Parser *p)` (`L130–153`, nova): implementa `seq = { fator } ;`, retornando `E_VAZIO` para sequência vazia, o próprio nó para um único fator, ou `E_SEQ` para dois ou mais fatores.
  - `parse_fator(Parser *p)` (`L156–192`, nova): trata terminais nomeados/literais (`E_TERM`), não terminais (`E_NAOTERM`), agrupamentos `(...)`, opcionais `[...]` (`E_OPC`), repetições `{...}` (`E_REP`) e erro sintático no `default` via `erro_encontrado(p, "fator")`.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/ebnf_parser.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/ebnf_parser.c	2026-11-03 10:21:20.019682900 -0400
@@ -17,7 +17,7 @@
  * As secoes TOKENS e RULES e a regra completa (regra) ja estao prontas,
  * incluindo a recuperacao de erros por sincronizacao no ';'.
  *
- * TODO(aluno): implementar parse_expr, parse_seq e parse_fator, que
+ * Implementado parse_expr, parse_seq e parse_fator, que
  * constroem a arvore Expr do lado direito das regras (ver gramatica.h).
  */
 #include <stdlib.h>
@@ -83,9 +83,11 @@
 /* ------------------------------------------------------------------ */
 
 static Expr *parse_expr(Parser *p);
+static Expr *parse_seq(Parser *p);
+static Expr *parse_fator(Parser *p);
 
 /*
- * TODO(aluno): implementar as funcoes abaixo seguindo a gramatica da
+ * Implementado as funcoes abaixo seguindo a gramatica da
  * notacao (cabecalho deste arquivo), uma funcao por nao terminal:
  *
  *   static Expr *parse_expr(Parser *p);   expr  = seq { "|" seq } ;
@@ -103,23 +105,92 @@
  *   - Evite nos com um unico filho: uma sequencia com um so fator ou
  *     uma alternativa unica devem ser devolvidas diretamente.
  *   - Uma sequencia vazia (ex.: "a = ;" ou "b | ") vira E_VAZIO.
- *
- * O stub abaixo apenas descarta o lado direito da regra, para que o
- * gerador compile e execute de ponta a ponta. Substitua-o.
  */
-static Expr *parse_expr(Parser *p)
-{
-    static int avisado = 0;
+static Expr *parse_expr(Parser *p) {
+    Expr *primeiro = parse_seq(p);
+    Expr *alt = NULL;
+
+    while (p->tok.tipo == MT_BARRA) {
+        avancar(p); /* consome '|' */
+        if (alt == NULL) {
+            alt = expr_criar(E_ALT, primeiro->linha, primeiro->coluna);
+            expr_adicionar(alt, primeiro);
+        }
+        expr_adicionar(alt, parse_seq(p));
+    }
+
+    return alt != NULL ? alt : primeiro;
+}
+
+static int eh_inicio_fator(MetaTipo t) {
+    return t == MT_NOME_TERM || t == MT_LITERAL || t == MT_NAOTERM || t == MT_ABRE_PAR  || t == MT_ABRE_COL || t == MT_ABRE_CHAVE;
+}
+
+/* seq = { fator } ; */
+static Expr *parse_seq(Parser *p) {
     int l = p->tok.linha, c = p->tok.coluna;
-    if (!avisado) {
-        diag_aviso(l, c, "parse_expr ainda nao implementado: regras lidas como vazias");
-        avisado = 1;
+    Expr *seq = NULL;
+    Expr *primeiro = NULL;
+
+    while (eh_inicio_fator(p->tok.tipo)) {
+        Expr *f = parse_fator(p);
+        if (primeiro == NULL) {
+            primeiro = f;
+        } else {
+            if (seq == NULL) {
+                seq = expr_criar(E_SEQ, primeiro->linha, primeiro->coluna);
+                expr_adicionar(seq, primeiro);
+            }
+            expr_adicionar(seq, f);
+        }
     }
-    while (p->tok.tipo != MT_PV && p->tok.tipo != MT_FIM)
-        avancar(p);
+
+    if (seq != NULL)
+        return seq;
+    if (primeiro != NULL)
+        return primeiro;
     return expr_criar(E_VAZIO, l, c);
 }
 
+/* fator = NOME_TERM | LITERAL | NAOTERM | "(" expr ")" | "[" expr "]" | "{" expr "}" ; */
+static Expr *parse_fator(Parser *p) {
+    int l = p->tok.linha, c = p->tok.coluna, id;
+    Expr *e;
+
+    switch (p->tok.tipo) {
+    case MT_NOME_TERM:
+        id = gram_terminal(p->g, p->tok.texto, 0, l, c);
+        avancar(p);
+        return expr_simbolo(E_TERM, id, l, c);
+    case MT_LITERAL:
+        id = gram_terminal(p->g, p->tok.texto, 1, l, c);
+        avancar(p);
+        return expr_simbolo(E_TERM, id, l, c);
+    case MT_NAOTERM:
+        id = gram_naoterminal(p->g, p->tok.texto, l, c);
+        avancar(p);
+        return expr_simbolo(E_NAOTERM, id, l, c);
+    case MT_ABRE_PAR:
+        avancar(p);
+        e = parse_expr(p);
+        esperar(p, MT_FECHA_PAR);
+        return e;
+    case MT_ABRE_COL:
+        avancar(p);
+        e = parse_expr(p);
+        esperar(p, MT_FECHA_COL);
+        return expr_unario(E_OPC, e, l, c);
+    case MT_ABRE_CHAVE:
+        avancar(p);
+        e = parse_expr(p);
+        esperar(p, MT_FECHA_CHAVE);
+        return expr_unario(E_REP, e, l, c);
+    default:
+        erro_encontrado(p, "fator");
+        return expr_criar(E_VAZIO, l, c);
+    }
+}
+
 /* ------------------------------------------------------------------ */
 /* Secoes e regras (fornecido)                                        */
 /* ------------------------------------------------------------------ */
```

### 3.2. `src/verificacao.c` (116 -> 322 linhas)

- **TODOs resolvidos:** `verif_inalcancaveis`, `verif_improdutivos` e `verif_recursao_esquerda` (comentário em `L8`: `TODO(aluno):` -> `Implementados:`).
- **Detalhe de formatação:** em `verif_indefinidos`, a linha 31 (`pronto`) tem um espaço em branco extra no final da linha após `g->nts[i].coluna,`.
- **Código removido:** stubs `(void) g; return 0;` nas três funções de verificação.
- **Funções implementadas e adicionadas:**
  - `coletar_nts` (`L68–77`, nova) e `verif_inalcancaveis` (`L85–123`): executam busca em largura (BFS) a partir de `g->inicial` e emitem `diag_aviso` para cada não terminal definido com `!alcancado[i]`, retornando `0`.
  - `expr_produtiva` (`L126–153`, nova) e `verif_improdutivos` (`L162–196`): computam produtividade por ponto fixo (`E_TERM`, `E_VAZIO`, `E_OPC` e `E_REP` são produtivos; `E_SEQ` exige todos os filhos produtivos; `E_ALT` exige ao menos um) e emitem `diag_erro` para não terminais definidos improdutivos.
  - `eh_anulavel` (`L199–210`, nova), `coletar_inicios` (`L213–239`, nova) e `verif_recursao_esquerda` (`L247–307`): montam a matriz de inícios diretos `direto[n][n]` atravessando prefixos anuláveis em `E_SEQ`, calculam o fecho transitivo `alcanca[n][n]` com Floyd-Warshall e reportam `diag_erro` para recursão à esquerda direta (`direto[i][i]`) ou indireta (`alcanca[i][i]`).

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/verificacao.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/verificacao.c	2026-11-03 10:21:20.052922800 -0400
@@ -5,7 +5,7 @@
  *   - verif_indefinidos: nao terminais usados mas nao definidos;
  *   - verif_terminais:   terminais nomeados sem declaracao.
  *
- * TODO(aluno):
+ * Implementados:
  *   - verif_inalcancaveis      (aviso)
  *   - verif_improdutivos       (erro)
  *   - verif_recursao_esquerda  (erro; direta e indireta)
@@ -28,7 +28,7 @@
     int i, erros = 0;
     for (i = 0; i < g->nnts; i++) {
         if (g->nts[i].regra == NULL) {
-            diag_erro(g->nts[i].linha, g->nts[i].coluna,
+            diag_erro(g->nts[i].linha, g->nts[i].coluna, 
                       "nao terminal %s usado mas nao definido", g->nts[i].nome);
             erros++;
         }
@@ -64,40 +64,246 @@
     return erros;
 }
 
-/* ------------------------------------------------------------------ */
-/* A implementar                                                      */
-/* ------------------------------------------------------------------ */
+/* Coleta todos os nao terminais usados em uma expressao */
+static void coletar_nts(const Expr *e, int *usados)
+{
+    int i;
+    if (e == NULL)
+        return;
+    if (e->tipo == E_NAOTERM)
+        usados[e->simbolo] = 1;
+    for (i = 0; i < e->nfilhos; i++)
+        coletar_nts(e->filhos[i], usados);
+}
+
+/* Emite um AVISO para cada nao terminal que nao pode ser alcancado a partir
+ * do simbolo inicial (g->inicial). Retorna 0 (avisos nao contam como erros). */
+
+/* Sugestao: marque o inicial e, ate um ponto fixo, marque todo nao 
+ * terminal que aparece na regra de um nao terminal ja marcado (expr_percorrer ajuda). */
 
-/* TODO(aluno): emitir um AVISO para cada nao terminal que nao pode ser
- * alcancado a partir do simbolo inicial (g->inicial). Sugestao: marque
- * o inicial e, ate um ponto fixo, marque todo nao terminal que aparece
- * na regra de um nao terminal ja marcado (expr_percorrer ajuda). */
 static int verif_inalcancaveis(Gramatica *g)
 {
-    (void) g;
+    int i, ini = 0, fim = 0;
+    int *fila, *alcancado;
+
+    if (g->inicial < 0 || g->nnts == 0)
+        return 0;
+
+    fila = (int *) xmalloc((size_t) g->nnts * sizeof(int));
+    alcancado = (int *) xcalloc((size_t) g->nnts, sizeof(int));
+
+    fila[fim++] = g->inicial;
+    alcancado[g->inicial] = 1;
+
+    while (ini < fim) {
+        int u = fila[ini++];
+        int *usados = (int *) xcalloc((size_t) g->nnts, sizeof(int));
+        coletar_nts(g->nts[u].regra, usados);
+        for (i = 0; i < g->nnts; i++) {
+            if (usados[i] && !alcancado[i]) {
+                alcancado[i] = 1;
+                fila[fim++] = i;
+            }
+        }
+        free(usados);
+    }
+
+    for (i = 0; i < g->nnts; i++) {
+        if (!alcancado[i] && g->nts[i].regra != NULL) {
+            diag_aviso(g->nts[i].linha_def, 0,
+                       "nao terminal %s nao e alcancavel a partir do simbolo inicial",
+                       g->nts[i].nome);
+        }
+    }
+
+    free(fila);
+    free(alcancado);
+    return 0;
+}
+
+/* Verifica se uma expressao deriva uma cadeia de terminais dado o vetor de produtivos */
+static int expr_produtiva(const Expr *e, const int *produtivo)
+{
+    int i;
+    if (e == NULL)
+        return 1;
+    switch (e->tipo) {
+    case E_TERM:
+    case E_VAZIO:
+    case E_OPC:
+    case E_REP:
+        return 1;
+    case E_NAOTERM:
+        return produtivo[e->simbolo];
+    case E_SEQ:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (!expr_produtiva(e->filhos[i], produtivo))
+                return 0;
+        }
+        return 1;
+    case E_ALT:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (expr_produtiva(e->filhos[i], produtivo))
+                return 1;
+        }
+        return 0;
+    }
     return 0;
 }
 
-/* TODO(aluno): emitir um ERRO para cada nao terminal definido que nao
- * deriva nenhuma cadeia de terminais. Ponto fixo: um nao terminal e
- * produtivo se sua regra for produtiva, onde terminais, E_VAZIO, [..] e
- * {..} sao produtivos, uma sequencia exige todos os filhos produtivos
- * e uma alternativa exige ao menos um. Retorne o numero de erros. */
+/* Emite um ERRO para cada nao terminal que nao deriva nenhuma cadeia de terminais */
+
+/* Ponto fixo: um nao terminal e produtivo se sua regra for produtiva, 
+ * onde terminais, E_VAZIO, [..] e {..} sao produtivos, uma sequencia 
+ * exige todos os filhos produtivos e uma alternativa exige ao menos um. 
+ * Retorne o numero de erros. */
+
 static int verif_improdutivos(Gramatica *g)
 {
-    (void) g;
+    int i, mudou, erros = 0;
+    int *produtivo;
+
+    if (g->nnts == 0)
+        return 0;
+
+    produtivo = (int *) xcalloc((size_t) g->nnts, sizeof(int));
+    mudou = 1;
+
+    while (mudou) {
+        mudou = 0;
+        for (i = 0; i < g->nnts; i++) {
+            if (!produtivo[i] && g->nts[i].regra != NULL) {
+                if (expr_produtiva(g->nts[i].regra, produtivo)) {
+                    produtivo[i] = 1;
+                    mudou = 1;
+                }
+            }
+        }
+    }
+
+    for (i = 0; i < g->nnts; i++) {
+        if (!produtivo[i] && g->nts[i].regra != NULL) {
+            diag_erro(g->nts[i].linha_def, 0,
+                      "nao terminal %s e improdutivo (nao deriva nenhuma cadeia de terminais)",
+                      g->nts[i].nome);
+            erros++;
+        }
+    }
+
+    free(produtivo);
+    return erros;
+}
+
+/* Verifica se uma subexpressao pode derivar a cadeia vazia */
+static int eh_anulavel(const Gramatica *g, const Expr *e)
+{
+    if (e == NULL)
+        return 1;
+    if (e->anulavel)
+        return 1;
+    if (e->tipo == E_VAZIO || e->tipo == E_OPC || e->tipo == E_REP)
+        return 1;
+    if (e->tipo == E_NAOTERM && g->nts[e->simbolo].anulavel)
+        return 1;
     return 0;
 }
 
-/* TODO(aluno): detectar recursao a esquerda direta (a = a ...) e
+/* Coleta os nao terminais que podem aparecer no inicio da derivacao de e */
+static void coletar_inicios(const Gramatica *g, const Expr *e, int *direto)
+{
+    int i;
+    if (e == NULL)
+        return;
+    switch (e->tipo) {
+    case E_NAOTERM:
+        direto[e->simbolo] = 1;
+        break;
+    case E_TERM:
+    case E_VAZIO:
+        break;
+    case E_ALT:
+    case E_OPC:
+    case E_REP:
+        for (i = 0; i < e->nfilhos; i++)
+            coletar_inicios(g, e->filhos[i], direto);
+        break;
+    case E_SEQ:
+        for (i = 0; i < e->nfilhos; i++) {
+            coletar_inicios(g, e->filhos[i], direto);
+            if (!eh_anulavel(g, e->filhos[i]))
+                break;
+        }
+        break;
+    }
+}
+
+/* Detecta recursao a esquerda direta (a = a ...) e
  * indireta (a = b ... ; b = a ...), inclusive atraves de prefixos
  * anulaveis (a = [ x ] a ...). Use o campo anulavel de Expr, ja
  * calculado quando esta funcao e chamada. Reporte um erro por nao
  * terminal recursivo e retorne o numero de erros. */
+
 int verif_recursao_esquerda(Gramatica *g)
 {
-    (void) g;
-    return 0;
+    int n = g->nnts, i, j, k, erros = 0;
+    int **direto, **alcanca;
+
+    if (n == 0)
+        return 0;
+
+    direto = (int **) xmalloc((size_t) n * sizeof(int *));
+    alcanca = (int **) xmalloc((size_t) n * sizeof(int *));
+    for (i = 0; i < n; i++) {
+        direto[i] = (int *) xcalloc((size_t) n, sizeof(int));
+        alcanca[i] = (int *) xcalloc((size_t) n, sizeof(int));
+    }
+
+    for (i = 0; i < n; i++) {
+        if (g->nts[i].regra != NULL)
+            coletar_inicios(g, g->nts[i].regra, direto[i]);
+    }
+
+    for (i = 0; i < n; i++) {
+        for (j = 0; j < n; j++) {
+            alcanca[i][j] = direto[i][j];
+        }
+    }
+
+    /* Fecho transitivo (Floyd-Warshall) */
+    for (k = 0; k < n; k++) {
+        for (i = 0; i < n; i++) {
+            for (j = 0; j < n; j++) {
+                if (alcanca[i][k] && alcanca[k][j])
+                    alcanca[i][j] = 1;
+            }
+        }
+    }
+
+    for (i = 0; i < n; i++) {
+        if (g->nts[i].regra == NULL)
+            continue;
+        if (direto[i][i]) {
+            diag_erro(g->nts[i].linha_def, 0,
+                      "nao terminal %s tem recursao a esquerda direta",
+                      g->nts[i].nome);
+            erros++;
+        } else if (alcanca[i][i]) {
+            diag_erro(g->nts[i].linha_def, 0,
+                      "nao terminal %s tem recursao a esquerda indireta",
+                      g->nts[i].nome);
+            erros++;
+        }
+    }
+
+    for (i = 0; i < n; i++) {
+        free(direto[i]);
+        free(alcanca[i]);
+    }
+    free(direto);
+    free(alcanca);
+
+    return erros;
 }
 
 int verif_basica(Gramatica *g, int modo_microc)
```

### 3.3. `src/conjuntos.c` (99 -> 276 linhas)

- **TODOs resolvidos:** `conj_anulavel`, `conj_first` e `conj_follow` (comentário `L6`: `TODO(aluno):` -> `Implementado:`; removidos o cabeçalho `A implementar` e os stubs `(void) g;`).
- **Funções implementadas e adicionadas:**
  - `atualizar_anulavel_expr` (`L61–112`, nova) e `conj_anulavel` (`L116–133`): calculam `e->anulavel` em pós-ordem e `g->nts[i].anulavel` por iteração até ponto fixo.
  - `atualizar_first_expr` (`L135–178`, nova) e `conj_first` (`L182–197`): atualizam em pós-ordem o `first` de todos os filhos (inclusive após filhos não anuláveis em `E_SEQ`, conforme exigido por `codegen.c`) e propagam para `g->nts[i].first` até ponto fixo.
  - `propagar_follow_expr` (`L199–253`, nova) e `conj_follow` (`L257–276`): incluem `TERM_FIM` em `g->nts[g->inicial].follow` e propagam `follow` top-down para `E_NAOTERM`, `E_ALT`, `E_OPC`, `E_REP` (incluindo `filhos[i]->first`) e `E_SEQ` (sufixos `FIRST(filhos[j])` e herança de `e->follow` quando o sufixo é anulável) até ponto fixo.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/conjuntos.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/conjuntos.c	2026-11-03 10:21:20.016658000 -0400
@@ -3,7 +3,7 @@
  *
  * Fornecido: conj_iniciar e conj_imprimir.
  *
- * TODO(aluno): conj_anulavel, conj_first e conj_follow. Os tres sao
+ * Implementado: conj_anulavel, conj_first e conj_follow. Os tres sao
  * calculados por iteracao ate ponto fixo: repita uma passada sobre todas
  * as regras enquanto algum conjunto (ou flag) mudar. bitset_unir devolve
  * 1 quando o conjunto de destino muda, o que ajuda a detectar o ponto fixo.
@@ -58,42 +58,219 @@
     }
 }
 
-/* ------------------------------------------------------------------ */
-/* A implementar                                                      */
-/* ------------------------------------------------------------------ */
+static int atualizar_anulavel_expr(Gramatica *g, Expr *e)
+{
+    int i, mudou = 0, novo = 0;
+    if (e == NULL)
+        return 0;
+
+    for (i = 0; i < e->nfilhos; i++) {
+        if (atualizar_anulavel_expr(g, e->filhos[i]))
+            mudou = 1;
+    }
+
+    switch (e->tipo) {
+    case E_TERM:
+        novo = 0;
+        break;
+    case E_VAZIO:
+        novo = 1;
+        break;
+    case E_NAOTERM:
+        novo = g->nts[e->simbolo].anulavel;
+        break;
+    case E_SEQ:
+        novo = 1;
+        for (i = 0; i < e->nfilhos; i++) {
+            if (!e->filhos[i]->anulavel) {
+                novo = 0;
+                break;
+            }
+        }
+        break;
+    case E_ALT:
+        novo = 0;
+        for (i = 0; i < e->nfilhos; i++) {
+            if (e->filhos[i]->anulavel) {
+                novo = 1;
+                break;
+            }
+        }
+        break;
+    case E_OPC:
+    case E_REP:
+        novo = 1;
+        break;
+    }
+
+    if (e->anulavel != novo) {
+        e->anulavel = novo;
+        mudou = 1;
+    }
 
-/* TODO(aluno): calcular e->anulavel para cada no Expr e g->nts[i].anulavel.
- *   E_TERM: 0        E_VAZIO: 1        E_NAOTERM: anulavel do nao terminal
- *   E_SEQ: 1 se todos os filhos forem anulaveis
- *   E_ALT: 1 se algum filho for anulavel
- *   E_OPC, E_REP: 1 (calcule tambem o do filho)
+    return mudou;
+}
+
+/* Calcula e->anulavel para cada no Expr e g->nts[i].anulavel.
  * Repita ate nada mudar. */
 void conj_anulavel(Gramatica *g)
 {
-    (void) g;
+    int mudou = 1;
+    while (mudou) {
+        int i;
+        mudou = 0;
+        for (i = 0; i < g->nnts; i++) {
+            if (g->nts[i].regra != NULL) {
+                if (atualizar_anulavel_expr(g, g->nts[i].regra))
+                    mudou = 1;
+                if (g->nts[i].anulavel != g->nts[i].regra->anulavel) {
+                    g->nts[i].anulavel = g->nts[i].regra->anulavel;
+                    mudou = 1;
+                }
+            }
+        }
+    }
 }
 
-/* TODO(aluno): calcular e->first para cada no Expr e g->nts[i].first.
- *   E_TERM t: {t}     E_NAOTERM B: FIRST(B)     E_VAZIO: {}
- *   E_SEQ a1..an: FIRST(a1) U FIRST(a2) ... ate o primeiro ai nao anulavel
- *   E_ALT, E_OPC, E_REP: uniao dos FIRST dos filhos
- * Calcule o FIRST de TODOS os filhos de uma sequencia, mesmo os que
- * nao contribuem para o FIRST dela: o gerador de codigo usa-os. */
+static int atualizar_first_expr(Gramatica *g, Expr *e)
+{
+    int i, mudou = 0;
+    if (e == NULL)
+        return 0;
+
+    for (i = 0; i < e->nfilhos; i++) {
+        if (atualizar_first_expr(g, e->filhos[i]))
+            mudou = 1;
+    }
+
+    switch (e->tipo) {
+    case E_TERM:
+        if (!bitset_tem(&e->first, e->simbolo)) {
+            bitset_add(&e->first, e->simbolo);
+            mudou = 1;
+        }
+        break;
+    case E_NAOTERM:
+        if (bitset_unir(&e->first, &g->nts[e->simbolo].first))
+            mudou = 1;
+        break;
+    case E_VAZIO:
+        break;
+    case E_ALT:
+    case E_OPC:
+    case E_REP:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (bitset_unir(&e->first, &e->filhos[i]->first))
+                mudou = 1;
+        }
+        break;
+    case E_SEQ:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (bitset_unir(&e->first, &e->filhos[i]->first))
+                mudou = 1;
+            if (!e->filhos[i]->anulavel)
+                break;
+        }
+        break;
+    }
+
+    return mudou;
+}
+
+/* Calcula e->first para cada no Expr e g->nts[i].first.
+ * Repita ate nada mudar. */
 void conj_first(Gramatica *g)
 {
-    (void) g;
+    int mudou = 1;
+    while (mudou) {
+        int i;
+        mudou = 0;
+        for (i = 0; i < g->nnts; i++) {
+            if (g->nts[i].regra != NULL) {
+                if (atualizar_first_expr(g, g->nts[i].regra))
+                    mudou = 1;
+                if (bitset_unir(&g->nts[i].first, &g->nts[i].regra->first))
+                    mudou = 1;
+            }
+        }
+    }
+}
+
+static int propagar_follow_expr(Gramatica *g, Expr *e)
+{
+    int i, j, mudou = 0;
+    if (e == NULL)
+        return 0;
+
+    switch (e->tipo) {
+    case E_NAOTERM:
+        if (bitset_unir(&g->nts[e->simbolo].follow, &e->follow))
+            mudou = 1;
+        break;
+    case E_ALT:
+    case E_OPC:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (bitset_unir(&e->filhos[i]->follow, &e->follow))
+                mudou = 1;
+        }
+        break;
+    case E_REP:
+        for (i = 0; i < e->nfilhos; i++) {
+            if (bitset_unir(&e->filhos[i]->follow, &e->follow))
+                mudou = 1;
+            if (bitset_unir(&e->filhos[i]->follow, &e->filhos[i]->first))
+                mudou = 1;
+        }
+        break;
+    case E_SEQ:
+        for (i = 0; i < e->nfilhos; i++) {
+            int todos_anulaveis = 1;
+            for (j = i + 1; j < e->nfilhos; j++) {
+                if (bitset_unir(&e->filhos[i]->follow, &e->filhos[j]->first))
+                    mudou = 1;
+                if (!e->filhos[j]->anulavel) {
+                    todos_anulaveis = 0;
+                    break;
+                }
+            }
+            if (todos_anulaveis) {
+                if (bitset_unir(&e->filhos[i]->follow, &e->follow))
+                    mudou = 1;
+            }
+        }
+        break;
+    case E_TERM:
+    case E_VAZIO:
+        break;
+    }
+
+    for (i = 0; i < e->nfilhos; i++) {
+        if (propagar_follow_expr(g, e->filhos[i]))
+            mudou = 1;
+    }
+
+    return mudou;
 }
 
-/* TODO(aluno): calcular e->follow (o que pode vir logo apos cada
- * construcao) e g->nts[i].follow. FOLLOW(inicial) contem $ (TERM_FIM).
- * Para cada regra A = alfa, faca follow(alfa) U= FOLLOW(A) e propague:
- *   E_SEQ a1..an:  follow(ai) U= FIRST(ai+1 ... an), mais follow(seq)
- *                  se ai+1 ... an for anulavel
- *   E_ALT, E_OPC:  follow(filho) U= follow(no)
- *   E_REP { a }:   follow(a) U= follow(no) U FIRST(a)
- *   E_NAOTERM B:   FOLLOW(B) U= follow(no)
+/* Calcula e->follow e g->nts[i].follow.
  * Repita ate nada mudar. */
 void conj_follow(Gramatica *g)
 {
-    (void) g;
+    int mudou = 1;
+
+    if (g->inicial >= 0 && g->inicial < g->nnts)
+        bitset_add(&g->nts[g->inicial].follow, TERM_FIM);
+
+    while (mudou) {
+        int i;
+        mudou = 0;
+        for (i = 0; i < g->nnts; i++) {
+            if (g->nts[i].regra != NULL) {
+                if (bitset_unir(&g->nts[i].regra->follow, &g->nts[i].follow))
+                    mudou = 1;
+                if (propagar_follow_expr(g, g->nts[i].regra))
+                    mudou = 1;
+            }
+        }
+    }
 }
```

### 3.4. `src/ll1.c` (60 -> 145 linhas)

- **TODOs resolvidos:** `verificar_expr` e `ll1_verificar` (comentário `L20`: `TODO(aluno):` -> `Implementado:`).
- **Código removido:** stub `(void) reportar; (void) g; return 0;` em `ll1_verificar`.
- **Funções implementadas e adicionadas:**
  - `verificar_expr(const Gramatica *g, int nt, const Expr *e)` (`L45–131`, nova): verifica recursivamente todos os nós e aplica as condições LL(1):
    - Em `E_ALT`: (1) `FIRST` disjuntos dois a dois (erro); (2) no máximo uma alternativa anulável (erro); (3) para alternativa anulável, `FOLLOW` disjunto do `FIRST` das demais alternativas (erro).
    - Em `E_OPC` (`[ ]`) e `E_REP` (`{ }`): conteúdo anulável gera erro; interseção entre `FIRST` do conteúdo e `FOLLOW` gera apenas aviso (`eh_aviso = 1`, resolução gulosa).
  - `ll1_verificar(const Gramatica *g)` (`L135–145`): itera sobre todas as regras definidas somando apenas os erros retornados por `verificar_expr`.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/ll1.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/ll1.c	2026-11-03 10:21:20.042694300 -0400
@@ -17,7 +17,7 @@
  * em que o else fica com o if mais proximo, como em C.
  *
  * Fornecido: reportar (formata as mensagens).
- * TODO(aluno): verificar_expr e ll1_verificar.
+ * Implementado: verificar_expr e ll1_verificar.
  */
 #include <stdarg.h>
 #include <stdio.h>
@@ -42,19 +42,104 @@
     fputc('\n', stderr);
 }
 
-/* TODO(aluno): percorrer as regras e, para cada no E_ALT, E_OPC e E_REP,
- * verificar as condicoes do cabecalho. Use bitset_intersecao/bitset_vazio
- * e reporte com reportar(...), por exemplo:
- *
- *   reportar(g, nt, e, 0, &comum, "alternativas %d e %d comecam com", i+1, j+1);
- *
- * que imprime:
- *   expr.ebnf:7:10: erro: conflito LL(1) em stmt: alternativas 1 e 2 comecam com {ID}
- *
- * Retorne o numero de ERROS (avisos nao contam). */
+static int verificar_expr(const Gramatica *g, int nt, const Expr *e)
+{
+    int i, j, erros = 0;
+    Bitset comum;
+
+    if (e == NULL)
+        return 0;
+
+    bitset_iniciar(&comum, g->nterms);
+
+    switch (e->tipo) {
+    case E_ALT:
+        /* 1. FIRST das alternativas sao disjuntos dois a dois */
+        for (i = 0; i < e->nfilhos; i++) {
+            for (j = i + 1; j < e->nfilhos; j++) {
+                bitset_intersecao(&comum, &e->filhos[i]->first, &e->filhos[j]->first);
+                if (!bitset_vazio(&comum)) {
+                    reportar(g, nt, e, 0, &comum,
+                             "alternativas %d e %d comecam com", i + 1, j + 1);
+                    erros++;
+                }
+            }
+        }
+        /* 1 (segunda parte): no maximo uma alternativa e anulavel */
+        for (i = 0; i < e->nfilhos; i++) {
+            if (e->filhos[i]->anulavel) {
+                for (j = i + 1; j < e->nfilhos; j++) {
+                    if (e->filhos[j]->anulavel) {
+                        reportar(g, nt, e, 0, NULL,
+                                 "alternativas %d e %d sao ambas anulaveis",
+                                 i + 1, j + 1);
+                        erros++;
+                    }
+                }
+            }
+        }
+        /* 2. Se uma alternativa ai e anulavel, FOLLOW e disjunto dos FIRST das demais */
+        for (i = 0; i < e->nfilhos; i++) {
+            if (e->filhos[i]->anulavel) {
+                for (j = 0; j < e->nfilhos; j++) {
+                    if (i != j) {
+                        bitset_intersecao(&comum, &e->follow, &e->filhos[j]->first);
+                        if (!bitset_vazio(&comum)) {
+                            reportar(g, nt, e, 0, &comum,
+                                     "alternativa %d e anulavel e alternativa %d comeca com",
+                                     i + 1, j + 1);
+                            erros++;
+                        }
+                    }
+                }
+            }
+        }
+        break;
+
+    case E_OPC:
+    case E_REP: {
+        const char *nome = (e->tipo == E_OPC) ? "[ ]" : "{ }";
+        if (e->nfilhos > 0) {
+            /* 3 (primeira parte): o conteudo nao pode ser anulavel (ERRO) */
+            if (e->filhos[0]->anulavel) {
+                reportar(g, nt, e, 0, NULL,
+                         "conteudo de %s e anulavel", nome);
+                erros++;
+            }
+            /* 3 (segunda parte): FIRST e FOLLOW disjuntos (AVISO - resolvido de forma gulosa) */
+            bitset_intersecao(&comum, &e->filhos[0]->first, &e->follow);
+            if (!bitset_vazio(&comum)) {
+                reportar(g, nt, e, 1, &comum,
+                         "FIRST e FOLLOW de %s se intersectam (resolvido de forma gulosa) em",
+                         nome);
+            }
+        }
+        break;
+    }
+
+    default:
+        break;
+    }
+
+    bitset_liberar(&comum);
+
+    /* Verifica recursivamente todos os filhos */
+    for (i = 0; i < e->nfilhos; i++)
+        erros += verificar_expr(g, nt, e->filhos[i]);
+
+    return erros;
+}
+
+/* Percorre as regras e verifica as condicoes LL(1).
+ * Retorna o numero de ERROS (avisos nao contam). */
 int ll1_verificar(const Gramatica *g)
 {
-    (void) reportar;
-    (void) g;
-    return 0;
+    int i, erros = 0;
+
+    for (i = 0; i < g->nnts; i++) {
+        if (g->nts[i].regra != NULL)
+            erros += verificar_expr(g, i, g->nts[i].regra);
+    }
+
+    return erros;
 }
```

### 3.5. `src/codegen.c` (832 -> 1392 linhas)

- **TODOs resolvidos:** `gen_expr`, `gen_casamento_regex` e `gen_token_de_arquivo` (comentário `L18`: `TODO(aluno):` -> `Implementado:`).
- **Implementação de `gen_expr` (`L273–356`):** adiciona guarda `if (e == NULL) return;`, remove o `default:` stub (`/* TODO(aluno): construcao ainda nao traduzida */`) e gera código para `E_VAZIO`, `E_SEQ`, `E_OPC` (`if`), `E_REP` (`while`) e `E_ALT` (`if` / `else if` / `else` com ramo anulável ou `emit_erro(em, &e->first)`).
- **Motor Regex NFA->DFA e `gen_casamento_regex` (`L362–846`):**
  - Define constantes e tipos `MAX_NFA_STATES` (`512`), `MAX_DFA_STATES` (`128`), `NFAEstado`, `Frag`, `NFABuilder` e `DFAEstado` (`L362–387`).
  - Adiciona construtor de AFN de Thompson (`set_add`, `set_has`, `nfa_novo_estado`, `nfa_char`, `nfa_concat`, `nfa_alt`, `nfa_star`, `nfa_plus`, `nfa_opt`), parser recursivo de regex (`parse_escape`, `parse_class`, `parse_base`, `parse_factor`, `parse_term`, `parse_regex_expr`), determinização (`epsilon_closure`) e compactador de transições (`emitir_condicao_faixas`) (`L389–709`).
  - `gen_casamento_regex` (`L716–846`): substitui o stub por parsing da regex, construção do DFA por subconjuntos (com erro via `diag_erro` para regex inválida ou estouro de `MAX_DFA_STATES`) e emissão da função `static size_t <nome>(const char *s)` baseada em `switch (estado)` e `static const int aceita[...]`.
- **Leitura de `--tokens` em `gen_token_de_arquivo` (`L859–912`):** substitui o stub `"opcao --tokens ainda nao implementada"` por leitura via `fgets` + `sscanf` de linhas no formato `Token: tipo = <N>, lexema = '<L>', linha = <ln>`, ignorando linhas em branco, preenchendo `t.coluna = 1` quando `!microc` e reportando linha malformada com `EXIT_FAILURE`.
- **Correção de vazamento de recursos em saídas antecipadas (`atexit(limpar_recursos)`):**
  - Adiciona `static FILE *arquivo_entrada = NULL;` em `rt_estado` (`L925`).
  - Adiciona `gerar_limpar_recursos(FILE *f, int microc)` (`L1126–1142`), chamada em `gerar_c` (`L1366`), que emite `static void limpar_recursos(void)` para fechar `arquivo_tokens`, finalizar o scanner (`scanner_finalizar()` no modo Micro C) ou liberar `fonte` (no modo próprio) e fechar `arquivo_entrada` (se diferente de `stdin`).
  - Em `gerar_main` (`L1281–1322`), atribui `arquivo_entrada = entrada;` (`L1312`), registra `atexit(limpar_recursos);` (`L1314`) e remove o bloco de limpeza manual que existia apenas no fim de `main` (`esqueleto` L755–761), garantindo limpeza mesmo quando erros léxicos/sintáticos chamam `exit(EXIT_FAILURE)`.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/codegen.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/codegen.c	2026-11-03 10:21:20.010656900 -0400
@@ -15,7 +15,7 @@
  * as primitivas, o lexico (exceto o reconhecimento das expressoes
  * regulares) e a traducao de terminais e nao terminais.
  *
- * TODO(aluno):
+ * Implementado:
  *   - gen_expr: traducao de sequencia, alternativa, [ ] e { }
  *     (esquema da secao 4 do enunciado);
  *   - gen_casamento_regex: converter uma expressao regular de TOKENS em
@@ -272,6 +272,8 @@
 
 static void gen_expr(Emissor *em, const Gramatica *g, const Expr *e)
 {
+    if (e == NULL)
+        return;
 
     switch (e->tipo) {
     case E_TERM:
@@ -280,36 +282,432 @@
     case E_NAOTERM:
         emit(em, "parse_%s();", g->nts[e->simbolo].nome);
         break;
-    /*
-     * TODO(aluno): traduzir as demais construcoes (secao 4):
-     *
-     *   E_SEQ   a1 a2 ... an   ->  gen_expr de cada filho, em ordem
-     *   E_ALT   a1 | ... | an  ->  if (FIRST(a1)) {...} else if ... else erro
-     *   E_OPC   [ a ]          ->  if (FIRST(a)) { ... }
-     *   E_REP   { a }          ->  while (FIRST(a)) { ... }
-     *   E_VAZIO                ->  nada
-     *
-     * Ferramentas disponiveis neste arquivo:
-     *   emit(em, fmt, ...)                 uma linha indentada
-     *   em->nivel++ / em->nivel--          indentacao dos blocos
-     *   emit_teste(em, "if (", g, &x->first, ") {")
-     *   emit_erro(em, &e->first)           erro_sintatico com os esperados
-     * Os conjuntos FIRST de cada no foram calculados em conjuntos.c.
-     * Uma alternativa anulavel nao tem teste: ela fica no else final,
-     * no lugar do erro.
-     */
-    default:
-        emit(em, "/* TODO(aluno): construcao ainda nao traduzida */");
-        (void) emit_teste;
-        (void) emit_erro;
+    case E_VAZIO:
+        break;
+    case E_SEQ: {
+        int i;
+        for (i = 0; i < e->nfilhos; i++)
+            gen_expr(em, g, e->filhos[i]);
         break;
     }
+    case E_OPC:
+        if (e->nfilhos > 0) {
+            emit_teste(em, "if (", g, &e->filhos[0]->first, ") {");
+            em->nivel++;
+            gen_expr(em, g, e->filhos[0]);
+            em->nivel--;
+            emit(em, "}");
+        }
+        break;
+    case E_REP:
+        if (e->nfilhos > 0) {
+            emit_teste(em, "while (", g, &e->filhos[0]->first, ") {");
+            em->nivel++;
+            gen_expr(em, g, e->filhos[0]);
+            em->nivel--;
+            emit(em, "}");
+        }
+        break;
+    case E_ALT: {
+        int i, primeiro = 1, idx_anulavel = -1;
+        for (i = 0; i < e->nfilhos; i++) {
+            if (e->filhos[i]->anulavel) {
+                idx_anulavel = i;
+                break;
+            }
+        }
+        for (i = 0; i < e->nfilhos; i++) {
+            if (i == idx_anulavel)
+                continue;
+            if (primeiro) {
+                emit_teste(em, "if (", g, &e->filhos[i]->first, ") {");
+                primeiro = 0;
+            } else {
+                emit_teste(em, "} else if (", g, &e->filhos[i]->first, ") {");
+            }
+            em->nivel++;
+            gen_expr(em, g, e->filhos[i]);
+            em->nivel--;
+        }
+        if (idx_anulavel >= 0) {
+            if (!primeiro) {
+                emit(em, "} else {");
+                em->nivel++;
+                gen_expr(em, g, e->filhos[idx_anulavel]);
+                em->nivel--;
+                emit(em, "}");
+            } else {
+                gen_expr(em, g, e->filhos[idx_anulavel]);
+            }
+        } else {
+            if (!primeiro) {
+                emit(em, "} else {");
+                em->nivel++;
+                emit_erro(em, &e->first);
+                em->nivel--;
+                emit(em, "}");
+            } else {
+                emit_erro(em, &e->first);
+            }
+        }
+        break;
+    }
+    }
 }
 
 /* ------------------------------------------------------------------ */
 /* Expressoes regulares de TOKENS (modo proprio)                      */
 /* ------------------------------------------------------------------ */
 
+#define MAX_NFA_STATES 512
+#define MAX_DFA_STATES 128
+
+typedef struct {
+    int trans_tipo; /* 0 = CHAR, 1 = EPSILON */
+    int out1;
+    int out2;
+    unsigned char match[256];
+} NFAEstado;
+
+typedef struct {
+    int start;
+    int accept;
+} Frag;
+
+typedef struct {
+    NFAEstado estados[MAX_NFA_STATES];
+    int nestados;
+    int erro;
+} NFABuilder;
+
+typedef struct {
+    unsigned char nfa_set[64];
+    int trans[256];
+    int aceita;
+} DFAEstado;
+
+static void set_add(unsigned char *set, int s)
+{
+    set[s / 8] |= (unsigned char) (1 << (s % 8));
+}
+
+static int set_has(const unsigned char *set, int s)
+{
+    return (set[s / 8] & (1 << (s % 8))) != 0;
+}
+
+static int nfa_novo_estado(NFABuilder *b, int tipo)
+{
+    int s;
+    if (b->nestados >= MAX_NFA_STATES) {
+        b->erro = 1;
+        return 0;
+    }
+    s = b->nestados++;
+    b->estados[s].trans_tipo = tipo;
+    b->estados[s].out1 = -1;
+    b->estados[s].out2 = -1;
+    memset(b->estados[s].match, 0, 256);
+    return s;
+}
+
+static Frag nfa_char(NFABuilder *b, const unsigned char *match)
+{
+    Frag f;
+    f.start = nfa_novo_estado(b, 0);
+    f.accept = nfa_novo_estado(b, 1);
+    memcpy(b->estados[f.start].match, match, 256);
+    b->estados[f.start].out1 = f.accept;
+    return f;
+}
+
+static Frag nfa_concat(NFABuilder *b, Frag f1, Frag f2)
+{
+    Frag f;
+    b->estados[f1.accept].out1 = f2.start;
+    f.start = f1.start;
+    f.accept = f2.accept;
+    return f;
+}
+
+static Frag nfa_alt(NFABuilder *b, Frag f1, Frag f2)
+{
+    Frag f;
+    f.start = nfa_novo_estado(b, 1);
+    f.accept = nfa_novo_estado(b, 1);
+    b->estados[f.start].out1 = f1.start;
+    b->estados[f.start].out2 = f2.start;
+    b->estados[f1.accept].out1 = f.accept;
+    b->estados[f2.accept].out1 = f.accept;
+    return f;
+}
+
+static Frag nfa_star(NFABuilder *b, Frag f1)
+{
+    Frag f;
+    f.start = nfa_novo_estado(b, 1);
+    f.accept = nfa_novo_estado(b, 1);
+    b->estados[f.start].out1 = f1.start;
+    b->estados[f.start].out2 = f.accept;
+    b->estados[f1.accept].out1 = f1.start;
+    b->estados[f1.accept].out2 = f.accept;
+    return f;
+}
+
+static Frag nfa_plus(NFABuilder *b, Frag f1)
+{
+    Frag f;
+    f.start = nfa_novo_estado(b, 1);
+    f.accept = nfa_novo_estado(b, 1);
+    b->estados[f.start].out1 = f1.start;
+    b->estados[f1.accept].out1 = f1.start;
+    b->estados[f1.accept].out2 = f.accept;
+    return f;
+}
+
+static Frag nfa_opt(NFABuilder *b, Frag f1)
+{
+    Frag f;
+    f.start = nfa_novo_estado(b, 1);
+    f.accept = nfa_novo_estado(b, 1);
+    b->estados[f.start].out1 = f1.start;
+    b->estados[f.start].out2 = f.accept;
+    b->estados[f1.accept].out1 = f.accept;
+    return f;
+}
+
+static int parse_escape(const char **ps)
+{
+    char c = **ps;
+    if (c == '\0')
+        return '\\';
+    (*ps)++;
+    switch (c) {
+    case 'n': return '\n';
+    case 't': return '\t';
+    case 'r': return '\r';
+    case 'a': return '\a';
+    case 'b': return '\b';
+    case 'f': return '\f';
+    case 'v': return '\v';
+    case '0': return '\0';
+    default:  return (unsigned char) c;
+    }
+}
+
+static void parse_class(const char **ps, unsigned char *match, int *erro)
+{
+    int neg = 0;
+    memset(match, 0, 256);
+    if (**ps == '^') {
+        neg = 1;
+        (*ps)++;
+    }
+    while (**ps != ']' && **ps != '\0') {
+        int c1;
+        if (**ps == '\\') {
+            (*ps)++;
+            c1 = parse_escape(ps);
+        } else {
+            c1 = (unsigned char) **ps;
+            (*ps)++;
+        }
+        if (**ps == '-' && *(*ps + 1) != ']' && *(*ps + 1) != '\0') {
+            int c2, k;
+            (*ps)++; /* consome '-' */
+            if (**ps == '\\') {
+                (*ps)++;
+                c2 = parse_escape(ps);
+            } else {
+                c2 = (unsigned char) **ps;
+                (*ps)++;
+            }
+            if (c1 <= c2) {
+                for (k = c1; k <= c2; k++)
+                    match[k] = 1;
+            } else {
+                for (k = c2; k <= c1; k++)
+                    match[k] = 1;
+            }
+        } else {
+            match[c1] = 1;
+        }
+    }
+    if (**ps == ']') {
+        (*ps)++;
+    } else {
+        *erro = 1;
+    }
+    if (neg) {
+        int k;
+        for (k = 1; k < 256; k++)
+            match[k] = (unsigned char) (!match[k]);
+        match[0] = 0;
+    }
+}
+
+static Frag parse_regex_expr(NFABuilder *b, const char **ps);
+
+static Frag parse_base(NFABuilder *b, const char **ps)
+{
+    unsigned char m[256];
+    Frag f;
+    memset(&f, 0, sizeof(f));
+
+    if (**ps == '(') {
+        (*ps)++;
+        f = parse_regex_expr(b, ps);
+        if (**ps == ')')
+            (*ps)++;
+        else
+            b->erro = 1;
+        return f;
+    }
+    if (**ps == '.') {
+        (*ps)++;
+        memset(m, 1, 256);
+        m[0] = 0;
+        m['\n'] = 0;
+        return nfa_char(b, m);
+    }
+    if (**ps == '[') {
+        (*ps)++;
+        parse_class(ps, m, &b->erro);
+        return nfa_char(b, m);
+    }
+    if (**ps == '\\') {
+        int c;
+        (*ps)++;
+        c = parse_escape(ps);
+        memset(m, 0, 256);
+        m[c] = 1;
+        return nfa_char(b, m);
+    }
+    if (**ps != '\0' && **ps != '|' && **ps != ')' && **ps != '*' && **ps != '+' && **ps != '?') {
+        int c = (unsigned char) **ps;
+        (*ps)++;
+        memset(m, 0, 256);
+        m[c] = 1;
+        return nfa_char(b, m);
+    }
+    b->erro = 1;
+    return f;
+}
+
+static Frag parse_factor(NFABuilder *b, const char **ps)
+{
+    Frag f = parse_base(b, ps);
+    if (b->erro)
+        return f;
+    while (**ps == '*' || **ps == '+' || **ps == '?') {
+        char op = **ps;
+        (*ps)++;
+        if (op == '*')
+            f = nfa_star(b, f);
+        else if (op == '+')
+            f = nfa_plus(b, f);
+        else if (op == '?')
+            f = nfa_opt(b, f);
+    }
+    return f;
+}
+
+static Frag parse_term(NFABuilder *b, const char **ps)
+{
+    Frag f;
+    int primeiro = 1;
+    memset(&f, 0, sizeof(f));
+
+    while (**ps != '\0' && **ps != '|' && **ps != ')') {
+        Frag f2 = parse_factor(b, ps);
+        if (b->erro)
+            return f;
+        if (primeiro) {
+            f = f2;
+            primeiro = 0;
+        } else {
+            f = nfa_concat(b, f, f2);
+        }
+    }
+    if (primeiro) {
+        f.start = nfa_novo_estado(b, 1);
+        f.accept = nfa_novo_estado(b, 1);
+        b->estados[f.start].out1 = f.accept;
+    }
+    return f;
+}
+
+static Frag parse_regex_expr(NFABuilder *b, const char **ps)
+{
+    Frag f = parse_term(b, ps);
+    if (b->erro)
+        return f;
+    while (**ps == '|') {
+        Frag f2;
+        (*ps)++;
+        f2 = parse_term(b, ps);
+        if (b->erro)
+            return f;
+        f = nfa_alt(b, f, f2);
+    }
+    return f;
+}
+
+static void epsilon_closure(NFABuilder *b, unsigned char *set)
+{
+    int pilha[MAX_NFA_STATES], topo = 0, i;
+    for (i = 0; i < b->nestados; i++) {
+        if (set_has(set, i))
+            pilha[topo++] = i;
+    }
+    while (topo > 0) {
+        int u = pilha[--topo];
+        if (b->estados[u].trans_tipo == 1) {
+            int v1 = b->estados[u].out1;
+            int v2 = b->estados[u].out2;
+            if (v1 >= 0 && v1 < b->nestados && !set_has(set, v1)) {
+                set_add(set, v1);
+                pilha[topo++] = v1;
+            }
+            if (v2 >= 0 && v2 < b->nestados && !set_has(set, v2)) {
+                set_add(set, v2);
+                pilha[topo++] = v2;
+            }
+        }
+    }
+}
+
+static void emitir_condicao_faixas(FILE *f, const unsigned char *match)
+{
+    int c, r_start = -1, primeiro = 1;
+    for (c = 1; c <= 256; c++) {
+        if (c < 256 && match[c]) {
+            if (r_start < 0)
+                r_start = c;
+        } else {
+            if (r_start >= 0) {
+                int r_end = c - 1;
+                if (!primeiro)
+                    fputs(" || ", f);
+                if (r_start == r_end) {
+                    fprintf(f, "c == %d", r_start);
+                } else if (r_end == 255) {
+                    if (r_start == 0)
+                        fputs("1", f);
+                    else
+                        fprintf(f, "c >= %d", r_start);
+                } else if (r_start == 0) {
+                    fprintf(f, "c <= %d", r_end);
+                } else {
+                    fprintf(f, "(c >= %d && c <= %d)", r_start, r_end);
+                }
+                primeiro = 0;
+                r_start = -1;
+            }
+        }
+    }
+}
+
 /* Emite a funcao
  *     static size_t <nome>(const char *s)
  * que devolve o comprimento do MAIOR prefixo de s reconhecido pela
@@ -317,20 +715,133 @@
  * Retorna 0 se a expressao for valida (senao reporte com diag_erro). */
 static int gen_casamento_regex(FILE *f, const char *nome, const char *regex)
 {
-    /* TODO(aluno): converter a expressao regular em automato finito
-     * deterministico (por exemplo: analisar a expressao, construir o AFN
-     * de Thompson e determiniza-lo pela construcao de subconjuntos) e
-     * emitir o automato como codigo C: um switch sobre o estado, com as
-     * transicoes por faixas de caracteres, guardando a ultima posicao em
-     * que o automato passou por um estado final. Subconjunto minimo:
-     * concatenacao, |, *, +, ?, parenteses, classes [a-z] e [^...], o
-     * ponto e escapes como \n, \t, \\ e \/.
-     *
-     * O stub abaixo nao reconhece nada. */
+    NFABuilder b;
+    Frag frag;
+    const char *p;
+    DFAEstado dfa[MAX_DFA_STATES];
+    int ndfa = 0, i, c, u, k;
+
+    if (regex == NULL || *regex == '\0') {
+        fprintf(f, "static size_t %s(const char *s)\n{\n    (void) s;\n    return 0;\n}\n\n", nome);
+        return 0;
+    }
+
+    memset(&b, 0, sizeof(b));
+    p = regex;
+    frag = parse_regex_expr(&b, &p);
+    if (b.erro || *p != '\0') {
+        diag_erro(0, 0, "expressao regular invalida '%s'", regex);
+        return -1;
+    }
+
+    /* Constroi o DFA a partir do NFA */
+    memset(&dfa[0], 0, sizeof(DFAEstado));
+    set_add(dfa[0].nfa_set, frag.start);
+    epsilon_closure(&b, dfa[0].nfa_set);
+    dfa[0].aceita = set_has(dfa[0].nfa_set, frag.accept);
+    for (c = 0; c < 256; c++)
+        dfa[0].trans[c] = -1;
+    ndfa = 1;
+
+    for (i = 0; i < ndfa; i++) {
+        for (c = 1; c < 256; c++) {
+            unsigned char dest_set[64];
+            int has_any = 0, d;
+            memset(dest_set, 0, sizeof(dest_set));
+
+            for (u = 0; u < b.nestados; u++) {
+                if (set_has(dfa[i].nfa_set, u)) {
+                    if (b.estados[u].trans_tipo == 0 && b.estados[u].match[c]) {
+                        int v = b.estados[u].out1;
+                        if (v >= 0) {
+                            set_add(dest_set, v);
+                            has_any = 1;
+                        }
+                    }
+                }
+            }
+            if (!has_any) {
+                dfa[i].trans[c] = -1;
+                continue;
+            }
+            epsilon_closure(&b, dest_set);
+            d = -1;
+            for (k = 0; k < ndfa; k++) {
+                if (memcmp(dfa[k].nfa_set, dest_set, sizeof(dest_set)) == 0) {
+                    d = k;
+                    break;
+                }
+            }
+            if (d < 0) {
+                if (ndfa >= MAX_DFA_STATES) {
+                    diag_erro(0, 0, "automato da expressao regular '%s' excedeu o limite de estados", regex);
+                    return -1;
+                }
+                d = ndfa++;
+                memset(&dfa[d], 0, sizeof(DFAEstado));
+                memcpy(dfa[d].nfa_set, dest_set, sizeof(dest_set));
+                dfa[d].aceita = set_has(dfa[d].nfa_set, frag.accept);
+                for (k = 0; k < 256; k++)
+                    dfa[d].trans[k] = -1;
+            }
+            dfa[i].trans[c] = d;
+        }
+    }
+
+    /* Emissao da funcao em codigo C */
     fprintf(f, "static size_t %s(const char *s)\n{\n", nome);
-    fputs("    /* TODO(aluno): automato para ", f);
-    emitir_comentario(f, regex);
-    fputs(" */\n    (void) s;\n    return 0;\n}\n\n", f);
+    fprintf(f, "    size_t i = 0, melhor = 0;\n");
+    fprintf(f, "    int estado = 0;\n");
+    fprintf(f, "    static const int aceita[%d] = {", ndfa);
+    for (i = 0; i < ndfa; i++)
+        fprintf(f, "%s%d", i > 0 ? ", " : " ", dfa[i].aceita);
+    fprintf(f, " };\n");
+    fprintf(f, "    if (aceita[0])\n        melhor = 0;\n");
+    fprintf(f, "    while (s[i] != '\\0') {\n");
+    fprintf(f, "        unsigned char c = (unsigned char) s[i];\n");
+    fprintf(f, "        switch (estado) {\n");
+
+    for (i = 0; i < ndfa; i++) {
+        int alvos[MAX_DFA_STATES], nalvos = 0;
+        for (c = 1; c < 256; c++) {
+            int t = dfa[i].trans[c];
+            if (t >= 0) {
+                int ja = 0;
+                for (k = 0; k < nalvos; k++) {
+                    if (alvos[k] == t) { ja = 1; break; }
+                }
+                if (!ja)
+                    alvos[nalvos++] = t;
+            }
+        }
+        if (nalvos == 0) {
+            fprintf(f, "        case %d:\n            goto fim;\n", i);
+        } else {
+            fprintf(f, "        case %d:\n", i);
+            for (k = 0; k < nalvos; k++) {
+                int target = alvos[k];
+                unsigned char match_alvo[256];
+                memset(match_alvo, 0, 256);
+                for (c = 1; c < 256; c++) {
+                    if (dfa[i].trans[c] == target)
+                        match_alvo[c] = 1;
+                }
+                if (k == 0)
+                    fputs("            if (", f);
+                else
+                    fputs(" else if (", f);
+                emitir_condicao_faixas(f, match_alvo);
+                fprintf(f, ") {\n                estado = %d;\n            }", target);
+            }
+            fputs(" else {\n                goto fim;\n            }\n            break;\n", f);
+        }
+    }
+
+    fprintf(f, "        default:\n            goto fim;\n        }\n");
+    fprintf(f, "        i++;\n");
+    fprintf(f, "        if (aceita[estado])\n            melhor = i;\n");
+    fprintf(f, "    }\nfim:\n    return melhor;\n}\n\n");
+
     return 0;
 }
 
@@ -347,23 +858,57 @@
  * Ao chegar ao fim do arquivo devolve um token TOKEN_FIM. */
 static void gen_token_de_arquivo(FILE *f, int microc)
 {
-    /* TODO(aluno): emitir a leitura real com fgets + sscanf (formato
-     * acima). Linhas em branco sao ignoradas; uma linha malformada deve
-     * ser reportada com o numero da linha do arquivo de tokens. */
-    static const char *const linhas[] = {
+    static const char *const linhas_antes[] = {
+        "static int linha_arq_tokens = 0;",
+        "",
         "static Token token_de_arquivo(void)",
         "{",
+        "    char buf[1024];",
         "    Token t;",
         "    memset(&t, 0, sizeof t);",
-        "    fprintf(stderr, \"opcao --tokens ainda nao implementada\\n\");",
-        "    exit(EXIT_FAILURE);",
+        "    while (fgets(buf, sizeof buf, arquivo_tokens) != NULL) {",
+        "        char *p = buf, *lex_inicio, *lex_fim, *lin_str;",
+        "        int tipo_val, linha_val;",
+        "        linha_arq_tokens++;",
+        "        while (*p == ' ' || *p == '\\t' || *p == '\\r' || *p == '\\n') p++;",
+        "        if (*p == '\\0') continue;",
+        "        if (strncmp(p, \"Token:\", 6) != 0) goto malformado;",
+        "        p = strstr(p + 6, \"tipo =\");",
+        "        if (p == NULL) goto malformado;",
+        "        if (sscanf(p + 6, \"%d\", &tipo_val) != 1) goto malformado;",
+        "        p = strstr(p, \"lexema = '\");",
+        "        if (p == NULL) goto malformado;",
+        "        lex_inicio = p + 10;",
+        "        lin_str = strstr(lex_inicio, \"', linha =\");",
+        "        if (lin_str == NULL) goto malformado;",
+        "        lex_fim = lin_str;",
+        "        if (sscanf(lin_str + 10, \"%d\", &linha_val) != 1) goto malformado;",
+        "        t.tipo = tipo_val;",
+        "        t.linha = linha_val;",
+        NULL
+    };
+    static const char *const linhas_depois[] = {
+        "        {",
+        "            size_t tam = (size_t)(lex_fim - lex_inicio);",
+        "            if (tam >= sizeof t.lexema) tam = sizeof t.lexema - 1;",
+        "            memcpy(t.lexema, lex_inicio, tam);",
+        "            t.lexema[tam] = '\\0';",
+        "        }",
+        "        return t;",
+        "    malformado:",
+        "        fprintf(stderr, \"linha %d do arquivo de tokens malformada\\n\", linha_arq_tokens);",
+        "        exit(EXIT_FAILURE);",
+        "    }",
+        "    t.tipo = TOKEN_FIM;",
         "    return t;",
         "}",
         "",
         NULL
     };
-    (void) microc;
-    emit_linhas(f, linhas);
+    emit_linhas(f, linhas_antes);
+    if (!microc)
+        fputs("        t.coluna = 1;\n", f);
+    emit_linhas(f, linhas_depois);
 }
 
 /* ------------------------------------------------------------------ */
@@ -377,6 +922,7 @@
     "static int imprimir_arvore = 0;    /* opcao --tree */",
     "static int nivel_arvore = 0;",
     "static FILE *arquivo_tokens = NULL; /* opcao --tokens */",
+    "static FILE *arquivo_entrada = NULL;",
     "",
     "static Token token_de_arquivo(void);",
     "",
@@ -577,6 +1123,24 @@
     fputs("    default: return \"token desconhecido\";\n    }\n}\n\n", f);
 }
 
+static void gerar_limpar_recursos(FILE *f, int microc)
+{
+    fputs("static void limpar_recursos(void)\n{\n", f);
+    fputs("    if (arquivo_tokens != NULL) {\n", f);
+    fputs("        fclose(arquivo_tokens);\n", f);
+    fputs("        arquivo_tokens = NULL;\n", f);
+    fputs("    } else {\n", f);
+    if (microc)
+        fputs("        scanner_finalizar();\n", f);
+    else
+        fputs("        if (fonte != NULL) {\n            free(fonte);\n            fonte = NULL;\n        }\n", f);
+    fputs("        if (arquivo_entrada != NULL && arquivo_entrada != stdin) {\n", f);
+    fputs("            fclose(arquivo_entrada);\n", f);
+    fputs("            arquivo_entrada = NULL;\n", f);
+    fputs("        }\n", f);
+    fputs("    }\n}\n\n", f);
+}
+
 static void gerar_posicao_e_avancar(FILE *f, int microc)
 {
     fputs("static void escrever_posicao(void)\n{\n", f);
@@ -745,20 +1309,15 @@
         fputs("        scanner_iniciar(entrada);\n", f);
     else
         fputs("        fonte = ler_tudo(entrada);\n", f);
+    fputs("        arquivo_entrada = entrada;\n", f);
     fputs("    }\n\n", f);
+    fputs("    atexit(limpar_recursos);\n\n", f);
     fputs("    avancar();\n", f);
     fprintf(f, "    parse_%s();\n", g->nts[g->inicial].nome);
     fputs("    if (tok.tipo != TOKEN_FIM) {\n", f);
     fputs("        fim[0] = TOKEN_FIM;\n        fim[1] = -1;\n", f);
     fputs("        erro_sintatico(fim);\n    }\n", f);
     fputs("    printf(\"entrada aceita\\n\");\n\n", f);
-    fputs("    if (arquivo_tokens != NULL) {\n        fclose(arquivo_tokens);\n", f);
-    fputs("    } else {\n", f);
-    if (op->microc)
-        fputs("        scanner_finalizar();\n", f);
-    else
-        fputs("        free(fonte);\n", f);
-    fputs("        if (entrada != stdin)\n            fclose(entrada);\n    }\n", f);
     fputs("    return 0;\n}\n", f);
 }
 
@@ -804,6 +1363,7 @@
     emit_linhas(f, rt_estado);
     if (!op->microc)
         erros += gerar_lexico(f, g);
+    gerar_limpar_recursos(f, op->microc);
     gerar_nome_token(f, g);
     gerar_posicao_e_avancar(f, op->microc);
     emit_linhas(f, rt_primitivas);
```

### 3.6. `src/microc_mapa.c` (91 -> 173 linhas)

- **TODO resolvido:** `microc_carregar_tokens_h` (comentário `L13`: `TODO(aluno):` -> `Implementado:`).
- **Código removido:** stub que emitia `diag_aviso` e retornava `-1`.
- **Implementação (`L60–154`):** evita recarga se `nnomes > 0`, lê o arquivo com `ler_arquivo(caminho)`, localiza `enum`, `'{'` e `'}'`, ignora espaços, comentários `/* ... */` e `// ...`, extrai cada identificador de token via `adicionar_nome`, e pula eventuais valores explícitos (`= <valor>`) até `','` ou `'}'`.

Diff completo (`diff -u`):

```diff
--- Trabalho_2-esqueleto/src/microc_mapa.c	2026-10-19 18:56:40.000000000 -0400
+++ Trabalho_2-pronto/src/microc_mapa.c	2026-11-03 10:21:20.051368100 -0400
@@ -10,7 +10,7 @@
  *
  * Se o seu tokens.h do TP1 usar outros nomes, ajuste a tabela.
  *
- * TODO(aluno): implementar microc_carregar_tokens_h.
+ * Implementado: implementar microc_carregar_tokens_h.
  */
 #include <ctype.h>
 #include <stdio.h>
@@ -54,21 +54,103 @@
     nomes[nnomes++] = xstrndup(s, n);
 }
 
-/* TODO(aluno): abrir o arquivo (ler_arquivo ajuda), localizar a
- * enumeracao "typedef enum { ... } TokenType;" e chamar adicionar_nome
- * para cada identificador da lista, ignorando comentarios e valores
- * explicitos ("X = 3"). Retorne 0 em caso de sucesso.
- * Enquanto nao implementada, a verificacao dos nomes e pulada. */
+/* Abre o arquivo de tokens, localiza a enumeracao
+ * "typedef enum { ... } TokenType;" e adiciona cada identificador a lista.
+ * Ignora comentarios e valores explicitos ("X = 3"). Retorna 0 em caso de sucesso. */
 int microc_carregar_tokens_h(const char *caminho)
 {
-    static int avisado = 0;
-    (void) adicionar_nome;
-    if (!avisado) {
-        diag_aviso(0, 0, "microc_carregar_tokens_h ainda nao implementado: nomes "
-                   "de %s nao verificados", caminho ? caminho : "tokens.h");
-        avisado = 1;
+    char *fonte, *p, *fim;
+
+    if (nnomes > 0)
+        return 0;
+
+    if (caminho == NULL)
+        return -1;
+
+    fonte = ler_arquivo(caminho);
+    if (fonte == NULL)
+        return -1;
+
+    p = strstr(fonte, "enum");
+    if (p == NULL) {
+        free(fonte);
+        return -1;
+    }
+
+    p = strchr(p, '{');
+    if (p == NULL) {
+        free(fonte);
+        return -1;
+    }
+
+    fim = strchr(p, '}');
+    if (fim == NULL) {
+        free(fonte);
+        return -1;
+    }
+
+    p++; /* passa '{' */
+
+    while (p < fim) {
+        /* Pula espacos em branco */
+        if (isspace((unsigned char) *p)) {
+            p++;
+            continue;
+        }
+
+        /* Pula comentarios estilo C */
+        if (p[0] == '/' && p[1] == '*') {
+            p += 2;
+            while (p < fim && !(p[0] == '*' && p[1] == '/'))
+                p++;
+            if (p < fim)
+                p += 2;
+            continue;
+        }
+
+        /* Pula comentarios de linha: // ... */
+        if (p[0] == '/' && p[1] == '/') {
+            p += 2;
+            while (p < fim && *p != '\n')
+                p++;
+            continue;
+        }
+
+        /* Identificador (nome do token) */
+        if (isalpha((unsigned char) *p) || *p == '_') {
+            const char *inicio = p;
+            while (p < fim && (isalnum((unsigned char) *p) || *p == '_'))
+                p++;
+            adicionar_nome(inicio, (size_t) (p - inicio));
+
+            /* Pula possivel valor explicito '= <valor>' antes da virgula */
+            while (p < fim && *p != ',' && *p != '}') {
+                if (isspace((unsigned char) *p)) {
+                    p++;
+                } else if (p[0] == '/' && p[1] == '*') {
+                    p += 2;
+                    while (p < fim && !(p[0] == '*' && p[1] == '/'))
+                        p++;
+                    if (p < fim)
+                        p += 2;
+                } else if (p[0] == '/' && p[1] == '/') {
+                    p += 2;
+                    while (p < fim && *p != '\n')
+                        p++;
+                } else {
+                    p++;
+                }
+            }
+            if (p < fim && *p == ',')
+                p++;
+            continue;
+        }
+
+        p++;
     }
-    return -1;
+
+    free(fonte);
+    return 0;
 }
 
 int microc_token_existe(const char *nome)
```

---

## 4. Novos testes (`json` e `txt`), arquivos `TEMP*.md` e artefatos de build

### 4.1. Novos testes de JSON (`testes/gramaticas/json.ebnf`, `testes/esperado/json.gerador` e `testes/programas/json/*`)

#### `testes/gramaticas/json.ebnf`

```ebnf
(* Gramatica de JSON para o modo proprio *)
TOKENS
  STRING   = /"[^"\n]*"/ ;
  NUMBER   = /-?[0-9]+/ ;
  BOOLEAN  = /true|false/ ;
  NULO     = /null/ ;
  SKIP     = /[ \t\r\n]+/ ;

RULES
  json   = valor ;
  valor  = objeto | array | STRING | NUMBER | BOOLEAN | NULO ;
  objeto = "{" [ par { "," par } ] "}" ;
  par    = STRING ":" valor ;
  array  = "[" [ valor { "," valor } ] "]" ;

```

#### `testes/esperado/json.gerador`

```text
NAO TERMINAL  ANULAVEL  FIRST / FOLLOW
json          nao       FIRST  = {STRING, NUMBER, BOOLEAN, NULO, '{', '['}
                        FOLLOW = {$}
valor         nao       FIRST  = {STRING, NUMBER, BOOLEAN, NULO, '{', '['}
                        FOLLOW = {$, ',', '}', ']'}
objeto        nao       FIRST  = {'{'}
                        FOLLOW = {$, ',', '}', ']'}
array         nao       FIRST  = {'['}
                        FOLLOW = {$, ',', '}', ']'}
par           nao       FIRST  = {STRING}
                        FOLLOW = {',', '}'}
status 0
```

#### `testes/programas/json/aceito_1.json`

```json
{
    "nome": "VScode",
    "versao": 2,
    "ativo": true
}
```

*(Nota: o arquivo original não possui quebra de linha ao final.)*

#### `testes/programas/json/aceito_1.esperado`

```text
entrada aceita
status 0
```

#### `testes/programas/json/aceito_2.json`

```json
[
    1,
    2,
    [
        3,
        4
    ],
    {
        "item": null
    }
]
```

*(Nota: o arquivo original não possui quebra de linha ao final.)*

#### `testes/programas/json/aceito_2.esperado`

```text
entrada aceita
status 0
```

#### `testes/programas/json/aceito_3.json`

```json
{}

```

#### `testes/programas/json/aceito_3.esperado`

```text
entrada aceita
status 0
```

#### `testes/programas/json/rejeitado_1.json`

```json
{"chave": }

```

#### `testes/programas/json/rejeitado_1.esperado`

```text
linha 1, coluna 11: encontrado '}', esperado um de {STRING, NUMBER, BOOLEAN, NULO, '{', '['}
status 1
```

#### `testes/programas/json/rejeitado_2.json`

```json
[1, 2,]

```

#### `testes/programas/json/rejeitado_2.esperado`

```text
linha 1, coluna 7: encontrado ']', esperado um de {STRING, NUMBER, BOOLEAN, NULO, '{', '['}
status 1
```

#### `testes/programas/json/rejeitado_3.json`

```json
{"chave" "valor"}

```

#### `testes/programas/json/rejeitado_3.esperado`

```text
linha 1, coluna 10: encontrado '"valor"', esperado ':'
status 1
```

### 4.2. Novos arquivos em `testes/txt/*`

#### `testes/txt/exemplo.txt`

```text
(1 + 2) * 3
```

#### `testes/txt/tokens.txt`

```text
Token: tipo = 34, lexema = 'int', linha = 1
Token: tipo = 29, lexema = 'main', linha = 1
Token: tipo = 23, lexema = '(', linha = 1
Token: tipo = 24, lexema = ')', linha = 1
Token: tipo = 25, lexema = '{', linha = 2
Token: tipo = 34, lexema = 'int', linha = 3
Token: tipo = 1, lexema = 'a', linha = 3
Token: tipo = 21, lexema = ';', linha = 3
Token: tipo = 34, lexema = 'int', linha = 4
Token: tipo = 1, lexema = 'b', linha = 4
Token: tipo = 21, lexema = ';', linha = 4
Token: tipo = 1, lexema = 'a', linha = 5
Token: tipo = 20, lexema = '=', linha = 5
Token: tipo = 3, lexema = '10', linha = 5
Token: tipo = 21, lexema = ';', linha = 5
Token: tipo = 1, lexema = 'b', linha = 6
Token: tipo = 20, lexema = '=', linha = 6
Token: tipo = 3, lexema = '20', linha = 6
Token: tipo = 21, lexema = ';', linha = 6
Token: tipo = 36, lexema = 'print', linha = 7
Token: tipo = 23, lexema = '(', linha = 7
Token: tipo = 1, lexema = 'a', linha = 7
Token: tipo = 6, lexema = '+', linha = 7
Token: tipo = 1, lexema = 'b', linha = 7
Token: tipo = 24, lexema = ')', linha = 7
Token: tipo = 21, lexema = ';', linha = 7
Token: tipo = 33, lexema = 'return', linha = 8
Token: tipo = 3, lexema = '0', linha = 8
Token: tipo = 21, lexema = ';', linha = 8
Token: tipo = 26, lexema = '}', linha = 9
```

### 4.3. Arquivos `TEMP*.md` (resumo)

Três arquivos de anotações auxiliares existem apenas em `Trabalho_2-pronto/`:

- **`TEMP1.md` (259 linhas):** visão geral do Trabalho 2, listagem dos `TODO(aluno)` originais do esqueleto, divisão do trabalho em 6 fases, diagrama do fluxo principal (`ebnf_lexer.c` -> `ebnf_parser.c` -> `verificacao.c` -> `conjuntos.c` -> `ll1.c` -> `codegen.c`), instruções de compilação/execução via `Makefile` e relação de integração com o scanner do Trabalho 1.
- **`TEMP2.md` (144 linhas):** explicação didática de cada módulo implementado (`ebnf_parser.c`, `verificacao.c`, `conjuntos.c`, `ll1.c`, `codegen.c`, `microc_mapa.c`, `microc/microc.flex` e `microc/scanner.c`), incluindo diagrama Mermaid do fluxo e referências ao caminho antigo `/home/maykon/Trabalho/Trabalho_2/...`.
- **`TEMP3.md` (105 linhas):** roteiro prático de entrada/saída esperada e comandos para compilar e testar o gerador, o parser de `expr.ebnf` (usando `testes/txt/exemplo.txt`), `make microc` (incluindo `--tokens testes/txt/tokens.txt`), `make test`, `--debug`, `--sets` e verificação de vazamentos com Valgrind.

### 4.4. Artefatos de compilação e execução (`gerador` e `build/`)

Presentes apenas em `Trabalho_2-pronto/` (gerados durante compilação e execução dos testes):

- **`gerador` (154.536 bytes):** binário do gerador compilado.
- **`build/obj/`:** 11 arquivos objeto (`bitset.o`, `codegen.o`, `conjuntos.o`, `ebnf_lexer.o`, `ebnf_parser.o`, `gramatica.o`, `ll1.o`, `main.o`, `microc_mapa.o`, `util.o`, `verificacao.o`).
- **`build/expr.c`, `build/expr.h`, `build/expr_bin`:** artefatos de geração e compilação manual da gramática `expr.ebnf`.
- **`build/microc/`:** `parser.c`, `parser.h`, `lex.yy.c`, `lex.yy.o` e `parser_microc` (scanner Micro C gerado pelo Flex e compilado com o parser gerado).
- **`build/testes/`:** resultados da execução da suíte `testes/executar.sh` para `conflito_ll1` (`.gerador`), `recursao_esquerda` (`.gerador`), `expr` (`.c`, `.h`, `.cc`, `.bin`, `.gerador` e 7 `.saida`), `json` (`.c`, `.h`, `.cc`, `.bin`, `.gerador` e 6 `.saida`) e `microc` (`.c`, `.h`, `.gerador` e 6 `.saida`), sem nenhum arquivo `.diff` restante.
- *Observação de permissão:* os binários `gerador`, `build/expr_bin`, `build/microc/parser_microc`, `build/testes/expr.bin` e `build/testes/json.bin` encontram-se atualmente sem permissão de execução (`-rw-r--r--`).
