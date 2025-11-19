package Colecoes_e_Generics.Exer_3;

public class Cliente extends Pessoa {
    private String email;

    public Cliente(String nome, int idade, String email) {
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