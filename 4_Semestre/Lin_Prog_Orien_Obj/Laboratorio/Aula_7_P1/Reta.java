package Aula_7_P1;

interface FormaGeometrica {
    public abstract boolean pertence(Coordenada2D ponto);
}

public class Reta implements FormaGeometrica {
    private double a, b;

    public boolean pertence(Coordenada2D ponto) {return ponto.getY() == a*ponto.getX() + b;}

    public double getA() {return a;}
    public double getB() {return b;}

    public void setA(double a) {this.a = a;}
    public void setB(double b) {this.b = b;}

    public String toString() {return "A reta tem a seguinte equação: y(x) = " + a + "x + (" + b + ").";}

    public Coordenada2D interseccao(Reta reta) {
        if (this.a == reta.a) {return null;}
        Coordenada2D ponto = new Coordenada2D();
        ponto.setX((reta.b - this.b) / (this.a - reta.a));
        ponto.setY(this.a * ponto.getX() + this.b);
        return ponto;
    }
}