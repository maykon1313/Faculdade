package Aula_8;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

class comparaTitulo implements Comparator<Musica> {
    @Override
    public int compare(Musica m1, Musica m2) {
        return m1.getTitulo().toLowerCase().compareTo(m2.getTitulo().toLowerCase());
    }
}

class comparaArtista implements Comparator<Musica> {
    @Override
    public int compare(Musica m1, Musica m2) {
        return m1.getArtista().toLowerCase().compareTo(m2.getArtista().toLowerCase());
    }
}

class comparaBpm implements Comparator<Musica> {
    @Override
    public int compare(Musica m1, Musica m2) {
        return Integer.compare(m2.getBpm(), m1.getBpm());
    }
}

class Musica implements Comparable<Musica> {
    private String titulo;
    private String artista;
    private int bpm;

    Musica(String titulo, String artista, int bpm) {
        this.titulo = titulo;
        this.artista = artista;
        this.bpm = bpm;
    }

    public int compareTo(Musica m) {return titulo.toLowerCase().compareTo(m.getTitulo().toLowerCase());}

    public String getTitulo() {return this.titulo;}
    public String getArtista() {return this.artista;}
    public int getBpm() {return this.bpm;}

    @Override
    public String toString() {
        return this.titulo + "|" + this.artista + "|" + this.bpm;
    }
}

class MockMusicas {
    public static List<Musica> getMusicas() {
        List<Musica> musicas = new ArrayList<>();

        musicas.add(new Musica("somersault","zero 7", 147));
        musicas.add(new Musica("cassidy","grateful dead", 158));
        musicas.add(new Musica("$10","hitchhiker", 140));
        musicas.add(new Musica("havana","cabello", 105));
        musicas.add(new Musica("Cassidy","grateful dead", 158));
        musicas.add(new Musica("$50 Ways","simon", 102));

        return musicas;
    }
}

public class Jukebox {
    public static void main(String[] args) {
        new Jukebox();
    }

    public Jukebox() {
        List<Musica> listaMusicas = MockMusicas.getMusicas();
        System.out.println(listaMusicas);

        Collections.sort(listaMusicas);
        System.out.println(listaMusicas);

        Collections.sort(listaMusicas, new comparaTitulo());
        System.out.println(listaMusicas);

        Collections.sort(listaMusicas, new comparaArtista());
        System.out.println(listaMusicas);

        Collections.sort(listaMusicas, new comparaBpm());
        System.out.println(listaMusicas);
    }
}
