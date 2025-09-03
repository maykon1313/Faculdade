// Superclasse
class Veiculo {
    String marca;
    String modelo;
    int ano;

    public Veiculo(String marca, String modelo, int ano) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
    }

    public void exibirInformacoes() {
        System.out.println("Marca: " + marca);
        System.out.println("Modelo: " + modelo);
        System.out.println("Ano: " + ano);
    }
}

// Subclasse
// Subclasse com método sobrescrito
class Carro extends Veiculo {
    int numeroDePortas;

    public Carro(String marca, String modelo, int ano, int numeroDePortas) {
        super(marca, modelo, ano);
        this.numeroDePortas = numeroDePortas;
    }

    @Override // Anotação de sobrescrita
    public void exibirInformacoes() {
        super.exibirInformacoes(); // Chama o método original da superclasse
        System.out.println("Número de Portas: " + numeroDePortas);
    }
}

public class Heranca {
    public static void main(String[] args) {
        // Criando um objeto da superclasse
        Veiculo meuVeiculo = new Veiculo("Toyota", "Corolla", 2022);
        System.out.println("--- Informações do Veículo Genérico ---");
        meuVeiculo.exibirInformacoes();

        System.out.println("\n---------------------------------------\n");

        // Criando um objeto da subclasse
        Carro meuCarro = new Carro("Honda", "Civic", 2023, 4);
        System.out.println("--- Informações do Carro ---");
        meuCarro.exibirInformacoes(); // Chama o método sobrescrito em Carro
    }
}