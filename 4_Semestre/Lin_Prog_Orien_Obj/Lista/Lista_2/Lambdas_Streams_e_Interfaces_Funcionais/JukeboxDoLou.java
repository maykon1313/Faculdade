package Lambdas_Streams_e_Interfaces_Funcionais;

import java.util.*;
import java.util.stream.Collectors;

public class JukeboxDoLou {
    public static void main(String[] args) {
        List<Musica> musicas = Arrays.asList(
            new Musica("Song1", "Artist1", "Rock", 1995, 10),
            new Musica("Song2", "Artist2", "Pop", 2005, 20),
            new Musica("Song3", "Artist1", "Pop", 2010, 15),
            new Musica("Song4", "Artist3", "Jazz", 1980, 5),
            new Musica("Song1", "Artist4", "Pop", 2020, 25),
            new Musica("Song5", "Artist2", "Rock", 1990, 8)
        );
        
        // a. 5 músicas mais tocadas
        List<Musica> top5 = musicas.stream()
            .sorted(Comparator.comparingInt(Musica::getVezesTocada).reversed())
            .limit(5)
            .collect(Collectors.toList());
        System.out.println("Top 5 músicas mais tocadas:");
        top5.forEach(System.out::println);
        
        // b. Música mais antiga e mais recente
        Musica maisAntiga = musicas.stream()
            .min(Comparator.comparingInt(Musica::getAno))
            .orElse(null);
        Musica maisRecente = musicas.stream()
            .max(Comparator.comparingInt(Musica::getAno))
            .orElse(null);
        System.out.println("Mais antiga: " + maisAntiga);
        System.out.println("Mais recente: " + maisRecente);
        
        // c. Músicas clássicas (<2000), ordenadas por gênero
        List<Musica> classicas = musicas.stream()
            .filter(m -> m.getAno() < 2000)
            .sorted(Comparator.comparing(Musica::getGenero))
            .collect(Collectors.toList());
        System.out.println("Músicas clássicas ordenadas por gênero:");
        classicas.forEach(System.out::println);
        
        // d. Número de artistas únicos
        long artistasUnicos = musicas.stream()
            .map(Musica::getArtista)
            .distinct()
            .count();
        System.out.println("Artistas únicos: " + artistasUnicos);
        
        // e. Músicas POP em ordem decrescente (ignorando case)
        List<Musica> popDesc = musicas.stream()
            .filter(m -> "pop".equalsIgnoreCase(m.getGenero()))
            .sorted(Comparator.comparing(Musica::getNome, String.CASE_INSENSITIVE_ORDER).reversed())
            .collect(Collectors.toList());
        System.out.println("Músicas POP em ordem decrescente:");
        popDesc.forEach(System.out::println);
        
        // f. Músicas com mesmo nome, artistas diferentes
        Map<String, List<Musica>> porNome = musicas.stream()
            .collect(Collectors.groupingBy(Musica::getNome));
        System.out.println("Músicas com mesmo nome, artistas diferentes:");
        porNome.entrySet().stream()
            .filter(e -> e.getValue().size() > 1)
            .forEach(e -> {
                Set<String> artistas = e.getValue().stream()
                    .map(Musica::getArtista)
                    .collect(Collectors.toSet());
                if (artistas.size() > 1) {
                    System.out.println(e.getKey() + ": " + artistas);
                }
            });
    }
}