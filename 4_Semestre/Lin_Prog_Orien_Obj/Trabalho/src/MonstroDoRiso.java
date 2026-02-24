package src;

// Subclasse Monstro de Riso
public final class MonstroDoRiso extends Monstro {
    public MonstroDoRiso(String nome) {
        super(nome);
    } // Contrutor que usa o construtor da classe que extende

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + " | Eficiência: " + String.format("%.4f", this.getEficiencia()) + " | Tipo: Riso";
    } // Sobrescrita do Método da class Object
}
