package Lambdas_Streams_e_Interfaces_Funcionais;

@FunctionalInterface
public interface Transformador {
    String transformar(String s);
    
    default void imprimirTransformada(String transformada) {
        System.out.println("String transformada: " + transformada);
    }
    
    static boolean isVazia(String s) {
        return s == null || s.isEmpty();
    }
}