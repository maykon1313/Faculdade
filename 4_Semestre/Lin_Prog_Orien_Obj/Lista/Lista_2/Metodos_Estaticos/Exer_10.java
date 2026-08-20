package Metodos_Estaticos;

import java.util.*;

class ContadorObjetos {
    private static int totalCriado;
    private int id;

    ContadorObjetos() {
        id = totalCriado;
        totalCriado++;
    }

    public int getId() { return this.id; }

    public static int getTotalCriado() { return totalCriado; }
    public static void resetTotalCriado() { totalCriado = 0; }
}

class Util {
    public static boolean ePar(int x) { return x%2 == 0; }
    public static int maior(int a, int b) { return a > b ? a : b; }
}

public class Exer_10 {
    public static void main(String[] args) {
        List<ContadorObjetos> l = new ArrayList<>();

        ContadorObjetos o1 = new ContadorObjetos();
        ContadorObjetos o2 = new ContadorObjetos();
        ContadorObjetos o3 = new ContadorObjetos();

        l.add(o1);
        l.add(o2);
        l.add(o3);

        for (ContadorObjetos o : l) {
            System.out.println("ID: " + o.getId() + '.');
        }

        System.out.println("ID Total: " + ContadorObjetos.getTotalCriado() + '.');

        ContadorObjetos.resetTotalCriado();

        ContadorObjetos o4 = new ContadorObjetos();
        ContadorObjetos o5 = new ContadorObjetos();

        l.add(o4);
        l.add(o5);

        for (int i = 3; i < 5; i++) {
            ContadorObjetos o = l.get(i);
            System.out.println("ID: " + o.getId() + '.');
        }

        System.out.println("ID Total: " + ContadorObjetos.getTotalCriado() + '.');

        int a = 3;
        int b = 4;
        System.out.println("Maior valor entre: " + a + " e " + b + '.');
        System.out.println("O maior valor entre é: " + Util.maior(a, b) + '.');
    
        System.out.println(a + " é par? " + Util.ePar(a) + '.');
        System.out.println(b + " é par? " + Util.ePar(b) + '.');
    }
}
