package Aula_7_P1;

public class Quadrado extends FiguraGeometrica {
    private double lado;

    public double getLado() {return lado;}
    public void setLado(double lado) {this.lado = lado;}

    public double area() {return lado*lado;}

    public String toString() {return "Centro: " + getCentro() +", lado: " + getLado() + ", área: " + area();}
}
