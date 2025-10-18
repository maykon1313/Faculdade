package P1_a;

class Coordenada2D {
    double x, y;

    public void setX(double x) { this.x = x; }
    public void setY(double y) { this.y = y; }

    public double getX() { return x; }
    public double getY() { return y; }

    public void mover() { setX(0); setY(0); }
    public void mover(double x, double y) { setX(x); setY(y); }
    public void mover(Coordenada2D ponto) { setX(ponto.getX()); setY(ponto.getY()); }

    public boolean equals(Object obj) {return this == obj ? true : (obj instanceof Coordenada2D ? (this.x == ((Coordenada2D) obj).getX() && this.y == ((Coordenada2D) obj).getY()) : false);}
}

abstract class FiguraGeometrica {
    Coordenada2D centro;

    public FiguraGeometrica() { this.centro = new Coordenada2D(); }

    public void setCentro(Coordenada2D centro) { this.centro.mover(centro); }
    public Coordenada2D getCentro() { return centro; }

    // Método abstrato para demonstrar @Override
    public abstract double area();
}

interface FormaGeometrica {
    public boolean pertence(Coordenada2D ponto);
}

class circulo extends FiguraGeometrica{
    private double raio;

    public double getRaio() { return raio; }
    public void setRaio(double raio) { this.raio = raio; }

    @Override
    public double area() { return Math.PI * raio * raio; }

    public void inflar(double valor) { this.raio += valor; }
    public void desinflar(double valor) { this.raio -= valor; }

    public void inflar() { inflar(1); }
    
    public void desinflar() { desinflar(1); }
}

class quadrado extends FiguraGeometrica {
    private double lado;

    public double getLado() { return lado; }
    public void setLado(double lado) { this.lado = lado; }

    @Override
    public double area() { return lado * lado; }

    public void inflar(double valor) { this.lado += valor; }
    public void desinflar(double valor) { this.lado -= valor; }
    public void inflar() { inflar(1); }
    public void desinflar() { desinflar(1); }
}

class reta implements FormaGeometrica {
    @Override
    public boolean pertence(Coordenada2D ponto) { return false; }
}


public class Main {
    public static void main(String[] args) {
        
    }
}