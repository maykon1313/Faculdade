package Exer_5_a_9;

public class Gerente extends FuncionarioCLT {
    private double gratificacaoGerencia;

    public Gerente(double gratificacaoGerencia) {
        super(0.0);
        this.gratificacaoGerencia = gratificacaoGerencia;
    }

    public Gerente(String nome, String documentos, double salarioBase, double gratificacaoGerencia) {
        super(nome, documentos, salarioBase, 0.0);
        this.gratificacaoGerencia = gratificacaoGerencia;
    }
    
    @Override
    public double calcularSalarioFinal() {
        return this.getSalarioBase() + this.getBonus() +  this.gratificacaoGerencia;
    }

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + ", Documentos: " + this.getDocumentos() + ", Salário base: " + this.getSalarioBase() + ", Bônus: " + this.getBonus() + ", Graticação: " + this.gratificacaoGerencia + ".";
    }
}
