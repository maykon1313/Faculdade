package Colecoes_e_Generics.Exer_3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Cadastro<T extends Pessoa> {
    private List<T> pessoas = new ArrayList<>();

    public void adicionar(T pessoa) {
        pessoas.add(pessoa);
    }

    public void listar() {
        for (T pessoa : pessoas) {
            System.out.println(pessoa);
        }
    }

    public void ordenar(Comparator<T> comparator) {
        Collections.sort(pessoas, comparator);
    }
}