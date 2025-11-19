package Colecoes_e_Generics.Exer_3;

public class Fornecedor extends Pessoa {
    private String empresa;

    public Fornecedor(String nome, int idade, String empresa) {
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