package Aula_5;

import java.util.ArrayList;

interface Domestico {
    public abstract void cute();
    public abstract void brinca();
}

interface Selvagem {
    public abstract void arrancaPedaco();
    public abstract void pedeMaozinha();
}

abstract class Animal {
    private String nome;
    private int fome;

    public void setNome(String n) {this.nome = n;}
    public void setFome(int n) {this.fome = n;}
    public String getNome() {return nome;}
    public int getFome() {return fome;}

    abstract public void vagar();
    abstract public void comer();
}

abstract class Canino extends Animal {
    public void uivar() {
        System.out.println("Auuuu!");
    }

    @Override
    public void vagar() {
        System.out.println("O Canino " + this.getNome() + " está vagando!");
    }
    
    @Override
    public void comer() {
        System.out.println("O Canino " + this.getNome() + " está comendo!");
    }
}

class Cachorro extends Canino implements Domestico {
    @Override
    public void vagar() {
        System.out.println("O Cachorro " + this.getNome() + " está vagando!");
    }

    public void abanaRabo() {
        System.out.println("O Cachorro " + this.getNome() + " está abanando o rabo!");
    }

    public void cute() {
        System.out.println("O Cachorro " + this.getNome() + " está existindo!");
    }

    public void brinca() {
        System.out.println("O Cachorro " + this.getNome() + " está fingindo de morto!");
    }
}

class Lobo extends Canino implements Selvagem {
    public void arrancaPedaco() {
        System.out.println("O Lobo " + this.getNome() + " quer comer!");
    }

    public void pedeMaozinha() {
        System.out.println("O Lobo " + this.getNome() + " nhack!");
    }
}

class Gato extends Animal implements Domestico {
    public void vagar() {
        System.out.println("O Gato " + this.getNome() + " está desfilando!");
    }

    public void comer() {
        if (this.getFome() > 0) {
            System.out.println("O Gato " + this.getNome() + " está degustando!");
            this.setFome(0);
        }

        else {
            System.out.println("O Gato " + this.getNome() + " está gordinho!");
        }
    }

    public void cute() {
        System.out.println("O Gato " + this.getNome() + " miau!");
    }

    public void brinca() {
        System.out.println("O Gato " + this.getNome() + " matou Cthulhu!");
    }
}

public class aula_5 {
    private static void classes() {
        Cachorro c1 = new Cachorro();
        Canino c2 = new Cachorro();
        Animal c3 = new Cachorro();
        Object c4 = new Cachorro();

        c1.setNome("Faísca");
        c1.setFome(0);

        c2.setNome("Leticia");
        c2.setFome(0);

        c3.setNome("Pedro");
        c3.setFome(0);

        //c4.setNome("Rabugento");
        //c4.setFome(0);

        c1.uivar();
        c1.vagar();
        c1.comer();
        c1.abanaRabo();
    
        c2.uivar();
        c2.vagar();
        c2.comer();
        //c2.abanaRabo();
    
        //c3.uivar();
        c3.vagar();
        c3.comer();
        //c3.abanaRabo();

        //c4.uivar();
        //c4.vagar();
        //c4.comer();
        //c4.abanaRabo();
        System.out.println(c4.getClass());
        
    }

    private static void interfaces() {
        Cachorro c1 = new Cachorro();
        Lobo l1 = new Lobo();

        c1.setNome("Faísca");
        c1.setFome(0);

        l1.setNome("Lucas");
        l1.setFome(100);

        l1.arrancaPedaco();
        l1.pedeMaozinha();

        c1.cute();
        c1.brinca();
    }

    private static void array() {
        ArrayList<Domestico> animais = new ArrayList<>();

        Cachorro c1 = new Cachorro();
        Gato g1 = new Gato();

        c1.setNome("Faísca");
        c1.setFome(0);

        g1.setNome("Bolinha de Gorfe");
        g1.setFome(1);

        animais.add(c1);
        animais.add(g1);

        g1.comer();

        for (Domestico n : animais) {
            n.brinca();
            n.cute();
        }
    }

    public static void main(String[] args) {
        classes();
        System.out.println();
        interfaces();
        System.out.println();
        array();
    }
}
