package Colecoes_e_Generics.Exer_3;

public class Funcionario extends Pessoa {
    private double salario;

    public Funcionario(String nome, int idade, double salario) {
        super(nome, idade);
        this.salario = salario;
    }

    public double getSalario() { return salario; }

    @Override
    public String getTipo() { return "Funcionario"; }

    @Override
    public String toString() {
        return super.toString() + ", salario=" + salario + "}";
    }
}