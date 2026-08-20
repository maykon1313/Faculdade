# Exercícios sobre Lambdas, Streams e Interfaces Funcionais

## 1. Considere a interface abaixo

```java
public interface Operacao {
    int executar(int a, int b);
    
    default void imprimir(int resultado) {
        System.out.println("Resultado: " + resultado);
    }
    
    static boolean isPositivo(int n) {
        return n >= 0;
    }
}
```

a. Explique por que essa interface pode ser considerada uma interface funcional.

**Resposta:** Essa interface é funcional porque possui apenas um método abstrato (`executar`). Interfaces funcionais em Java podem ter apenas um método abstrato, embora possam incluir métodos default e static.

b. Quantos métodos abstratos uma interface funcional pode ter? Explique.

**Resposta:** Uma interface funcional pode ter exatamente um método abstrato. Se tiver mais de um, não será considerada funcional e não poderá ser usada com expressões lambda.

## 2. Crie uma interface funcional chamada Transformador, que recebe uma String e retorna outra String

A interface deve ter:
a. um único método abstrato `String transformar(String s);`
b. um método default que imprime a string transformada
c. um método static que verifica se a string é vazia

## 3. Considere as interfaces funcionais

```java
@FunctionalInterface
interface Somador {
    int somar(int a, int b);
}

@FunctionalInterface
interface Mensagem {
    String formatar(String nome);
}
```

a. No método main, crie uma expressão lambda para Somador que some dois números.
b. No método main, crie uma expressão lambda para Mensagem que retorne "Olá, \<nome>! Bem-vindo."
c. Atribua cada lambda a uma variável com referência à interface funcional e escreva um exemplo de chamada.

```java
public class Main3 {
    public static void main(String[] args) {
        Somador s = (a, b) -> a + b;
        Mensagem m = nome -> "Olá, " + nome + "! Bem-vindo.";
        
        int resultado = s.somar(10, 5);
        System.out.println(resultado); // 15
        
        String msg = m.formatar("Ana");
        System.out.println(msg); // Olá, Ana! Bem-vindo.
    }
}

@FunctionalInterface
interface Somador {
    int somar(int a, int b);
}

@FunctionalInterface
interface Mensagem {
    String formatar(String nome);
}
```

## 4. Utilizando a interface

```java
@FunctionalInterface
interface CalculadoraArea {
    double calcular(double largura, double altura);
}
```

Crie uma expressão lambda com bloco de código, que:
a. valida se largura e altura são positivas. Se não forem, retorna 0. Caso contrário, retorna a área (largura × altura).
b. Na main, escreva um exemplo de chamada do método.

**Resposta:** Criado `Main4.java`:

```java
public class Main4 {
    public static void main(String[] args) {
        CalculadoraArea calc = (largura, altura) -> {
            if (largura > 0 && altura > 0) {
                return largura * altura;
            } else {
                return 0.0;
            }
        };
        
        double area = calc.calcular(5.0, 10.0);
        System.out.println("Área: " + area); // Área: 50.0
    }
}

@FunctionalInterface
interface CalculadoraArea {
    double calcular(double largura, double altura);
}
```

## 5. Considere a classe

```java
class Produto {
    private String nome;
    private double preco;
    
    public Produto(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
    }
    
    public String getNome() { return nome; }
    public double getPreco() { return preco; }
    
    @Override
    public String toString() {
        return nome + " - R$ " + preco;
    }
}
```

E a lista:

```java
List<Produto> produtos = List.of(
    new Produto("Camiseta", 50),
    new Produto("Calça", 120),
    new Produto("Boné", 35),
    new Produto("Jaqueta", 350),
    new Produto("Meias", 20)
);
```

Usando streams:
a. Gere uma lista contendo apenas os produtos com preço acima de 50.
b. Imprima os resultados usando forEach.
c. Usando a stream map, gere uma lista somente com os nomes dos produtos em letras maiúsculas.
d. Usando streams, obtenha, retornando uma lista: os nomes dos produtos com preço abaixo de 100, ordenados alfabeticamente.

