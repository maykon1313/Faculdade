# Conceitos de LPOO aplicados no Trabalho

## 1. Classes e Objetos

- Todas as entidades do sistema são representadas por classes (ex.: `Monstro`, `Crianca`, `Porta`, `Cilindro`, `Gabinete`, `Agencia`).
- Objetos são instâncias dessas classes, criados dinamicamente durante a execução do programa.

## 2. Encapsulamento

- Atributos são declarados como `private` e acessados via métodos getters e setters (ex.: em `Crianca`, `Monstro`, `Porta`).
- Isso protege o estado interno dos objetos e permite controle sobre como os dados são modificados.

## 3. Herança

- A classe `Monstro` é abstrata e serve como superclasse para `MonstroDoRiso`, `MonstroDoSusto` e `MonstroDeSuporte`.
- As subclasses herdam atributos e métodos da superclasse, mas podem sobrescrever comportamentos específicos.

## 4. Polimorfismo

- Métodos como `getEficiencia()` e `getTipoMonstro()` comportam-se de forma diferente dependendo do tipo de monstro (usando `instanceof`).
- Permite tratar objetos de subclasses como instâncias da superclasse, facilitando a extensibilidade.

## 5. Abstração

- A classe `Monstro` é abstrata, definindo uma interface comum para todos os tipos de monstros sem implementação completa.
- Foca nos aspectos essenciais, ocultando detalhes de implementação.

## 6. Métodos Estáticos e Genéricos

- A classe `Agencia` usa métodos estáticos para gerenciar dados globais.
- Métodos genéricos como `encontrarPorIndex<T>()` permitem reutilização de código para diferentes tipos.

## 7. Tratamento de Exceções

- Uso de `try-catch` e lançamento de exceções (`IllegalArgumentException`, `IllegalStateException`) para validar entradas e estados (ex.: em `Gabinete.processarEnergia()`).

## 8. Expressões Lambda

- Expressões lambda são usadas para implementar interfaces funcionais de forma concisa (ex.: `n -> null` em `Main.java` para criar funções que retornam `null` quando um monstro não é encontrado).
- Permite passar comportamento como parâmetro, facilitando a programação funcional em Java.

## 9. Map e HashMap

- `Map` é uma interface que representa uma coleção de pares chave-valor, permitindo acesso rápido aos valores através das chaves.
- `HashMap` é uma implementação concreta de `Map` que usa uma tabela hash para armazenar os dados, oferecendo operações eficientes de inserção, remoção e busca (ex.: em `Main.java`, mapas são usados para associar nomes de crianças a objetos `Crianca`, IDs de portas a objetos `Porta`, etc., facilitando o carregamento e recuperação de dados do arquivo CSV).
- Também é usado `Map.of()` para criar mapas imutáveis com entradas fixas (ex.: `monstroFactory` para mapear tipos de monstros a construtores).
