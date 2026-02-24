package Colecoes_e_Generics;

import java.util.*;

abstract class Pessoa {
    private String nome;
    private int idade;

    Pessoa(String nome, int idade) {
        this.nome = nome;
        this.idade = idade;
    }

    public String getNome() { return this.nome; }
    public int getIdade() { return this.idade; }

    @Override
    public String toString() { return "Nome: " + this.nome + ", Idade: " + this.idade + '.'; }

    public abstract String getTipo();
}

class Funcionario extends Pessoa {
    private double salario;

    Funcionario(String nome, int idade, double salario) {
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

class Cliente extends Pessoa {
    private String email;

    Cliente(String nome, int idade, String email) {
        super(nome, idade);
        this.email = email;
    }

    public String getEmail() { return email; }

    @Override
    public String getTipo() { return "Cliente"; }

    @Override
    public String toString() {
        return super.toString() + ", email='" + email + "'}";
    }
}

class Fornecedor extends Pessoa {
    private String empresa;

    Fornecedor(String nome, int idade, String empresa) {
        super(nome, idade);
        this.empresa = empresa;
    }

    public String getEmpresa() { return empresa; }

    @Override
    public String getTipo() { return "Fornecedor"; }

    @Override
    public String toString() {
        return super.toString() + ", empresa='" + empresa + "'}";
    }
}

class Cadastro<T extends Pessoa> {
    private ArrayList<T> pessoas = new ArrayList<>();

    public void adicionar(T pessoa) {
        pessoas.add(pessoa);
    }

    public void listar() {
        for (T pessoa : pessoas) {
            System.out.println(pessoa);
        }
    }

    public void ordenar(Comparator<T> comparator) {
        Collections.sort(pessoas, comparator);
    }
}

class CompararPessoaPorNome implements Comparator<Pessoa> {
    @Override
    public int compare(Pessoa p1, Pessoa p2) {
        return p1.getNome().compareTo(p2.getNome());
    }
}

class CompararPessoaPorIdade implements Comparator<Pessoa> {
    @Override
    public int compare(Pessoa p1, Pessoa p2) {
        return Integer.compare(p1.getIdade(), p2.getIdade());
    }
}

class CompararPessoaPorTipo implements Comparator<Pessoa> {
    @Override
    public int compare(Pessoa p1, Pessoa p2) {
        return p1.getTipo().compareTo(p2.getTipo());
    }
}

public class Exer_3 {
    public static void main(String[] args) {
        Cadastro<Pessoa> cadastro = new Cadastro<>();
        cadastro.adicionar(new Funcionario("João", 30, 3000.0));
        cadastro.adicionar(new Cliente("Maria", 25, "maria@email.com"));
        cadastro.adicionar(new Fornecedor("Carlos", 40, "Empresa X"));

        System.out.println("Pessoas originais:");
        cadastro.listar();

        System.out.println("\nOrdenado por nome:");
        cadastro.ordenar(new CompararPessoaPorNome());
        cadastro.listar();

        System.out.println("\nOrdenado por idade:");
        cadastro.ordenar(new CompararPessoaPorIdade());
        cadastro.listar();

        System.out.println("\nOrdenado por tipo:");
        cadastro.ordenar(new CompararPessoaPorTipo());
        cadastro.listar();
    }
}