**Resposta:** Criado `Main5.java`:

```java
import java.util.List;
import java.util.stream.Collectors;

public class Main5 {
    public static void main(String[] args) {
        List<Produto> produtos = List.of(
            new Produto("Camiseta", 50),
            new Produto("Calça", 120),
            new Produto("Boné", 35),
            new Produto("Jaqueta", 350),
            new Produto("Meias", 20)
        );
        
        // a. Produtos com preço acima de 50
        List<Produto> acima50 = produtos.stream()
            .filter(p -> p.getPreco() > 50)
            .collect(Collectors.toList());
        
        // b. Imprimir
        acima50.forEach(System.out::println);
        
        // c. Nomes em maiúsculas
        List<String> nomesMaiusculos = produtos.stream()
            .map(p -> p.getNome().toUpperCase())
            .collect(Collectors.toList());
        System.out.println(nomesMaiusculos);
        
        // d. Nomes com preço < 100, ordenados
        List<String> nomesAbaixo100Ordenados = produtos.stream()
            .filter(p -> p.getPreco() < 100)
            .map(Produto::getNome)
            .sorted()
            .collect(Collectors.toList());
        System.out.println(nomesAbaixo100Ordenados);
    }
}

class Produto {
    private String nome;
    private double preco;
    
    public Produto(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
    }
    
    public String getNome() { return nome; }
    public double getPreco() { return preco; }
    
    @Override
    public String toString() {
        return nome + " - R$ " + preco;
    }
}
```

## 6. A partir do código “JukeboxDoLou”, modifique-o para

(Nota: Como o código original não foi fornecido, criei uma versão simplificada de Jukebox com músicas.)

a. Exiba as 5 músicas mais tocadas.
b. Encontre a música mais antiga e a música mais recente da lista.
c. Crie uma lista com as músicas clássicas, lançadas antes do ano 2000. Ordene-as por gênero.
d. Conte o número de artistas únicos cadastrados.
e. Exiba todas as músicas do gênero POP em ordem decrescente desconsiderando letras maiúsculas e minúsculas.
f. Existem músicas com o mesmo nome, mas artistas diferentes? Liste-as.4352

## 7. Descreva a relação entre expressões lambda e interfaces funcionais. Use um exemplo para explicar como a JVM sabe qual método deve ser executado

**Resposta:** Expressões lambda são implementações concisas de interfaces funcionais. Elas permitem passar comportamento como parâmetro sem criar classes anônimas. A JVM sabe qual método executar porque a interface funcional tem apenas um método abstrato, então a lambda implementa exatamente esse método. Exemplo: Para `Runnable r = () -> System.out.println("Hello");`, a JVM executa o método `run()` da interface `Runnable`.

## 8. Explique como funcionam as lambdas com bloco de código { ... }. Em quais situações elas são mais apropriadas do que lambdas simples (de uma linha)?

**Resposta:** Lambdas com bloco de código permitem múltiplas instruções, incluindo declarações de variáveis, loops e condicionais. Elas são apropriadas quando a lógica é complexa e não cabe em uma expressão simples. Lambdas simples são para operações diretas, como `(a, b) -> a + b`.

## 9. O que significa dizer que uma "stream é uma pipeline de operações"? Explique o que são operações intermediárias e terminais

**Resposta:** Uma stream é uma sequência de elementos que suporta operações funcionais. Uma pipeline é uma cadeia de operações: intermediárias (como `filter`, `map`) transformam a stream sem executá-la, e terminais (como `collect`, `forEach`) executam a pipeline e produzem um resultado.

## 10. Compare a operação map com a operação filter. Qual é o objetivo de cada uma? Quando usar uma e quando usar a outra?

**Resposta:** `map` transforma cada elemento da stream em outro (ex.: converter tipos). `filter` seleciona elementos que atendem a uma condição. Use `map` para transformação, `filter` para seleção.
