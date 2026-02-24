import java.util.ArrayList;
import java.util.List;

class Veiculo {
    private String marca;
    private String modelo;
    private int ano;

    Veiculo() {
        this.marca = "Desconhecida";
        this.modelo = "Genérico";
        this.ano = 2000;
    }

    Veiculo(String marca, String modelo, int ano) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
    }

    public String getMarca() { return this.marca; }
    public String getModel() { return this.modelo; }
    public int getAno() { return this.ano; }

    @Override
    public String toString() { return "Marca: " + this.marca + ", Modelo: " + this.modelo + ", Ano: " + this.ano + '.'; }
}

class Carro extends Veiculo {
    private int porta;
    
    Carro() {
        super();
        this.porta = 0;
    }

    Carro(String marca, String modelo, int ano, int porta) {
        super(marca, modelo, ano);
        this.porta = porta;
    }

    @Override
    public String toString() { return "Marca: " + this.getMarca() + ", Modelo: " + this.getModel() + ", Ano: " + this.getAno() + ", Número de portas: " + this.porta + '.'; }
}

class Moto extends Veiculo {
    private boolean temBau;
    
    Moto() {
        super();
        this.temBau = false;
    }

    Moto(String marca, String modelo, int ano, boolean temBau) {
        super(marca, modelo, ano);
        this.temBau = temBau;
    }

    @Override
    public String toString() { return "Marca: " + this.getMarca() + ", Modelo: " + this.getModel() + ", Ano: " + this.getAno() + ", Possuí Baú: " + this.temBau + '.'; }
}

public class Exer1_4 {
    public static void main(String[] args) {
        List<Veiculo> l = new ArrayList<>();

        Carro c = new Carro();
        Moto m = new Moto();

        l.add(c);
        l.add(m);

        for (Veiculo v : l) {
            System.out.println(v);
        }

        c = new Carro("BMW", "Esportivo", 2016, 4);
        m = new Moto("Honda", "Anda", 2018, true);
    
        l.set(0, c);
        l.set(1, m);
        
        for (Veiculo v : l) {
            System.out.println(v);
        }
    }
}