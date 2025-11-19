package Exer_5_a_9;

public class PrestadorServico extends Profissional {
    private int horasTrabalhadas;
    private double valorHora;

    public PrestadorServico(double valorHora) {
        super();
        this.valorHora = valorHora;
    }

    public PrestadorServico(String nome, String documentos, int horasTrabalhadas, double valorHora) {
        super(nome, documentos, 0);
        this.horasTrabalhadas = horasTrabalhadas;
        this.valorHora = valorHora;
    }

    @Override
    public double calcularSalarioFinal() {
        return this.horasTrabalhadas * this.valorHora;
    }

    @Override
    public String toString() {
        return "Nome: " + this.getNome() + ", Documentos: " + this.getDocumentos() + ", Salário base: " + this.getSalarioBase() + ", Horas trabalhadas: " + this.horasTrabalhadas + ", Valor Hora: " + this.valorHora;
    }
}
