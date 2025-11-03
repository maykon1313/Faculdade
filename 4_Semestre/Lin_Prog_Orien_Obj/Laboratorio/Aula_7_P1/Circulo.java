package Aula_7_P1;

public class Circulo  extends FiguraGeometrica {
    double raio;

    public double getRaio() {return raio;}
    public void setRaio(double raio) {this.raio = raio;}

    public double area() {return 2*3.1415*raio;}

    public String toString() {return "Centro: " + getCentro() +", raio: " + getRaio() + ", área: " + area();}
}