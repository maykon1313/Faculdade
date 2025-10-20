package Aula_6_Revisao_P1;

public class Coordenada2D {
    private double x, y;

    public double getX() {return x;}
    public double getY() {return y;}

    public void setX(double x) {this.x = x;}
    public void setY(double y) {this.y = y;}

    public void mover() {setX(0); setY(0);}
    public void mover(double x, double y) {setX(x); setY(y);}
    public void mover(Coordenada2D ponto) {setX(ponto.getX()); setY(ponto.getY());}

    public boolean equals(Object obj) {return this == obj ? true : (obj instanceof Coordenada2D ? (this.x == ((Coordenada2D) obj).getX() && this.y == ((Coordenada2D) obj).getY()) : false);}

    public String toString() {return "Coordenada: [x = " + getX() + ", y = " + getY() + "].";}

    public double distancia(Coordenada2D ponto) {return Math.sqrt((ponto.x - this.x)*(ponto.x - this.x) + (ponto.y - this.y)*(ponto.y - this.y));}
}
