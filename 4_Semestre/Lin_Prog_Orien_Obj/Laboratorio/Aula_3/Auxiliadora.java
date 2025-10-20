import java.util.Scanner; 

public class Auxiliadora { 

    private static final Scanner scanner = new Scanner(System.in);

    public int leEntrada(String prompt) { 
      System.out.print(prompt + ": "); 
      return scanner.nextInt(); 
    } 
}
