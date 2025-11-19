package Colecoes_e_Generics.Exer_2;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Catalogo<T> {
    private List<T> itens = new ArrayList<>();

    public void adicionar(T item) {
        itens.add(item);
    }

    public void listarTodos() {
        for (T item : itens) {
            System.out.println(item);
        }
    }

    public void ordenar(Comparator<T> comparator) {
        Collections.sort(itens, comparator);
    }
}