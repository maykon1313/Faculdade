package Lambdas_Streams_e_Interfaces_Funcionais;

public class Musica {
    private String nome;
    private String artista;
    private String genero;
    private int ano;
    private int vezesTocada;
    
    public Musica(String nome, String artista, String genero, int ano, int vezesTocada) {
        this.nome = nome;
        this.artista = artista;
        this.genero = genero;
        this.ano = ano;
        this.vezesTocada = vezesTocada;
    }
    
    // Getters
    public String getNome() { return nome; }
    public String getArtista() { return artista; }
    public String getGenero() { return genero; }
    public int getAno() { return ano; }
    public int getVezesTocada() { return vezesTocada; }
    
    @Override
    public String toString() {
        return nome + " - " + artista + " (" + genero + ", " + ano + ", tocada " + vezesTocada + " vezes)";
    }
}