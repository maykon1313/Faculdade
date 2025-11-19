package Exer_1_a_4;

public class Veiculo {
    private String marca;
    private String modelo;
    private int ano;
    
    public Veiculo() {
        this.marca = "Desconhecido";
        this.modelo = "Genérico";
        this.ano = 2000;
    }

    public Veiculo(String marca, String modelo, int ano) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
    }

    public String getMarca() { return this.marca; }
    public String getModelo() { return this.modelo; }
    public int getAno() { return this.ano; }

    @Override
    public String toString() {
        return "Marca: " + this.marca + ", Modelo: " + this.modelo + ", Ano: " + this.ano + ".";
    }
}
