package Aula_4.Zoologico;

public class Animal {
    private String nome;
    private int idade;

    public void emitirSom() {
        System.out.println("Som de Animal.");
    }
    
    public void setNome(String n) {
        nome = n;
    }

    public void setIdade(int n) {
        idade = n;
    }

    public String getNome() {
        return nome;
    }

    public int getIdade() {
        return idade;
    }
}
