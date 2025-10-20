package Aula_4.Zoologico;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<Animal> zoo = new ArrayList<Animal>();

        Cachorro d = new Cachorro();
        Gato g = new Gato();
        Passaro p = new Passaro();

        d.setNome("Caramelo");
        d.setIdade(12);

        zoo.add(d);

        g.setNome("Melo");
        g.setIdade(1);

        zoo.add(g);

        p.setNome("Beto");
        p.setIdade(5);

        zoo.add(p);

        for (Animal n : zoo) {
            System.out.println("O animal nomeado " + n.getNome() + " de idade " + n.getIdade() + " emitiu: ");
            n.emitirSom();
        }
    }
}
