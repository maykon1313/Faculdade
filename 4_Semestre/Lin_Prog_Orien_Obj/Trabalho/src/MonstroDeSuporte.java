package src;

public final class MonstroDeSuporte extends Monstro {
    public MonstroDeSuporte(String nome){
        super(nome);
    } // Contrutor que usa o construtor da classe que extende

    public int receberEnergia(int energia, Cilindro c) throws IllegalStateException, IllegalArgumentException {
        if (energia < 0) {
            throw new IllegalArgumentException("Energia recebida deve ser não negativa.");
        }
        int energia_real = energia + (int) (Math.random() * energia * this.getEficiencia());
        int armazenou = c.armazenarEnergia(energia_real);

        if (armazenou == 1) {
            System.out.println("\nAVISO - Cilindro " + c.getId() + " está cheio. Armazenamento máximo atingido.");
            return -1;
        }

        else {
            System.out.println(getNome() + " armazenou " + energia_real + " unidades de energia no cilindro " + c.getId() + ".");
            return energia_real;
        }
    } // Método para armazenar energia recebida no cilindro, e aplicando a própria eficiência

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + " | Eficiência: " + String.format("%.4f", this.getEficiencia()) + " | Tipo: Suporte";
    } // Sobrescrita do Método da class Object
}
