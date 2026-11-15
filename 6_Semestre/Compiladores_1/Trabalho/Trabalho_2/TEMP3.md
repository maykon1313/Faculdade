### 1. Entrada e Saída Esperada

#### Fase A: O Gerador (`./gerador`)

* **Entrada:** Um arquivo de gramática com extensão `.ebnf` (contendo as seções `TOKENS` e `RULES`).

* **Saída esperada:**
* Dois arquivos de código-fonte em ANSI C especificados pelo prefixo: `prefixo.c` e `prefixo.h`.

* *(Opcional)* Tabelas de conjuntos de anulabilidade, `FIRST` e `FOLLOW` exibidas no terminal se usada a flag `--sets`.

* Mensagens de erro/aviso sintático ou semântico caso a gramática possua problemas (ex.: recursão à esquerda, conflitos $LL(1)$, símbolos indefinidos).

#### Fase B: O Analisador Gerado (Executável compilado)

* **Entrada:** Um programa fonte em formato texto (passado por argumento ou via `stdin`) ou um arquivo `tokens.txt` oriundo do TP1 (usando a flag `--tokens`).

* **Saída esperada:**
* **Se aceito:** Imprime `entrada aceita`. O código de saída do processo (exit code) deve ser `0`. Caso utilize a opção `--tree`, imprime também a árvore de derivação hierárquica.

* **Se houver erro sintático:** Imprime a linha, coluna (se não for modo Micro C), o token lido e os tokens que eram esperados naquele ponto (ex.: `linha 1, coluna 10: encontrado ')', esperado um de {NUM, ID, '('}`). O código de saída é `1`.

* **Se houver erro léxico:** Imprime a linha e o caractere inválido (ex.: `linha 1, coluna 5: erro lexico: caractere invalido '@'`) com código de saída `1`.

---

### 2. Como Executar

#### Passo 1: Compilar o gerador

No diretório raiz do projeto:

```bash
make
```

#### Passo 2: Gerar e compilar um analisador sintático

* **Para gramáticas gerais com analisador léxico próprio** (exemplo com `expr.ebnf`):

```bash
# 1. Cria a pasta de build (se não existir)
mkdir -p build

# 2. Executa o gerador para criar build/expr.c e build/expr.h
./gerador testes/gramaticas/expr.ebnf -o build/expr --tree

# 3. Compila o parser gerado
gcc -ansi -pedantic -Wall -Wextra -o build/expr_bin build/expr.c

# 4. Executa o analisador sobre um arquivo de teste
./build/expr_bin testes/txt/exemplo.txt

# Ou para ver a árvore de derivação:
./build/expr_bin --tree testes/txt/exemplo.txt
```

* **Para a linguagem Micro C (integrada ao TP1)**:

```bash
# Gera e compila o executável do parser Micro C diretamente
make microc

# Executa sobre um programa em Micro C
./build/microc/parser_microc testes/programas/microc/bubble.mc

# Ou executando a partir do arquivo de tokens gerado pelo TP1
./build/microc/parser_microc --tokens testes/txt/tokens.txt
```

---

### 3. Como Testar

1. **Bateria de testes automatizados:**
Execute o script integrado de testes:

```bash
make test
```

* O comando roda o gerador e os analisadores contra os casos presentes em `testes/` e compara com as saídas esperadas em `testes/esperado/` e `testes/programas/`.

* Se houver falhas, verifique os arquivos `.diff` gerados na pasta `build/testes/` para comparar o que divergiu.

2. **Inspeção de tabelas e depuração:**
* Teste se o parser da EBNF leu a gramática corretamente:

```bash
./gerador testes/gramaticas/expr.ebnf --debug
```

* Verifique se o cálculo de Anulável, FIRST e FOLLOW está batendo com as derivações manuais:

```bash
./gerador testes/gramaticas/expr.ebnf -o build/expr --sets
```

3. **Verificação de vazamentos de memória (Valgrind):**
O trabalho exige zero vazamentos de memória tanto no gerador quanto no analisador final:

```bash
valgrind --leak-check=full ./gerador testes/gramaticas/expr.ebnf -o build/expr
valgrind --leak-check=full ./build/expr_bin testes/txt/exemplo.txt
```