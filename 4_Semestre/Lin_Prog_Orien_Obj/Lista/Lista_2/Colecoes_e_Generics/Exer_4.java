package Colecoes_e_Generics;

import java.util.*;

class Curso implements Comparable<Curso> {
    private String nome;
    private int cargaHoraria;
    private String nivel;

    public Curso(String nome, int cargaHoraria, String nivel) {
        this.nome = nome;
        this.cargaHoraria = cargaHoraria;
        this.nivel = nivel;
    }

    public String getNome() { return nome; }
    public int getCargaHoraria() { return cargaHoraria; }
    public String getNivel() { return nivel; }

    @Override
    public String toString() {
        return "Curso{nome='" + nome + "', cargaHoraria=" + cargaHoraria + ", nivel='" + nivel + "'}";
    }

    @Override
    public int compareTo(Curso outro) {
        return this.nome.compareTo(outro.nome);
    }
}

class Gerenciador<T> {
    private List<T> itens = new ArrayList<>();

    public void adicionar(T item) {
        itens.add(item);
    }

    public void listar() {
        for (T item : itens) {
            System.out.println(item);
        }
    }

    public void ordenar(Comparator<T> comparator) {
        Collections.sort(itens, comparator);
    }

    @SuppressWarnings({ "unchecked", "rawtypes" })
    public void ordenarPadrao() {
        if (!itens.isEmpty() && itens.get(0) instanceof Comparable) {
            Collections.sort((List) itens);
        }
    }
}

class ComparadorPorNivel implements Comparator<Curso> {
    @Override
    public int compare(Curso c1, Curso c2) {
        int ordem1 = getOrdem(c1.getNivel());
        int ordem2 = getOrdem(c2.getNivel());
        return Integer.compare(ordem1, ordem2);
    }

    private int getOrdem(String nivel) {
        switch (nivel) {
            case "Básico": return 1;
            case "Intermediário": return 2;
            case "Avançado": return 3;
            default: return 4;
        }
    }
}

class ComparadorPorCargaHoraria implements Comparator<Curso> {
    @Override
    public int compare(Curso c1, Curso c2) {
        return Integer.compare(c1.getCargaHoraria(), c2.getCargaHoraria());
    }
}

public class Exer_4 {
    public static void main(String[] args) {
        Gerenciador<Curso> gerenciador = new Gerenciador<>();
        gerenciador.adicionar(new Curso("Java Básico", 40, "Básico"));
        gerenciador.adicionar(new Curso("Python Avançado", 60, "Avançado"));
        gerenciador.adicionar(new Curso("C# Intermediário", 50, "Intermediário"));
        gerenciador.adicionar(new Curso("JavaScript", 30, "Intermediário"));
        gerenciador.adicionar(new Curso("SQL", 20, "Básico"));

        System.out.println("Cursos originais:");
        gerenciador.listar();

        System.out.println("\nOrdenados por nome (padrão):");
        gerenciador.ordenarPadrao();
        gerenciador.listar();

        System.out.println("\nOrdenados por carga horária:");
        gerenciador.ordenar(new ComparadorPorCargaHoraria());
        gerenciador.listar();

        System.out.println("\nOrdenados por nível:");
        gerenciador.ordenar(new ComparadorPorNivel());
        gerenciador.listar();
    }
}