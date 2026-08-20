import java.util.stream.*;
import java.util.function.*;
import java.util.*;

class Musicas{
  public static List<Musica> getMusicas() {
    return List.of(
        new Musica("Somersault", "Zero 7", "Downtempo", 2004, 147),
        new Musica("Clocks", "Coldplay", "Rock Alternativo", 2002, 230),
        new Musica("Billie Jean", "Michael Jackson", "Pop", 1983, 520),
        new Musica("Smells Like Teen Spirit", "Nirvana", "Grunge", 1991, 480),
        new Musica("Shape of You", "Ed Sheeran", "Pop", 2017, 610),
        new Musica("Bohemian Rhapsody", "Queen", "Rock", 1975, 550),
        new Musica("Lose Yourself", "Eminem", "Hip Hop", 2002, 470),
        new Musica("Get Lucky", "Daft Punk", "Disco", 2013, 390),
        new Musica("Rolling in the Deep", "Adele", "Soul", 2011, 440),
        new Musica("Viva La Vida", "Coldplay", "Pop Rock", 2008, 510),
        new Musica("Hotel California", "Eagles", "Rock", 1976, 580),
        new Musica("Blinding Lights", "The Weeknd", "Synthpop", 2019, 630),
        new Musica("Bad Guy", "Billie Eilish", "Pop Alternativo", 2019, 420),
        new Musica("Wonderwall", "Oasis", "Britpop", 1995, 460),
        new Musica("Uptown Funk", "Mark Ronson ft. Bruno Mars", "Funk Pop", 2014, 570),
        new Musica("Hey Ya!", "Outkast", "Hip Hop", 2003, 495),
        new Musica("Hallelujah", "Leonard Cohen", "Folk", 1984, 350),           
        new Musica("Hallelujah", "Jeff Buckley", "Folk Rock", 1994, 400),       
        new Musica("Shallow", "Lady Gaga & Bradley Cooper", "Pop", 2018, 490),
        new Musica("Imagine", "John Lennon", "Rock", 1971, 560),
        new Musica("Imagine", "A Perfect Circle", "Rock Alternativo", 2004, 310) 
    );
  }
}

class Musica{
  private final String titulo;
  private final String artista;
  private final String genero;
  private final int ano;
  private final int vezesTocada;  
  
  public String getTitulo(){ return titulo; }
  public String getArtista(){ return artista; }
  public String getGenero(){ return genero; }
  public int getAno(){ return ano; }
  public int getVezesTocada(){ return vezesTocada; }

  public Musica(String titulo, String artista, String genero, int ano, int vezesTocada){
    this.titulo = titulo;
    this.artista = artista;
    this.genero = genero;
    this.ano = ano;
    this.vezesTocada = vezesTocada;
  }

  public String toString(){
    return "Título:"+titulo+", Artista:"+artista+", Gênero:"+genero+", Ano:"+ano+", Tocado:"+vezesTocada; 
  }
}

public class JukeboxDoLou{
  public static void main(String[] args) {
    List<Musica> musicas = Musicas.getMusicas();
    
    //exer1(musicas);
    //exer2(musicas);
    //exer3(musicas);
    //exer4(musicas);
    exer5(musicas);
  }

  static void exer1(List<Musica> musicas) {
    System.out.println("\nTodas:");
    musicas.forEach((Musica m) -> System.out.println(m));

    List<Musica> musicasDeRock = musicas.stream().filter((Musica m) -> m.getGenero().equals("Rock")).collect(Collectors.toList());
    System.out.println("\nSó rock:");
    musicasDeRock.forEach((Musica m) -> System.out.println(m));

    List<Musica> musicasComRock = musicas.stream().filter((Musica m) -> m.getGenero().contains("Rock")).collect(Collectors.toList());
    System.out.println("\nCom rock:");
    musicasComRock.forEach((Musica m) -> System.out.println(m));

    List<Musica> musicasComImagine = musicas.stream().filter((Musica m) -> m.getTitulo().contains("Imagine")).collect(Collectors.toList());
    System.out.println("\nCom Imagine:");
    musicasComImagine.forEach((Musica m) -> System.out.println(m));
  }

  static void exer2(List<Musica> musicas) {
    //List<String> generosMusicais = musicas.stream().map((Musica m) -> m.getGenero()).distinct().sorted().collect(Collectors.toList());
    
    Set<String> generosMusicais = musicas.stream().map((Musica m) -> m.getGenero()).collect(Collectors.toSet());

    System.out.println("\nGêneros das músicas:");
    generosMusicais.forEach((String s) -> System.out.println(s));
  }

  static void exer3(List<Musica> musicas) {
    Function<Musica, String> getGenero = Musica::getGenero;
    Set<String> generosMusicais = musicas.stream().map(getGenero).collect(Collectors.toSet());
    System.out.println("\nGêneros das músicas:");
    generosMusicais.forEach((String s) -> System.out.println(s));
  }

  static void exer4(List<Musica> musicas) {
    //Optional<Musica> result = musicas.stream().filter(m -> m.getAno()==1995).findFirst();
    Optional<Musica> result = musicas.stream().filter(m -> m.getAno()==2004).findAny();

    if (result.isPresent()) System.out.println(result);
    else System.out.println("Não há batidas.");
  }

  static void exer5(List<Musica> musicas) {
    List<Musica> tocadasMusicais = musicas.stream().sorted((o1, o2)->o1.getAno() - o2.getAno()).collect(Collectors.toList());
    for (int i = 0; i < 5; i++) System.out.println(tocadasMusicais.get(i));
  }
}
