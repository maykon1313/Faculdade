# Visão geral

O Trabalho 2 é um **gerador de analisadores sintáticos descendentes recursivos**.

Você fornece uma gramática em EBNF:

```bash
./gerador gramatica.ebnf -o saida/parser
```

O programa `gerador` lê essa gramática, analisa se ela é válida e gera:

```text
saida/parser.c
saida/parser.h
```

Depois, esses arquivos são compilados junto com um scanner para formar um analisador da linguagem descrita.

## TODOs

```bash
src/verificacao.c:8: * TODO(aluno):
src/verificacao.c:71:/* TODO(aluno): emitir um AVISO para cada nao terminal que nao pode ser
src/verificacao.c:81:/* TODO(aluno): emitir um ERRO para cada nao terminal definido que nao
src/verificacao.c:92:/* TODO(aluno): detectar recursao a esquerda direta (a = a ...) e
src/microc_mapa.c:13: * TODO(aluno): implementar microc_carregar_tokens_h.
src/microc_mapa.c:57:/* TODO(aluno): abrir o arquivo (ler_arquivo ajuda), localizar a
src/conjuntos.c:6: * TODO(aluno): conj_anulavel, conj_first e conj_follow. Os tres sao
src/conjuntos.c:65:/* TODO(aluno): calcular e->anulavel para cada no Expr e g->nts[i].anulavel.
src/conjuntos.c:76:/* TODO(aluno): calcular e->first para cada no Expr e g->nts[i].first.
src/conjuntos.c:80: * Calcule o FIRST de TODOS os filhos de uma sequencia, mesmo os que
src/conjuntos.c:87:/* TODO(aluno): calcular e->follow (o que pode vir logo apos cada
src/codegen.c:18: * TODO(aluno):
src/codegen.c:284:     * TODO(aluno): traduzir as demais construcoes (secao 4):
src/codegen.c:302:        emit(em, "/* TODO(aluno): construcao ainda nao traduzida */");
src/codegen.c:320:    /* TODO(aluno): converter a expressao regular em automato finito
src/codegen.c:331:    fputs("    /* TODO(aluno): automato para ", f);
src/codegen.c:350:    /* TODO(aluno): emitir a leitura real com fgets + sscanf (formato
src/ebnf_parser.c:20: * TODO(aluno): implementar parse_expr, parse_seq e parse_fator, que
src/ebnf_parser.c:88: * TODO(aluno): implementar as funcoes abaixo seguindo a gramatica da
src/ll1.c:20: * TODO(aluno): verificar_expr e ll1_verificar.
src/ll1.c:45:/* TODO(aluno): percorrer as regras e, para cada no E_ALT, E_OPC e E_REP,
microc/LEIAME.md:8:- `scanner.c`: adaptador entre `microc_yylex()` e `Token`. Procure os `TODO(aluno)`.
microc/scanner.c:10: * TODO(aluno): adaptar os pontos marcados ao seu TP1, para que
microc/scanner.c:32:    /* TODO(aluno): para ID, INTEGERCONST, CHARCONST e STRINGCONST, devolva
microc/scanner.c:98:    /* TODO(aluno): liberar tambem a tabela de strings do TP1. */
```

```bash
Fase 1: Leitura da EBNF (AST)
   └── X src/ebnf_parser.c
   │
Fase 2: Verificações Semânticas Básicas
   └── X src/verificacao.c (inalcançáveis e improdutivos)
   │
Fase 3: Conjuntos Sintáticos & Recursão à Esquerda
   ├── 3.1: src/conjuntos.c (conj_anulavel)
   ├── X 3.2: src/verificacao.c (verif_recursao_esquerda)
   └── 3.3: src/conjuntos.c (conj_first e conj_follow)
   │ 
Fase 4: Verificação LL(1)
   └── src/ll1.c (ll1_verificar e 3 condições)
   │
Fase 5: Geração de Código & Integração Micro C
   ├── 5.1: src/codegen.c (gen_expr)
   ├── 5.2: microc_mapa.c + microc/ (scanner TP1)
   └── 5.3: src/codegen.c (gen_casamento_regex e gen_token_de_arquivo)
   │
Fase 6: Bateria de Testes Finais e Documentação
   └── Novas gramáticas, programas aceitos/rejeitados, README.md, USO_IA.md
```

