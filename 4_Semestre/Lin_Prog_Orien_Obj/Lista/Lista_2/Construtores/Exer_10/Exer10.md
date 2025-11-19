# Exercício 10

Explique com suas próprias palavras os seguintes conceitos fundamentais da memória e do modelo de execução de programas a objetos:

a. O que são variáveis locais? Onde elas são armazenadas? Qual é seu tempo de vida e escopo?

    Variáveis locais são aquelas declaradas dentro de um método, construtor ou bloco de código. Elas são armazenadas na pilha de execução (stack). Seu tempo de vida é limitado à execução do método ou bloco onde foram declaradas, ou seja, elas existem apenas durante essa execução e são destruídas quando o método termina. O escopo é local ao método ou bloco, o que significa que não podem ser acessadas fora dele.

b. O que são variáveis de instância? Onde elas ficam armazenadas? Quando elas existem e
quando deixam de existir?

    Variáveis de instância são atributos de uma classe, declarados fora de métodos, mas não estáticos. Elas são armazenadas na heap, associadas a cada instância (objeto) da classe. Elas existem desde o momento em que o objeto é criado (usando new) até quando o objeto deixa de ser e é coletado pelo garbage collector do Java.

c. Qual a função da Stack (pilha de execução) no programa? Que tipos de dados ou informações são guardados nela? O que acontece com os frames da  (stack frames) quando métodos são chamados e quando retornam?

    A Stack (pilha de execução) é responsável por gerenciar as chamadas de métodos e armazenar informações temporárias necessárias para a execução do programa. Ela guarda variáveis locais, parâmetros dos métodos, endereços de retorno (para saber onde voltar após a execução do método) e outras informações de controle. Quando um método é chamado, um novo frame (stack frame) é empilhado na stack, contendo essas informações. Quando o método retorna, o frame é desempilhado, liberando a memória e retornando o controle ao método chamador.

d. Qual a função da Heap no Java? Que tipos de valores estão na heap? Quem controla o ciclo de vida dos objetos armazenados nela?

    A Heap no Java é a área de memória usada para armazenar objetos criados dinamicamente durante a execução do programa. Ela contém instâncias de classes, arrays e outros objetos que são criados com a palavra-chave new. O ciclo de vida dos objetos na heap é controlado pelo garbage collector (GC), que automaticamente identifica e remove objetos que não são mais referenciados por nenhuma parte do programa, liberando a memória para reutilização.
