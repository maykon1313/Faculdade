package Exer_11;

class Produto {
    String nome;
    double preco;
    Produto(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
    }
}

public class Main {
    public static void main(String[] args) {
        int quantidade = 5;
        Produto p1 = new Produto("Café", 10.0);
        calculaTotal(p1, quantidade);

        @SuppressWarnings("unused")
        Produto p2 = criarProdutoPromocional("Açúcar");
    }

    public static void calculaTotal(Produto prod, int q) {
        double total = prod.preco * q;
        System.out.println("Total: " + total);
    }

    public static Produto criarProdutoPromocional(String nomeBase) {
        String nomePromo = nomeBase + " Promoção";
        return new Produto(nomePromo, 5.0);
    }
}
