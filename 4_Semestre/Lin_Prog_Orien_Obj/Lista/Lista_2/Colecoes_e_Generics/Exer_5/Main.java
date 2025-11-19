package Colecoes_e_Generics.Exer_5;

import java.util.*;

public class Main {
    public static <T> void imprimirColecao(Collection<T> colecao) {
        for (T item : colecao) {
            System.out.println(item);
        }
    }

    public static void main(String[] args) {
        List<Veiculo> veiculos = new ArrayList<>();
        veiculos.add(new Veiculo("Civic", "Sedan", 2020, 15000));
        veiculos.add(new Veiculo("HR-V", "SUV", 2019, 20000));
        veiculos.add(new Veiculo("Civic", "Sedan", 2020, 15000)); // duplicado
        veiculos.add(new Veiculo("F-150", "Caminhão", 2018, 50000));
        veiculos.add(new Veiculo("Corolla", "Sedan", 2021, 10000));
        veiculos.add(new Veiculo("RAV4", "SUV", 2022, 5000));

        System.out.println("Veículos cadastrados:");
        imprimirColecao(veiculos);

        // Ordenar por quilometragem decrescente
        veiculos.sort(Comparator.comparing(Veiculo::getKmRodados).reversed());
        System.out.println("\nOrdenados por quilometragem (decrescente):");
        imprimirColecao(veiculos);

        // Ordenar por ano, empate km crescente
        veiculos.sort(Comparator.comparing(Veiculo::getAno).thenComparing(Veiculo::getKmRodados));
        System.out.println("\nOrdenados por ano (crescente), empate km (crescente):");
        imprimirColecao(veiculos);

        // HashSet
        Set<Veiculo> hashSet = new HashSet<>(veiculos);
        System.out.println("\nHashSet (sem duplicados):");
        imprimirColecao(hashSet);

        // TreeSet
        Set<Veiculo> treeSet = new TreeSet<>(veiculos);
        System.out.println("\nTreeSet (ordenado por compareTo):");
        imprimirColecao(treeSet);

        // HashMap categoria -> soma km
        Map<String, Integer> mapa = new HashMap<>();
        for (Veiculo v : veiculos) {
            mapa.put(v.getCategoria(), mapa.getOrDefault(v.getCategoria(), 0) + v.getKmRodados());
        }
        System.out.println("\nSoma km por categoria:");
        for (String cat : mapa.keySet()) {
            System.out.println(cat + ": " + mapa.get(cat));
        }
    }
}