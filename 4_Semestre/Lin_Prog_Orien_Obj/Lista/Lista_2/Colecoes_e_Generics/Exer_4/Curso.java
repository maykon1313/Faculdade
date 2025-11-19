package Colecoes_e_Generics.Exer_4;

public class Curso implements Comparable<Curso> {
    private String nome;
    private int cargaHoraria;
    private String nivel;

    public Curso(String nome, int cargaHoraria, String nivel) {
        this.nome = nome;
        this.cargaHoraria = cargaHoraria;
        this.nivel = nivel;
    }

    public String getNome() { return nome; }
    public int getCargaHoraria() { return cargaHoraria; }
    public String getNivel() { return nivel; }

    @Override
    public String toString() {
        return "Curso{nome='" + nome + "', cargaHoraria=" + cargaHoraria + ", nivel='" + nivel + "'}";
    }

    @Override
    public int compareTo(Curso outro) {
        return this.nome.compareTo(outro.nome);
    }
}