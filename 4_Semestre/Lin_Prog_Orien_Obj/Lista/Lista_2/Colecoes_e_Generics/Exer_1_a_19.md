# Exercícios

## 1. Analise o código

```java
List<String> musicas = new ArrayList<>();
```

Explique o papel do operador diamante (<>) no código acima. O que significa usar new ArrayList<>() ao invés de new ArrayList\<String>()?

**Resposta:** O operador diamante `<>` permite a inferência de tipos em Java. Ele foi introduzido no Java 7 para simplificar a sintaxe de criação de instâncias de classes genéricas. No código acima, `new ArrayList<>()` infere o tipo `String` a partir da declaração `List<String> musicas`, tornando-o equivalente a `new ArrayList<String>()`. Isso evita a repetição desnecessária do tipo e torna o código mais limpo e legível.

## 7. Explique, com suas próprias palavras, a diferença fundamental entre as coleções List e Set

**Resposta:** A diferença fundamental é que List permite elementos duplicados e mantém a ordem de inserção (ou uma ordem específica), enquanto Set não permite duplicados e geralmente não mantém ordem (exceto TreeSet que ordena). List é melhor para situações onde a ordem e duplicatas importam, como listas de tarefas. Set é melhor para coleções únicas, como conjunto de IDs únicos.

## 8. Como o comportamento de inserção e acesso de elementos difere entre List e Set?

**Resposta:** Em List, inserção adiciona ao final ou posição específica, acesso por índice com get(index). Permite duplicatas. Em Set, inserção adiciona se não existir, sem posição específica. Acesso via iterador ou contains. Set não permite duplicatas. List tem índices, Set não. Ordenação: List mantém ordem de inserção, Set pode ser não ordenado (HashSet) ou ordenado (TreeSet).

## 9. Por que um HashSet pode considerar que dois objetos são duplicados mesmo que ocupem posições diferentes na memória?

**Resposta:** Porque HashSet usa equals() e hashCode() para verificar igualdade. Mesmo objetos diferentes na memória, se equals() retornar true e hashCode() for igual, são considerados iguais e não adicionados como duplicados.

## 10. O que diferencia o Map das coleções List e Set?

**Resposta:** Map armazena pares chave-valor, não apenas elementos. List e Set armazenam elementos únicos ou com duplicatas. Use Map quando precisar associar chaves a valores, como dicionários.

## 11. Em uma aplicação real, quando você escolheria utilizar um TreeSet ao invés de um HashSet?

**Resposta:** Quando precisar de ordenação automática dos elementos, pois TreeSet mantém os elementos ordenados, enquanto HashSet não garante ordem.

## 12. Explique por que um Map não pode ser diretamente considerado uma coleção de elementos como List ou Set

**Resposta:** Porque Map representa uma estrutura de pares chave-valor, não uma coleção de elementos individuais. Embora tenha métodos como keySet() e values() que retornam coleções, o Map em si não implementa Collection.

## 13. Explique o conceito de Factory Method em orientação a objetos

**Resposta:** Factory Method é um padrão de design onde uma classe define um método para criar objetos, mas deixa as subclasses decidirem qual classe instanciar. É útil para criar objetos de diferentes tipos sem especificar a classe concreta, promovendo flexibilidade e desacoplamento.

## 14. O que são parâmetros de tipos genéricos em Java

**Resposta:** Parâmetros de tipos genéricos permitem criar classes, interfaces e métodos que operam em tipos especificados pelo usuário. Antes do Java 5, usava-se Object, causando problemas de type safety e necessidade de castings. Genéricos fornecem type safety em tempo de compilação.

## 15. Qual é a diferença entre declarar um tipo genérico na classe (class Caixa\<T>) e declarar na assinatura de um método (\<T> T identidade(T valor))?

**Resposta:** Na classe, o tipo é para toda a classe. No método, o tipo é específico para aquele método. Use na classe quando o tipo afeta múltiplos métodos/atributos. No método quando só afeta aquele método.

## 16. Por que interfaces como Comparable\<T> e classes como Collections usam tanto parâmetros de tipos genéricos?

**Resposta:** Para garantir type safety. Por exemplo, Comparable\<T> compara objetos do mesmo tipo, evitando erros de compilação. Collections.sort(List\<T>) garante que a lista é de elementos comparáveis.

## 17. Qual é a diferença entre usar List\<Object> e List<?> como parâmetro de método?

**Resposta:** List\<Object> aceita qualquer List, mas permite adicionar Object. List\<?> é wildcard, aceita qualquer tipo de List, mas não permite adicionar elementos (exceto null). Use List\<Object> quando precisar adicionar objetos de qualquer tipo, List<?> para leitura apenas.

## 18. Explique por que o código abaixo gera erro de compilação

```java
List<? extends Number> numeros = new ArrayList<Integer>();
numeros.add(10);
```

**Resposta:** Porque ? extends Number significa "qualquer subtipo de Number", mas o compilador não sabe qual exatamente. Adicionar 10 (int) pode não ser compatível com o tipo real. Para corrigir, use List\<Number> ou não adicione.

## 19. Seja o compilador

- private void takeDogs(List\<Dog> dogs){}
- private void takeAnimals(List\<Animal> animals){}
- private void takeSomeAnimals(List<? extends Animal> animals){}
- private void takeObjects(ArrayList\<Object> objects){}

Quais dos comandos abaixo compilam e quais não compilam?

- takeAnimals(new ArrayList\<Animal>()); **Compila**
- takeDogs(new ArrayList\<Animal>()); **Não compila** (List\<Animal> não é List\<Dog>)
- takeAnimals(new ArrayList\<Dog>()); **Não compila** (List\<Dog> não é List\<Animal>)
- takeDogs(new ArrayList\<Dog>()); **Compila**
- List\<Dog> dogs = new ArrayList\<Dog>(); takeDogs(dogs); **Compila**
- takeSomeAnimals(new ArrayList\<Dog>()); **Compila** (covariância)
- takeSomeAnimals(new ArrayList\<Animal>()); **Compila**
