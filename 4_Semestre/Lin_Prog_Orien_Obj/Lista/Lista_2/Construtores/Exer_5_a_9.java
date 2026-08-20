

import java.util.*;

abstract class Profissional {
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

class FuncionarioCLT extends Profissional {
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

class Gerente extends FuncionarioCLT {
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

class PrestadorServico extends Profissional {
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

class Main {
    public static void main(String[] args) {
        List<Profissional> lista = new ArrayList<>();

        PrestadorServico ps1 = new PrestadorServico(10.0);
        PrestadorServico ps2 = new PrestadorServico("João", "CPF123", 40, 15.0);

        FuncionarioCLT clt1 = new FuncionarioCLT(100.0);
        FuncionarioCLT clt2 = new FuncionarioCLT("Ana", "RG456", 2000.0, 500.0);

        Gerente g1 = new Gerente(300.0);
        Gerente g2 = new Gerente("Pedro", "CNH789", 3000.0, 800.0);

        lista.add(ps1);
        lista.add(ps2);
        lista.add(clt1);
        lista.add(clt2);
        lista.add(g1);
        lista.add(g2);

        for (Profissional p : lista) {
            System.out.println(p);
            System.out.println(p.calcularSalarioFinal());
        }
    }
}