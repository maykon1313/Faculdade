package Colecoes_e_Generics.Exer_2;

import java.util.Comparator;

public class ComparadorPorNome implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getNome().compareTo(p2.getNome());
    }
}