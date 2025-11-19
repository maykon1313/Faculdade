package Exer_1_a_4;

public class Carro extends Veiculo {
    private int portas;

    public Carro(int portas) {
        super();
        this.portas = portas;
    }

    public Carro(String marca, String modelo, int ano, int portas) {
        super(marca, modelo, ano);
        this.portas = portas;
    }

    @Override
    public String toString() {
        return "Marca: " + this.getMarca() + ", Modelo: " + this.getModelo() + ", Ano: " + this.getAno() + ", Número de portas: " + this.portas + ".";
    }
}
