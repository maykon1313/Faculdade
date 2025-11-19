package Colecoes_e_Generics.Exer_3;

import java.util.Comparator;

public class ComparadorPorIdade implements Comparator<Pessoa> {
    @Override
    public int compare(Pessoa p1, Pessoa p2) {
        return Integer.compare(p1.getIdade(), p2.getIdade());
    }
}