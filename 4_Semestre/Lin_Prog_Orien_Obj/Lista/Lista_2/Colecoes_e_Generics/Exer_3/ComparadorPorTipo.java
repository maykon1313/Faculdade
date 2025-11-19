package Colecoes_e_Generics.Exer_3;

import java.util.Comparator;

public class ComparadorPorTipo implements Comparator<Pessoa> {
    @Override
    public int compare(Pessoa p1, Pessoa p2) {
        return p1.getTipo().compareTo(p2.getTipo());
    }
}