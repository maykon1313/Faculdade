package Aula_8;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

class comparaNome implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getNome().toLowerCase().compareTo(p2.getNome().toLowerCase());
    }
}

class comparaPreco implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return Double.compare(p2.getPreco(), p1.getPreco());
    }
}

class comparaCategoria implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getCategoria().toLowerCase().compareTo(p2.getCategoria().toLowerCase());
    }
}

class Produto {
    private String nome;
    private double preco;
    private String categoria;

    public Produto(String nome, double preco, String categoria) {
        this.nome = nome;
        this.preco = preco;
        this.categoria = categoria;
    }

    public String getNome() {return this.nome;}
    public double getPreco() {return this.preco;}
    public String getCategoria() {return this.categoria;}

    public String toString() {return "Nome="+this.nome+", "+"Preço="+this.preco+", Categoria="+this.categoria;}
}

class Catalogo<T> {
    List<T> itens = new ArrayList<>();

    public void adicionar(T item) {itens.add(item);}

    public void listar() {for (T item : itens) {System.out.println(item);}}

    public void ordenar(Comparator<T> comparator) {itens.sort(comparator);}
}

public class Exer1 {
    public static void main(String[] args) {
        Catalogo<Produto> catalogo = new Catalogo<Produto>();

        catalogo.adicionar(new Produto("Carne", 100.99, "Comida"));
        catalogo.adicionar(new Produto("Lápis", 1.99, "Materia Escolar"));
        catalogo.adicionar(new Produto("Mouse", 102.99, "Computador"));
        catalogo.adicionar(new Produto("Arroz", 101.99, "Comida"));

        System.out.println("Catalago:");
        catalogo.listar();

        System.out.println();

        System.out.println("Catalago por nome:");
        catalogo.ordenar(new comparaNome());
        catalogo.listar();

        System.out.println();

        System.out.println("Catalago por preço:");
        catalogo.ordenar(new comparaPreco());
        catalogo.listar();

        System.out.println();

        System.out.println("Catalago por categoria:");
        catalogo.ordenar(new comparaCategoria());
        catalogo.listar();
    }
    
}
