class Fracao {
    private int numerador;
    private int denominador;

    public Fracao(int numerador, int denominador) { this.numerador = numerador; this.denominador = denominador; }
    public Fracao() { this(0, 1); }
    public Fracao(int numerador) { this(numerador, 1); }

    public void setNumerador(int numerador) { this.numerador = numerador; }
    public void setDenominador(int denominador) { this.denominador = denominador; }
    public int getNumerador() { return numerador; }
    public int getDenominador() { return denominador; }

    @Override
    public String toString() { return "Fração: " + getNumerador() + "/" + getDenominador(); }
}


public class Constructor {
    public static void main(String[] args) {
        System.out.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAh.");

        Fracao f1 = new Fracao(50, 30);
        Fracao f2 = new Fracao();
        Fracao f3 = new Fracao(13);

        System.out.println(f1);
        System.out.println(f2);
        System.out.println(f3);
    }
}