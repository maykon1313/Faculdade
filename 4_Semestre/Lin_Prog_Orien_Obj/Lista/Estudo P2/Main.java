import java.util.*;

class Curso implements Comparable<Curso> {
    private String nome;
    private int cargaHoraria;
    private String dificuldade;

    Curso(String nome, int cargaHoraria, String dificuldade) {
        this.nome = nome;
        this.cargaHoraria = cargaHoraria;
        this.dificuldade = dificuldade;
    }

    public String getNome() { return this.nome; }
    public int getCargaHoraria() { return this.cargaHoraria; }
    public String getDificuldade() { return this.dificuldade; }

    @Override
    public String toString() { return "Nome: " + this.nome +", Carga Horária: " + cargaHoraria + ", dificuldade:'" + dificuldade + '.'; }

    @Override
    public int compareTo(Curso outroCurso) {
        return this.nome.compareTo(outroCurso.getNome());
    }
}

class ComparadorPorNivel implements Comparator<Curso> {
    @Override
    public int compare(Curso c1, Curso c2) {
        int ordem1 = getOrdem(c1.getNivel());
        int ordem2 = getOrdem(c2.getNivel());
        return Integer.compare(ordem1, ordem2);
    }

    private int getOrdem(String nivel) {
        switch (nivel) {
            case "Básico": return 1;
            case "Intermediário": return 2;
            case "Avançado": return 3;
            default: return 4;
        }
    }
}

class ComparadorPorCargaHoraria implements Comparator<Curso> {
    @Override
    public int compare(Curso c1, Curso c2) {
        return Integer.compare(c1.getCargaHoraria(), c2.getCargaHoraria());
    }
}

class Gerenciador<T> {
    private List<T> itens = new ArrayList<>();

    public void adicionar(T item) {
        itens.add(item);
    }

    public void listar() {
        for (T item : itens) {
            System.out.println(item);
        }
    }

    public void ordenar(Comparator<T> comparator) {
        Collections.sort(itens, comparator);
    }

    public void ordenarPadrao() {
    }
}

public class Main {
    public static void main(String[] args) {

    }
}