## Fluxo principal

```text
gramatica.ebnf
      |
      v
ebnf_lexer.c
      |
      v
ebnf_parser.c
      |
      v
Árvore Expr da gramática
      |
      v
verificacao.c
      |
      v
conjuntos.c (nullable, FIRST, FOLLOW)
      |
      v
ll1.c
      |
      v
codegen.c
      |
      v
parser.c/parser.h
      |
      v
scanner + parser gerado
```

O fluxo é coordenado principalmente pelo `main.c`, conforme descrito no `README.md`.

## O que precisa ser implementado

Os pontos principais marcados com `TODO(aluno)` são:

1. **Parser da gramática EBNF**
   - `parse_expr`
   - `parse_seq`
   - `parse_fator`

2. **Verificação semântica**
   - símbolos inalcançáveis;
   - símbolos improdutivos;
   - recursão à esquerda.

3. **Conjuntos**
   - anulabilidade;
   - `FIRST`;
   - `FOLLOW`.

4. **Verificação LL(1)**
   - as três condições para saber se as alternativas podem ser escolhidas com um token de lookahead.

5. **Geração de código**
   - `gen_expr`;
   - geração de sequência;
   - alternativas;
   - opcionais `[ ... ]`;
   - repetições `{ ... }`;
   - casamento de expressões regulares;
   - leitura de token de arquivo.

6. **Integração com o scanner do Trabalho 1**
   - copiar os arquivos do scanner para `microc/`;
   - implementar `microc_carregar_tokens_h`;
   - ajustar `microc/scanner.c`;
   - garantir que o scanner devolva `END_OF_FILE`;
   - ajustar o prefixo do Flex para `microc_yy`.

A tabela completa está no `README.md`.

## Como compilar

Na raiz do projeto:

```bash
make
```

Isso compila o gerador. Se os arquivos do Micro C estiverem em `microc/`, também tenta compilá-lo.

Para executar os testes:

```bash
make test
```

Para gerar o parser do Micro C:

```bash
make microc
```

O resultado será:

```text
build/microc/parser_microc
```

Para remover arquivos gerados:

```bash
make clean
```

Esses comandos estão definidos no `Makefile`.

## Como gerar um parser manualmente

```bash
./gerador gramatica.ebnf -o saida/parser
gcc -ansi -pedantic -Wall -Wextra -o parser saida/parser.c
./parser programa.txt
```

Opções úteis:

```bash
./gerador gramatica.ebnf -o saida/parser --sets
./gerador gramatica.ebnf -o saida/parser --tree
./gerador gramatica.ebnf -o saida/parser --debug
```

Para usar o scanner do Micro C:

```bash
./gerador testes/gramaticas/microc.ebnf \
  -o build/microc/parser \
  --scanner microc \
  --tree
```

## Relação com o Trabalho 1

O scanner do Trabalho 1 não é descartado. Ele será reutilizado assim:

```text
programa Micro C
      |
      v
scanner do TP1
      |
      v
tokens
      |
      v
parser gerado no TP2
      |
      v
aceita ou rejeita o programa
```

O arquivo `microc.flex` é o esqueleto do scanner. Ele precisa estar no projeto como:

```text
microc/microc.flex
```

Atenção: o arquivo fornecido aparece como `file_microc.flex`; provavelmente será necessário copiá-lo/renomeá-lo para `microc/microc.flex`.

## O que ainda falta fazer, na prática

Ordem recomendada:

1. Copiar o scanner e arquivos auxiliares do TP1 para `microc/`.
2. Preencher `aluno:` e `uso_ia:` no `README.md`.
3. Registrar o uso de IA no `USO_IA.md`.
4. Implementar os `TODO(aluno)`.
5. Rodar:

```bash
make
make test
make microc
```

6. Adicionar os testes exigidos:
   - pelo menos 5 gramáticas;
   - 3 programas aceitos por gramática válida;
   - 3 programas rejeitados por gramática válida.

Em resumo: o TP1 fornece o **scanner**; o TP2 implementa o **gerador do parser**, as análises `FIRST/FOLLOW/LL(1)` e a geração automática do analisador sintático.