package Exer_1_a_4;

public class Moto extends Veiculo {
    private boolean temBau;
    
    public Moto(boolean temBau) {
        this.temBau = temBau;
    }

    public Moto(String marca, String modelo, int ano, boolean temBau) {
        super(marca, modelo, ano);
        this.temBau = temBau;
    }

    @Override
    public String toString() {
        return "Marca: " + this.getMarca() + ", Modelo: " + this.getModelo() + ", Ano: " + this.getAno() + ", Possui Baú: " + this.temBau + ".";
    }
}
