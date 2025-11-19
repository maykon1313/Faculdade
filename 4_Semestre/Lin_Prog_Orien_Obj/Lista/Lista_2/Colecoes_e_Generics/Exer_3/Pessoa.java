package Colecoes_e_Generics.Exer_3;

public abstract class Pessoa {
    protected String nome;
    protected int idade;

    public Pessoa(String nome, int idade) {
        this.nome = nome;
        this.idade = idade;
    }

    public String getNome() { return nome; }
    public int getIdade() { return idade; }

    @Override
    public String toString() {
        return "Pessoa{nome='" + nome + "', idade=" + idade + ", tipo='" + getTipo() + "'}";
    }

    public abstract String getTipo();
}