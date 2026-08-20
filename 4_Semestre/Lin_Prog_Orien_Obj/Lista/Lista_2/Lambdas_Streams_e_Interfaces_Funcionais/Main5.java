package Lambdas_Streams_e_Interfaces_Funcionais;

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