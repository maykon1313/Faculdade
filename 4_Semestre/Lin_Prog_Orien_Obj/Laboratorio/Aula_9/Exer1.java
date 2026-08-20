import java.util.*;

abstract class GetVeiculos {
    public static ArrayList<Veiculo> MockArrayList() {
        ArrayList<Veiculo> mock = new ArrayList<>();
        mock.add(new Veiculo("Civic", "Sedan", 2020, 50_000));
        mock.add(new Veiculo("Accord", "Sedan", 2019, 60_000));
        mock.add(new Veiculo("F-150", "Pickup", 2021, 30_000));
        mock.add(new Veiculo("Corolla", "Sedan", 2018, 70_000));
        mock.add(new Veiculo("Camry", "Sedan", 2020, 45_000));
        mock.add(new Veiculo("Mustang", "Coupe", 2019, 55_000));
        mock.add(new Veiculo("Explorer", "SUV", 2021, 40_000));
        mock.add(new Veiculo("Ranger", "Pickup", 2020, 35_000));
        mock.add(new Veiculo("Focus", "Hatchback", 2017, 80_000));
        mock.add(new Veiculo("Fusion", "Sedan", 2019, 65_000));
        mock.add(new Veiculo("Escape", "SUV", 2020, 50_000));
        mock.add(new Veiculo("Edge", "SUV", 2021, 30_000));
        mock.add(new Veiculo("Taurus", "Sedan", 2018, 75_000));
        mock.add(new Veiculo("Expedition", "SUV", 2020, 45_000));
        mock.add(new Veiculo("Fiesta", "Hatchback", 2016, 90_000));
        mock.add(new Veiculo("Bronco", "SUV", 2021, 25_000));
        mock.add(new Veiculo("Transit", "Van", 2019, 60_000));
        mock.add(new Veiculo("EcoSport", "SUV", 2020, 55_000));
        mock.add(new Veiculo("C-Max", "Hatchback", 2018, 70_000));
        mock.add(new Veiculo("GT", "Coupe", 2020, 20_000));
        mock.add(new Veiculo("Maverick", "Pickup", 2021, 15_000));
        mock.add(new Veiculo("Puma", "SUV", 2020, 40_000));
        mock.add(new Veiculo("Puma", "SUV", 2020, 40_000));
        return mock;
    }
}

class Veiculo implements Comparable<Veiculo> {
    private String modelo;
    private String categoria;
    private int ano;
    private int kmRodados;

    Veiculo(String modelo, String categoria, int ano, int kmRodados) {
        this.modelo = modelo;
        this.categoria = categoria;
        this.ano = ano;
        this.kmRodados = kmRodados;
    }

    public String getModelo() { return this.modelo; }
    public String getCategoria() { return this.categoria; }
    public int getAno() { return this.ano; }
    public int getKmRodados() { return this.kmRodados; }

    @Override
    public String toString() {return "Modelo: " + this.getModelo() + ", Categoria: " + this.getCategoria() + ", Ano: " + this.getAno() + ", Kilometros Rodados: " + this.getKmRodados(); }

    @Override
    public int compareTo(Veiculo outro) {
        int aux = this.getCategoria().toLowerCase().compareTo(outro.getCategoria().toLowerCase());
        if (aux != 0) return aux;
        return this.getModelo().toLowerCase().compareTo(outro.getModelo().toLowerCase());
    }

    @Override
    public boolean equals(Object o) {
        Veiculo outro = (Veiculo) o;
        return this.getModelo().equals(outro.getModelo()) && this.getCategoria().equals(outro.getCategoria()) && this.getAno() == outro.getAno() && this.getKmRodados() == outro.getKmRodados();
    }

    @Override
    public int hashCode() {
        String veiculo_completo = this.modelo + this.categoria + this.ano + this.kmRodados;
        return veiculo_completo.hashCode();
    }
}

class Exer1 {
    public static void main(String[] args) {
        ordenar();

        hashset();
    }

    public static void ordenar() {
        ArrayList<Veiculo> veiculos = GetVeiculos.MockArrayList();

        System.out.println("\nAntes de ordenar:");
        imprimirColecao(veiculos);

        Collections.sort(veiculos);

        System.out.println("\nDepois de ordenar:");
        imprimirColecao(veiculos);
    }

    public static void hashset() {
        ArrayList<Veiculo> veiculos = GetVeiculos.MockArrayList();

        Set<Veiculo> conjuntoDeVeiculos = new HashSet<>(veiculos);

        System.out.println("\nHashSet:");
        imprimirColecao(conjuntoDeVeiculos);
    }

    public static <T> void imprimirColecao(Collection<T> colecao) {
        for (T c : colecao) {
            System.out.println(c);
        }
    }
}