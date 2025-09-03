class Funcionario {
    private String nome;
    private double salario;
    
    void setNome(String n) {
        nome = n;
    }
    
    void setSalario(Double n) {
        salario = n;
    }

    String getNome() {
        return nome;
    }
    
    double getSalario() {
        return salario;
    }

    void addAumento(double valor) {
        salario = salario + valor;
    }

    double ganhoAnual() {
        return salario * 12;
    }

    void exibeDados() {
        System.out.print("Nome: " + nome + ".\n");
        System.out.print("Salario: " + salario + ".\n");
    }
}

class Assitente extends Funcionario {
    private int numeroMatricula;

    void setNumeroMatricula(int n) {
        numeroMatricula = n;
    }

    int getNumeroMatricula() {
        return numeroMatricula;
    }

    void exibeDados() {
        super.exibeDados();
        System.out.print("Matrícula: " + numeroMatricula + ".\n");
    }
}

public class Salario {
    public static void main(String[] args) {
        Funcionario n1 = new Funcionario();
        Assitente n2 = new Assitente();

        n1.setNome("Bob");
        n1.setSalario(1200.0);

        n1.exibeDados();

        n2.setNome("Robson");
        n2.setSalario(120.0);
        n2.setNumeroMatricula(123);

        n2.exibeDados();
    }
}