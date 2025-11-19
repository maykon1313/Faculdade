package Lambdas_Streams_e_Interfaces_Funcionais;

public class Main3 {
    public static void main(String[] args) {
        Somador s = (a, b) -> a + b;
        Mensagem m = nome -> "Olá, " + nome + "! Bem-vindo.";
        
        int resultado = s.somar(10, 5);
        System.out.println(resultado); // 15
        
        String msg = m.formatar("Ana");
        System.out.println(msg); // Olá, Ana! Bem-vindo.
    }
}

@FunctionalInterface
interface Somador {
    int somar(int a, int b);
}

@FunctionalInterface
interface Mensagem {
    String formatar(String nome);
}