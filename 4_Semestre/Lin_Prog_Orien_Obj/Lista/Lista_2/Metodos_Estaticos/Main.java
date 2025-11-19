package Metodos_Estaticos;

public class Main {
    public static void main(String[] args) {
        // e. Crie três instâncias de ContadorObjetos e imprima seus IDs. Imprima o valor de ContadorObjetos.getTotalCriados().
        ContadorObjetos obj1 = new ContadorObjetos();
        ContadorObjetos obj2 = new ContadorObjetos();
        ContadorObjetos obj3 = new ContadorObjetos();

        System.out.println("ID do obj1: " + obj1.getId());
        System.out.println("ID do obj2: " + obj2.getId());
        System.out.println("ID do obj3: " + obj3.getId());
        System.out.println("Total criado: " + ContadorObjetos.getTotalCriados());

        // f. Chame ContadorObjetos.resetarContador().
        ContadorObjetos.resetarContador();

        // g. Crie mais dois objetos e exiba seus IDs e o total atualizado.
        ContadorObjetos obj4 = new ContadorObjetos();
        ContadorObjetos obj5 = new ContadorObjetos();

        System.out.println("ID do obj4: " + obj4.getId());
        System.out.println("ID do obj5: " + obj5.getId());
        System.out.println("Total criado após reset: " + ContadorObjetos.getTotalCriados());

        // h. Use os métodos da classe Util para: verificar se um número é par; Encontrar o maior entre dois inteiros.
        int num = 4;
        System.out.println(num + " é par? " + Util.ehPar(num));

        int a = 10, b = 20;
        System.out.println("Maior entre " + a + " e " + b + ": " + Util.maior(a, b));
    }
}
