package Colecoes_e_Generics.Exer_6;

import java.util.*;

public class Main {
    public static <T> void imprimirColecao(Collection<T> colecao) {
        for (T item : colecao) {
            System.out.println(item);
        }
    }

    public static void main(String[] args) {
        List<Livro> livros = List.of(
            new Livro("Java", "Autor A", "Tecnologia", 2020, 100),
            new Livro("Python", "Autor B", "Tecnologia", 2019, 200),
            new Livro("História", "Autor C", "História", 2018, 150),
            new Livro("Java", "Autor A", "Tecnologia", 2020, 100), // duplicado
            new Livro("Física", "Autor D", "Ciência", 2021, 300),
            new Livro("Matemática", "Autor E", "Ciência", 2017, 250),
            new Livro("Literatura", "Autor F", "Literatura", 2016, 180),
            new Livro("Química", "Autor G", "Ciência", 2022, 120)
        );

        System.out.println("Livros cadastrados:");
        imprimirColecao(livros);

        // Comparator por uso
        Comparator<Livro> comparatorPorUso = Comparator.comparing(Livro::getPaginasLidas).reversed();
        List<Livro> sortedPorUso = new ArrayList<>(livros);
        sortedPorUso.sort(comparatorPorUso);
        System.out.println("\nOrdenados por páginas lidas (decrescente):");
        imprimirColecao(sortedPorUso);

        // Ordenar por ano, empate paginasLidas
        List<Livro> sortedPorAno = new ArrayList<>(livros);
        sortedPorAno.sort(Comparator.comparing(Livro::getAnoPublicado).thenComparing(Livro::getPaginasLidas));
        System.out.println("\nOrdenados por ano (crescente), empate páginas lidas (crescente):");
        imprimirColecao(sortedPorAno);

        // HashSet
        Set<Livro> hashSet = new HashSet<>(livros);
        System.out.println("\nHashSet (sem duplicados):");
        imprimirColecao(hashSet);

        // TreeSet
        Set<Livro> treeSet = new TreeSet<>(livros);
        System.out.println("\nTreeSet (ordenado por compareTo):");
        imprimirColecao(treeSet);

        // HashMap categoria -> soma paginasLidas
        Map<String, Integer> mapa = new HashMap<>();
        for (Livro l : livros) {
            mapa.put(l.getCategoria(), mapa.getOrDefault(l.getCategoria(), 0) + l.getPaginasLidas());
        }
        System.out.println("\nSoma páginas lidas por categoria:");
        for (String cat : mapa.keySet()) {
            System.out.println(cat + ": " + mapa.get(cat));
        }
    }
}