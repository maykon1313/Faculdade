package Colecoes_e_Generics;

import java.util.*;

class Produto {
    private String nome;
    private double preco;
    private String categoria;

    Produto(String nome, double preco, String categoria) {
        this.nome = nome;
        this.preco = preco;
        this.categoria = categoria;
    }

    public String getNome() { return this.nome; }
    public double getpreco() { return this.preco; }
    public String getCategoria() { return this.categoria; }

    @Override
    public String toString() { return "Nome: " + this.nome + ", Preco: " + this.preco + ", Categoria: " + this.categoria + '.'; } 
}

class Catalago<T> {
    private List<T> itens = new ArrayList<>();

    public void adicionar(T item) { itens.add(item); }

    public void listarItens() { for(T i : itens) { System.out.println(i); } }

    public void ordenar(Comparator<T> comparator) { Collections.sort(itens, comparator); }
}

class CompararProdutoPorNome implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getNome().compareTo(p2.getNome());
    }
}

class CompararProdutoPorPreco implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return Double.compare(p1.getpreco(), p2.getpreco());
    }
}

class CompararProdutoPorCategoria implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getCategoria().compareTo(p2.getCategoria());
    }
}

public class Exer_2 {
    public static void main(String[] args) {
        Catalago<Produto> c = new Catalago<>();

        c.adicionar(new Produto("Notebook", 2500.0, "Eletrônicos"));
        c.adicionar(new Produto("Livro", 50.0, "Livros"));
        c.adicionar(new Produto("Mouse", 30.0, "Eletrônicos"));

        System.out.println("Produtos originais:");
        c.listarItens();

        System.out.println("\nOrdenado por nome:");
        c.ordenar(new CompararProdutoPorNome());
        c.listarItens();

        System.out.println("\nOrdenado por preço:");
        c.ordenar(new CompararProdutoPorPreco());
        c.listarItens();

        System.out.println("\nOrdenado por categoria:");
        c.ordenar(new CompararProdutoPorCategoria());
        c.listarItens();
    }
}

