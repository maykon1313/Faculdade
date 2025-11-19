package Metodos_Estaticos;

public class ContadorObjetos {
    private static int totalCriados = 0;
    private int id;

    public ContadorObjetos() {
        totalCriados++;
        this.id = totalCriados;
    }

    public int getId() {
        return id;
    }

    public static int getTotalCriados() {
        return totalCriados;
    }

    public static void resetarContador() {
        totalCriados = 0;
    }
}
