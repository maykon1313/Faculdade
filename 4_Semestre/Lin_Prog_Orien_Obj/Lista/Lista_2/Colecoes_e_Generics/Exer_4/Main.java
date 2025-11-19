package Colecoes_e_Generics.Exer_4;

public class Main {
    public static void main(String[] args) {
        Gerenciador<Curso> gerenciador = new Gerenciador<>();
        gerenciador.adicionar(new Curso("Java Básico", 40, "Básico"));
        gerenciador.adicionar(new Curso("Python Avançado", 60, "Avançado"));
        gerenciador.adicionar(new Curso("C# Intermediário", 50, "Intermediário"));
        gerenciador.adicionar(new Curso("JavaScript", 30, "Intermediário"));
        gerenciador.adicionar(new Curso("SQL", 20, "Básico"));

        System.out.println("Cursos originais:");
        gerenciador.listar();

        System.out.println("\nOrdenados por nome (padrão):");
        gerenciador.ordenarPadrao();
        gerenciador.listar();

        System.out.println("\nOrdenados por carga horária:");
        gerenciador.ordenar(new ComparadorPorCargaHoraria());
        gerenciador.listar();

        System.out.println("\nOrdenados por nível:");
        gerenciador.ordenar(new ComparadorPorNivel());
        gerenciador.listar();
    }
}