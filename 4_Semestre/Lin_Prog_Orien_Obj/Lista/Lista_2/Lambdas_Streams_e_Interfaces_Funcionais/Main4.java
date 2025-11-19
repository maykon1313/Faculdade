package Lambdas_Streams_e_Interfaces_Funcionais;

public class Main4 {
    public static void main(String[] args) {
        CalculadoraArea calc = (largura, altura) -> {
            if (largura > 0 && altura > 0) {
                return largura * altura;
            } else {
                return 0.0;
            }
        };
        
        double area = calc.calcular(5.0, 10.0);
        System.out.println("Área: " + area); // Área: 50.0
    }
}

@FunctionalInterface
interface CalculadoraArea {
    double calcular(double largura, double altura);
}