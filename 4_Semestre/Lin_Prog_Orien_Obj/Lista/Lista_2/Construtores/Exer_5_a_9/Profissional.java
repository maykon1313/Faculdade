package Exer_5_a_9;

public abstract class Profissional {
    private String nome;
    private String documentos;
    private double salarioBase;

    public Profissional() {
        this.nome = "Noname";
        this.documentos = "N/A";
        this.salarioBase = 0.0;
    }

    public Profissional(String nome, String documentos, double salarioBase) {
        this.nome = nome;
        this.documentos = documentos;
        this.salarioBase = salarioBase;
    }

    public String getNome() { return this.nome; }
    public String getDocumentos() { return this.documentos; }
    public double getSalarioBase() { return this.salarioBase; }

    @Override
    public String toString() {
        return "Nome: " + this.nome + ", Documentos: " + this.documentos + ", Salário base: " + this.salarioBase + ".";
    }

    public abstract double calcularSalarioFinal();
}
