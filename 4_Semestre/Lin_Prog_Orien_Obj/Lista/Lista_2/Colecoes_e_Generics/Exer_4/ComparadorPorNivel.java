package Colecoes_e_Generics.Exer_4;

import java.util.Comparator;

public class ComparadorPorNivel implements Comparator<Curso> {
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