class Produto {
    private String nome;
    private double preco;
    private int quantidade;

    public Produto(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
        this.quantidade = 0;
    }

    public Produto(String nome, double preco, int quantidade) {
        this.nome = nome;
        this.preco = preco;
        this.quantidade = quantidade;
    }

    public void setNome(String nome) { this.nome = nome; }
    public void setPreco(double preco) { this.preco = preco; }
    public void setQuantidade(int quantidade) { this.quantidade = quantidade; }
    public String getNome() { return this.nome; }
    public Double getPreco() { return this.preco; }
    public int getQuantidade() { return this.quantidade; }

    public void exibirInfo() { System.out.println("Produto: [" + this.nome + "], Preço: R$[" + this.preco + "], Quantidade: [" + this.quantidade + "]"); }

    public void adicionarEstoque(int qtd) { this.quantidade = this.quantidade + qtd; }
    public void removerEstoque(int qtd) {
        int aux = this.quantidade - qtd;
        if (aux >= 0) {
            this.quantidade = aux;
        } else {
            System.out.println("Não.");
        }
    }
}

public class Exercicio {
    public static void main(String[] Args) {
        Produto caneta = new Produto("Caneta", 10);
        Produto lapis = new Produto("Lápis", 5, 20);

        caneta.exibirInfo();
        lapis.exibirInfo();

        caneta.adicionarEstoque(12);
        lapis.removerEstoque(5);
        
        caneta.exibirInfo();
        lapis.exibirInfo();
    }
}
