package Colecoes_e_Generics.Exer_2;

public class Main {
    public static void main(String[] args) {
        Catalogo<Produto> catalogo = new Catalogo<>();
        catalogo.adicionar(new Produto("Notebook", 2500.0, "Eletrônicos"));
        catalogo.adicionar(new Produto("Livro", 50.0, "Livros"));
        catalogo.adicionar(new Produto("Mouse", 30.0, "Eletrônicos"));

        System.out.println("Produtos originais:");
        catalogo.listarTodos();

        System.out.println("\nOrdenado por nome:");
        catalogo.ordenar(new ComparadorPorNome());
        catalogo.listarTodos();

        System.out.println("\nOrdenado por preço:");
        catalogo.ordenar(new ComparadorPorPreco());
        catalogo.listarTodos();

        System.out.println("\nOrdenado por categoria:");
        catalogo.ordenar(new ComparadorPorCategoria());
        catalogo.listarTodos();
    }
}