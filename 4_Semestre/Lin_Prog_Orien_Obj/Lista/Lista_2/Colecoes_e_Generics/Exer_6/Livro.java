package Colecoes_e_Generics.Exer_6;

import java.util.Objects;

public class Livro implements Comparable<Livro> {
    private String titulo;
    private String autor;
    private String categoria;
    private int anoPublicado;
    private int paginasLidas;

    public Livro(String titulo, String autor, String categoria, int anoPublicado, int paginasLidas) {
        this.titulo = titulo;
        this.autor = autor;
        this.categoria = categoria;
        this.anoPublicado = anoPublicado;
        this.paginasLidas = paginasLidas;
    }

    public String getTitulo() { return titulo; }
    public String getAutor() { return autor; }
    public String getCategoria() { return categoria; }
    public int getAnoPublicado() { return anoPublicado; }
    public int getPaginasLidas() { return paginasLidas; }

    @Override
    public String toString() {
        return "Livro{titulo='" + titulo + "', autor='" + autor + "', categoria='" + categoria + "', ano=" + anoPublicado + ", paginasLidas=" + paginasLidas + "}";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Livro livro = (Livro) obj;
        return anoPublicado == livro.anoPublicado && paginasLidas == livro.paginasLidas &&
               Objects.equals(titulo, livro.titulo) && Objects.equals(autor, livro.autor) &&
               Objects.equals(categoria, livro.categoria);
    }

    @Override
    public int hashCode() {
        return Objects.hash(titulo, autor, categoria, anoPublicado, paginasLidas);
    }

    @Override
    public int compareTo(Livro outro) {
        int cmp = this.categoria.compareTo(outro.categoria);
        if (cmp == 0) {
            cmp = this.autor.compareTo(outro.autor);
            if (cmp == 0) {
                cmp = this.titulo.compareTo(outro.titulo);
            }
        }
        return cmp;
    }
}