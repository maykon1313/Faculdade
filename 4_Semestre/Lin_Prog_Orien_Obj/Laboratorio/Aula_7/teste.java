package Aula_7;

class Dog {
    Dog() {System.out.println("Bark!");}
}

public class teste {
    public static void main(String[] args) {
        String classe = "Dog";

        //classe d = new classe();

        try {
            Class<?> clazz = Class.forName("Aula_7." + classe);
            Object d = clazz.getDeclaredConstructor().newInstance();

            System.out.println(d.toString());
        } 
        
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
