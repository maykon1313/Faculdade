import java.util.Scanner; 

public class Auxiliadora { 

    public int leEntrada(String prompt) { 
      System.out.print(prompt + ": "); 
      Scanner scanner = new Scanner(System.in); 
      return scanner.nextInt(); 
    } 
}
