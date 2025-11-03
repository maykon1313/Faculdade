package Aula_7_P1;

public abstract class FiguraGeometrica {
    Coordenada2D centro = new Coordenada2D();

    public Coordenada2D getCentro() {return centro;}
    public void setCentro(Coordenada2D ponto) {centro.mover(ponto);}
    
    public void mover() {centro.mover(0, 0);}
    public void mover(double x, double y) {centro.mover(x, y);}
    public void mover(Coordenada2D ponto) {this.centro.mover(ponto);}

    abstract double area();
}
