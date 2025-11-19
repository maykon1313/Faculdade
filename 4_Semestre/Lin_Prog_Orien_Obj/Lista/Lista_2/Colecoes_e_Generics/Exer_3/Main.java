package Colecoes_e_Generics.Exer_3;

public class Main {
    public static void main(String[] args) {
        Cadastro<Pessoa> cadastro = new Cadastro<>();
        cadastro.adicionar(new Funcionario("João", 30, 3000.0));
        cadastro.adicionar(new Cliente("Maria", 25, "maria@email.com"));
        cadastro.adicionar(new Fornecedor("Carlos", 40, "Empresa X"));

        System.out.println("Pessoas originais:");
        cadastro.listar();

        System.out.println("\nOrdenado por nome:");
        cadastro.ordenar(new ComparadorPorNome());
        cadastro.listar();

        System.out.println("\nOrdenado por idade:");
        cadastro.ordenar(new ComparadorPorIdade());
        cadastro.listar();

        System.out.println("\nOrdenado por tipo:");
        cadastro.ordenar(new ComparadorPorTipo());
        cadastro.listar();
    }
}