package Colecoes_e_Generics;

import java.util.Objects;
import java.util.*;

class Veiculo implements Comparable<Veiculo> {
    private String modelo;
    private String categoria;
    private int ano;
    private int kmRodados;

    public Veiculo(String modelo, String categoria, int ano, int kmRodados) {
        this.modelo = modelo;
        this.categoria = categoria;
        this.ano = ano;
        this.kmRodados = kmRodados;
    }

    public String getModelo() { return modelo; }
    public String getCategoria() { return categoria; }
    public int getAno() { return ano; }
    public int getKmRodados() { return kmRodados; }

    @Override
    public String toString() {
        return "Veiculo{modelo='" + modelo + "', categoria='" + categoria + "', ano=" + ano + ", kmRodados=" + kmRodados + "}";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Veiculo veiculo = (Veiculo) obj;
        return ano == veiculo.ano && kmRodados == veiculo.kmRodados &&
               Objects.equals(modelo, veiculo.modelo) && Objects.equals(categoria, veiculo.categoria);
    }

    @Override
    public int hashCode() {
        return Objects.hash(modelo, categoria, ano, kmRodados);
    }

    @Override
    public int compareTo(Veiculo outro) {
        int cmp = this.categoria.compareTo(outro.categoria);
        if (cmp == 0) {
            cmp = this.modelo.compareTo(outro.modelo);
        }
        return cmp;
    }
}

class Main {
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