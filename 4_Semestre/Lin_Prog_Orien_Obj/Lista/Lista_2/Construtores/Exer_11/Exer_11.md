# Exercício 11

## Enunciado

Explique detalhadamente, usando conceitos de stack e heap, quais variáveis desse código ficam armazenadas na stack e quais ficam na heap. Em sua resposta, descreva também:

a. Quais variáveis existem apenas dentro do escopo de cada método e deixam de existir após
sua execução.

b. Quais objetos continuam vivos na heap depois que cada método termina.

c. O que acontece com os parâmetros dos métodos quando os métodos retornam.

d. Qual a diferença entre as variáveis locais (armazenadas na stack) e os objetos referenciados
por elas (armazenados na heap)?

## a. Quais variáveis existem apenas dentro do escopo de cada método e deixam de existir após sua execução?

- **No método `main`**:
  - `quantidade` (tipo `int`): Variável local primitiva, armazenada na stack. Existe apenas durante a execução do `main` e é removida da stack quando o método termina.
  - `p1` (referência a `Produto`): Referência local, armazenada na stack. Aponta para um objeto na heap, mas a própria referência deixa de existir após o `main` terminar (embora o objeto na heap possa persistir se houver outras referências).
  - `p2` (referência a `Produto`): Similar a `p1`, é uma referência local na stack que deixa de existir após o `main`.

- **No método `calculaTotal`**:
  - `prod` (parâmetro, referência a `Produto`): Referência local na stack, passada como cópia da referência original. Deixa de existir quando o método retorna.
  - `q` (parâmetro, tipo `int`): Valor primitivo copiado na stack. Deixa de existir quando o método retorna.
  - `total` (tipo `double`): Variável local primitiva na stack. Deixa de existir quando o método retorna.

- **No método `criarProdutoPromocional`**:
  - `nomeBase` (parâmetro, referência a `String`): Referência local na stack, passada como cópia. Deixa de existir quando o método retorna.
  - `nomePromo` (referência a `String`): Referência local na stack, criada dentro do método. Deixa de existir quando o método retorna.

Essas variáveis são desalocadas automaticamente da stack quando o método sai do escopo, pois a stack segue o princípio LIFO (Last In, First Out).

## b. Quais objetos continuam vivos na heap depois que cada método termina?

- Após `calculaTotal` terminar: O objeto `Produto` criado em `main` (referenciado por `p1`) continua vivo na heap, pois ainda há uma referência ativa a ele em `main`. O objeto `String` "Café" (usado no construtor) também permanece, pois é parte do objeto `Produto`.
  
- Após `criarProdutoPromocional` terminar: O novo objeto `Produto` criado no `return` continua vivo na heap, pois é retornado e atribuído a `p2` em `main`. O objeto `String` "Açúcar Promoção" (criado para `nomePromo`) também permanece, pois é usado no novo `Produto`. O objeto `String` "Açúcar" (passado como parâmetro) continua vivo se houver outras referências, mas neste caso, é um literal de string que pode ser reutilizado pela JVM.

- Após `main` terminar: Nenhum objeto permanece vivo na heap, pois todas as referências (`p1` e `p2`) são removidas da stack, e não há mais ponteiros para os objetos. O garbage collector (GC) da JVM pode desalocar esses objetos posteriormente.

Objetos na heap só são desalocados pelo GC quando não há mais referências ativas a eles.

## c. O que acontece com os parâmetros dos métodos quando os métodos retornam?

Quando um método retorna, os parâmetros são removidos da stack automaticamente. Para parâmetros primitivos (como `int q` ou `double total`), o valor é perdido. Para parâmetros de referência (como `Produto prod` ou `String nomeBase`), apenas a cópia da referência é removida da stack — o objeto na heap permanece intacto, desde que haja outras referências a ele. Isso não afeta o objeto original; mudanças no objeto dentro do método persistem se o objeto for mutável (como modificar campos de `Produto`).

## d. Qual a diferença entre as variáveis locais (armazenadas na stack) e os objetos referenciados por elas (armazenados na heap)?

- **Variáveis locais (na stack)**: São temporárias e existem apenas durante a execução do método. Incluem primitivos (como `int quantidade`) e referências (como `Produto p1`). Elas são rápidas de alocar/desalocar e seguem o escopo do método. Uma referência na stack é apenas um ponteiro (endereço de memória) para um objeto na heap — ela não contém o objeto em si.

- **Objetos referenciados (na heap)**: São as instâncias reais de classes (como o objeto `Produto` criado com `new`). Eles podem persistir além do escopo do método se houver referências ativas. A heap é mais lenta e gerenciada pelo GC, que remove objetos não referenciados para evitar vazamentos de memória. A diferença chave é que a stack armazena "metadados" (valores primitivos ou ponteiros), enquanto a heap armazena os dados complexos e mutáveis.

Essa separação permite eficiência (stack para operações rápidas) e flexibilidade (heap para objetos compartilhados). No código, por exemplo, `p1` é uma referência na stack apontando para um `Produto` na heap. Se `p1` for reatribuída, a referência muda, mas o objeto na heap pode continuar vivo.
