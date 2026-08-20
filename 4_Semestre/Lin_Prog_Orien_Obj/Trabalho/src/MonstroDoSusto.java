package src;

// Subclasse Monstro do Susto
public final class MonstroDoSusto extends Monstro {
    public MonstroDoSusto(String nome) {
        super(nome);
    } // Contrutor que usa o construtor da classe que extende

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + " | Eficiência: " + String.format("%.4f", this.getEficiencia()) + " | Tipo: Susto";
    } // Sobrescrita do Método da class Object
}
