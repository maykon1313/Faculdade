package Colecoes_e_Generics.Exer_4;

import java.util.Comparator;

public class ComparadorPorCargaHoraria implements Comparator<Curso> {
    @Override
    public int compare(Curso c1, Curso c2) {
        return Integer.compare(c1.getCargaHoraria(), c2.getCargaHoraria());
    }
}