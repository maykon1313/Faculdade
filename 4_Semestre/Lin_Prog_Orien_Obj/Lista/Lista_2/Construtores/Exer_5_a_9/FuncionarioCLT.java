package Exer_5_a_9;

public class FuncionarioCLT extends Profissional {
    private double bonus;

    public FuncionarioCLT(double bonus) {
        super();
        this.bonus = bonus;
    }

    public FuncionarioCLT(String nome, String documentos, double salarioBase, double bonus) {
        super(nome, documentos, salarioBase);
        this.bonus = bonus;
    }

    public double getBonus() { return this.bonus; }

    @Override
    public double calcularSalarioFinal() {
        return this.getSalarioBase() + this.bonus;
    }

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + ", Documentos: " + this.getDocumentos() + ", Salário base: " + this.getSalarioBase() + ", Bônus: " + this.bonus + ".";
    }
}
