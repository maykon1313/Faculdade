package Aula_6_Revisao_P1;

public class Main {
    public static void main(String[] args) {
        Coordenada2D p1 = new Coordenada2D();
        p1.setX(3);
        p1.setY(7);

        Coordenada2D p2 = new Coordenada2D();
        p2.setX(10);
        p2.setY(4);

        p1.mover();

        p1.mover(p2);

        System.out.println("São iguais? " + p1.equals(p2));
        System.out.println("Distância? " + p1.distancia(p2));
        
        p1.mover(4, 7);

        System.out.println("São iguais? " + p1.equals(p2));
        System.out.println("Distância? " + p1.distancia(p2));

        System.out.println("P1: " + p1.toString());
        System.out.println("P2: " + p2.toString());

        Circulo c = new Circulo();
        Quadrado q = new Quadrado();
        Reta r1 = new Reta();
        Reta r2 = new Reta();

        c.setCentro(p1);
        c.setRaio(2);
        q.setCentro(p2);
        q.setLado(2);
        
        r1.setA(2);
        r1.setB(1);
    
        r2.setA(17);
        r2.setB(-14);
    
        System.out.println(c.toString());
        System.out.println(q.toString());
        System.out.println(r1.toString());
        System.out.println(r2.toString());

        Coordenada2D inter = (Coordenada2D) (r1.interseccao(r2));
        System.out.println(inter.toString());
    }
}