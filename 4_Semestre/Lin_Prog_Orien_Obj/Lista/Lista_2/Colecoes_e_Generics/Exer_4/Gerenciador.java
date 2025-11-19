package Colecoes_e_Generics.Exer_4;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Gerenciador<T> {
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

    @SuppressWarnings({ "unchecked", "rawtypes" })
    public void ordenarPadrao() {
        if (!itens.isEmpty() && itens.get(0) instanceof Comparable) {
            Collections.sort((List) itens);
        }
    }
}