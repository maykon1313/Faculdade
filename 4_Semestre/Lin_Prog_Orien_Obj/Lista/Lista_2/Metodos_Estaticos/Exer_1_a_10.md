# Exercícios sobre Métodos Estáticos

## 1. Defina o conceito de método utilitário. Como os métodos utilitários são acessados?

Um método utilitário é um método estático projetado para realizar operações auxiliares ou cálculos que não dependem do estado de uma instância específica da classe. Eles são acessados diretamente pela classe, sem necessidade de instanciar um objeto, usando a sintaxe `Classe.metodo()`.

## 2. Defina o conceito de classe utilitária. Qual a diferença de uma classe utilitária e uma classe comum na orientação a Objetos?

Uma classe utilitária é uma classe que contém apenas métodos estáticos e não possui atributos de instância, sendo projetada para fornecer funcionalidades auxiliares sem necessidade de criação de objetos. A diferença para uma classe comum é que classes utilitárias não são instanciadas (geralmente têm construtores privados ou são declaradas como `final` para impedir instanciação), enquanto classes comuns permitem criação de objetos e encapsulam estado e comportamento por instância.

## 3. Defina o conceito de variáveis estáticas. Qual a diferença entre variáveis estáticas e variáveis de instância em uma classe? Qual a diferença em relação ao acesso de valores considerando esses dois tipos de variáveis? Quando uma variável estática é inicializada?

Variáveis estáticas (declaradas com `static`) são compartilhadas por todas as instâncias da classe e existem independentemente de objetos criados. A diferença para variáveis de instância é que estas são únicas por objeto, enquanto estáticas são globais à classe. Em termos de acesso, variáveis estáticas são acessadas via `Classe.variavel`, enquanto instâncias usam `objeto.variavel`. Uma variável estática é inicializada uma vez, quando a classe é carregada pela JVM, antes de qualquer instância.

## 4. Qual a diferença entre uma variável estática e uma variável estática final (material EaD sobre números e elementos estáticos). Qual a convenção usada para criar nomes de constantes no Java? Quais são as formas de inicialização de variáveis estáticas?

Uma variável estática pode ser modificada após inicialização, enquanto uma `static final` é uma constante imutável após atribuição. A convenção para nomes de constantes é usar letras maiúsculas e underscores para separar palavras (ex.: `MAX_VALUE`). Formas de inicialização: na declaração (ex.: `static int x = 5;`), em bloco estático (ex.: `static { x = 10; }`), ou na primeira referência (lazy initialization).

## 5. Onde a palavra "final" pode ser usada no Java? O significado é sempre o mesmo? Variáveis finais sempre são estáticas?

A palavra `final` pode ser usada em variáveis (imutáveis após inicialização), métodos (não podem ser sobrescritos) e classes (não podem ser herdadas). O significado varia: para variáveis, impede reatribuição; para métodos e classes, impede extensão. Variáveis finais não são necessariamente estáticas; podem ser de instância ou locais, mas constantes globais geralmente são `static final`.

## 6. O que é um método final? Qual sua utilidade na orientação a objetos?

Um método final é declarado com `final` e não pode ser sobrescrito em subclasses. Sua utilidade é garantir que o comportamento específico do método seja preservado, evitando alterações acidentais ou maliciosas em heranças, promovendo segurança e previsibilidade no design.

## 7. O que é uma classe final? Em que contexto faz sentido a criação de uma classe final?

Uma classe final é declarada com `final` e não pode ser herdada. Faz sentido em contextos onde a classe representa uma implementação completa e imutável, como classes utilitárias (ex.: `Math`), ou para segurança, evitando subclasses que possam comprometer o comportamento (ex.: classes de segurança ou APIs críticas).

## 8. O que são classes wrapper? Qual sua utilidade na orientação a objetos?

Classes wrapper (como `Integer`, `Double`) encapsulam tipos primitivos em objetos, permitindo tratá-los como objetos em coleções ou APIs que exigem objetos. Sua utilidade é fornecer métodos adicionais, conversões e suporte a genéricos, facilitando operações orientadas a objetos com tipos primitivos.

## 9. O que são imports estáticos? Em quais contextos eles podem ser úteis? Em quais contextos não é adequado utilizá-los?

Imports estáticos (ex.: `import static java.lang.Math.PI;`) permitem acessar membros estáticos de uma classe sem qualificar com o nome da classe. São úteis para reduzir verbosidade em código que usa muitos membros estáticos (ex.: constantes ou métodos utilitários). Não são adequados em contextos onde há risco de conflitos de nomes, em código colaborativo sem clareza, ou quando o uso excessivo pode tornar o código menos legível.

## 10. Em Java, crie a classe ContadorObjetos. Ele possui os seguintes atributos

- `private static int totalCriados`: contar quantos objetos dessa classe foram instanciados no total.
- `private int id`: identificador único para cada objeto criado

### a. Crie um construtor padrão, sem parâmetros. A cada vez que um novo objeto é criado, a variável totalCriados deve ser incrementada em 1 unidade. Além disso, atribua ao atributo id o valor atual de totalCriados

### b. Implemente o método getId(), que deve retornar o identificador do objeto

### c. Crie os métodos estáticos

- `public static int getTotalCriados()`: retorna quantos objetos já foram criados
- `public static void resetarContador()`: zera o contador totalCriados. O método não deve afetar os IDs dos objetos já criados, apenas o contador global.

### d. Crie a classe Util: A classe deve possuir apenas métodos utilitários (sem atributos), contendo

- `public static boolean ehPar(int x)` → retorna true se o número for par.
- `public static int maior(int a, int b)` → retorna o maior dos dois valores.

### e. Na classe Main, crie três instâncias de ContadorObjetos e imprima seus IDs. Imprima o valor de ContadorObjetos.getTotalCriados()

### f. Chame ContadorObjetos.resetarContador()

### g. Crie mais dois objetos e exiba seus IDs e o total atualizado

### h. Use os métodos da classe Util para: verificar se um número é par; Encontrar o maior entre dois inteiros
