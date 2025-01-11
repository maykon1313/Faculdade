import java.util.ArrayList;

public class estruturas_basicas { 
    public static void main(String[] args) {
    
        // int[] vetor = {1, 2, 3, 4, 5};

        // System.out.println("Valor na primeira posição: " + vetor[0]);
        // System.out.println("Valor na segunda posição: " + vetor[1]); 
        // System.out.println("Valor na terceira posição: " + vetor[2]);
        // System.out.println("Valor na quarta posição: " + vetor[3]);
        // System.out.println("Valor na quinta posição: " + vetor[4]);

        // System.out.println("Tamanho do vetor: " + vetor.length);
        

        // int[] numeros = new int[4];
        
        // System.out.println("Valor na primeira posição: " + numeros[0]);
        // System.out.println("Valor na segunda posição: " + numeros[1]); 
        // System.out.println("Valor na terceira posição: " + numeros[2]);
        // System.out.println("Valor na quarta posição: " + numeros[3]);

        // System.out.println("Tamanho do vetor: " + numeros.length);
        
        
        /* 
        ArrayList<String> nome = new ArrayList<>();

        nome.add("Maykon");
        nome.add("Kazuhiro");
        nome.add("Falcão");

        // System.out.println("Nome na primeira posição: " + nome.get(0));

        // nome.remove(0);

        // System.out.println("Nome na primeira posição: " + nome.get(0));

        System.out.println("Meu nome:");

        int i = 0;
        for (i = 0; i < nome.size(); i++) {
            System.out.println(nome.get(i));
        }
        
        i = 0;  
        while (i < nome.size()) {
            System.out.println(nome.get(i));
            i++;
        }

        for (String n : nome) {
            System.out.println(n);
        }
        */
        
        

        String meunumeroStr = "10";
        int meunumeroInt = Integer.parseInt(meunumeroStr);
        String voltaStr = String.valueOf(meunumeroInt);

        System.out.println(meunumeroStr.getClass());
        System.out.println(((Object) meunumeroInt).getClass());
        System.out.println(voltaStr.getClass());

    }
}
