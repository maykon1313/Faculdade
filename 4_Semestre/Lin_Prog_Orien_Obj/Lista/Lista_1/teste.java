class Object {
    public String equals(Object obj) {
        if (this == obj) return "inguais!";
        else return "naum inguais!";
    }

    public String toString() {
        return this.getClass().getName() + "@" + Integer.toHexString(this.hashCode()) + "+" + "Isso é novo.";
    }
}

abstract class Animal extends Object {
    private String nome;

    public String som() {return "som.";}
    public void setNome(String n) {nome = n;}
    public String getNome() {return nome;}
}

class Gato extends Animal {
    public String som() {return "miau miau";}
}

class Cachorro extends Animal {
    public String som() {return "au au";}
}

public class teste {
    public static void main(String[] args) {
        Gato g = new Gato();
        Cachorro c = new Cachorro();

        g.setNome("Mimia");
        c.setNome("Caos");
        
        System.out.println("Os animais: " + g.getNome() + " e " + c.getNome() + " são " + g.equals(c));
        
        System.out.println(g.som());
        System.out.println(c.som());

        System.out.println(g.getClass());
        System.out.println(c.getClass());

        System.out.println(g.toString());
        System.out.println(c.toString());

        Animal Breno;

        Breno = c;

        System.out.println(Breno.som());        
    }
}
