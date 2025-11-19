package Colecoes_e_Generics.Exer_5;

import java.util.Objects;

public class Veiculo implements Comparable<Veiculo> {
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