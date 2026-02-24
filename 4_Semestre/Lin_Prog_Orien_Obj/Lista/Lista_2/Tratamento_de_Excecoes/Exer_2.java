package Tratamento_de_Excecoes;

public class Exer_2 {
    public static String lerTemperatura(double valor) {
        if (valor < -50 || valor > 80) {
            throw new IllegalArgumentException("Temperatura fora do intervalo permitido (-50 a 80°C).");
        }
        return "Temperatura registrada: " + valor + "°C";
    }

    public static void main(String[] args) {
        try {
            System.out.println(lerTemperatura(22.5));
            System.out.println(lerTemperatura(150));
        } catch (IllegalArgumentException e) {
            System.out.println("Erro ao ler temperatura: " + e.getMessage());
        }
    }
}