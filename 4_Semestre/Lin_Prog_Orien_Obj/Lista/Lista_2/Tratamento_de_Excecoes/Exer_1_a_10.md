# Exercícios sobre Tratamento de Exceções

## 1. Implemente o método buscarUsuario

Implemente um método chamado `buscarUsuario` que recebe um `String id` e:

a. lança uma exceção `IllegalArgumentException` caso o id seja nulo ou vazio;

b. caso contrário, retorna a mensagem "Usuário encontrado: " + id.

c. Depois disso, crie um método main que:

- Chama `buscarUsuario` com um valor válido.
- Chama `buscarUsuario` passando `null` ou `""`.
- Trata a exceção lançada usando try/catch.
- Exibe uma mensagem amigável quando ocorrer erro.

**Observação:** `IllegalArgumentException` é uma exceção unchecked que estende `RuntimeException`.

## 2. Implemente o método lerTemperatura

Implemente um método chamado `lerTemperatura` que recebe um `double valor` e lança uma `IllegalArgumentException` caso a temperatura esteja fora do intervalo permitido [-50, 80].

Caso contrário, retorna a mensagem: "Temperatura registrada: " + valor + "°C"

## 3. Implemente o método lerArquivoConfiguracao

Implemente um método chamado `lerArquivoConfiguracao` que recebe um `String caminho` e lança uma `IOException` se o caminho for nulo ou vazio.

**Observação:** `IOException` é uma checked exception.

## 4. Diferença entre exceções checked e unchecked

Exceções checked são verificadas pelo compilador e devem ser tratadas ou declaradas com `throws`. Exemplos incluem `IOException` e `SQLException`. Exceções unchecked, como `IllegalArgumentException` e `NullPointerException`, estendem `RuntimeException` e não precisam ser declaradas.

Checked devem ser usadas para condições recuperáveis externas ao programa, como falhas de I/O. Unchecked para erros de programação que poderiam ser evitados.

Impacto no design: Checked forçam o tratamento explícito, tornando as APIs mais robustas e previsíveis, mas podem tornar o código mais verboso. Unchecked permitem código mais limpo, mas riscos de tratamento inadequado.

## 5. Método "adia o tratamento" de uma exceção

Significa que o método declara a exceção com `throws` em sua assinatura, adiando o tratamento para o código que o chama.

Exemplo:

```java
public void lerArquivo(String caminho) throws IOException {
    // código que pode lançar IOException
}
```

Recomendado quando o método não tem contexto suficiente para tratar a exceção adequadamente, ou em bibliotecas/APIs onde o chamador deve decidir como lidar com o erro.

## 6. Múltiplos blocos catch

Quando uma exceção é lançada, o Java verifica os blocos `catch` em ordem. O primeiro bloco `catch` cujo tipo de parâmetro é compatível com a exceção lançada (ou uma superclasse) é executado.

A ordem é crucial: blocos `catch` para subclasses devem vir antes dos para superclasses. Caso contrário, o compilador gera erro.

## 7. Bloco finally

O bloco `finally` executa sempre, independentemente de uma exceção ser lançada ou não, após o `try`/`catch`. É usado para limpeza de recursos, como fechar arquivos ou conexões.

Exemplo: Em operações de arquivo, `finally` garante que o arquivo seja fechado mesmo se ocorrer erro.

Se houver `return` em `try` ou `catch`, `finally` executa antes do retorno.

## 8. Polimorfismo aplicado a exceções

Exceções seguem hierarquia de herança. É possível capturar uma subclasse específica ou uma superclasse como `Exception`.

Isso permite tratamento genérico ou específico. Riscos de capturar `Exception`: Pode capturar erros irrecuperáveis como `OutOfMemoryError`, mascarar bugs, e tornar debugging difícil.

## 9. Exceção não tratada dentro de um método

A exceção propaga para o método chamador. Se nenhum método trata, chega ao `main`, e a JVM termina o programa, imprimindo o stack trace.

## 10. Papel da cláusula throws

A cláusula `throws` na assinatura declara quais exceções checked o método pode lançar, informando o compilador e programadores.

Afeta o chamador: obriga a tratar com `try`/`catch` ou declarar `throws` novamente.

Obrigatória para checked exceptions; opcional para unchecked.

Ela documenta o contrato do método e força tratamento adequado.
