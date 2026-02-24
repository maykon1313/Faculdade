package src;

public final class Cilindro {
    private int id;
    private int armazenado; // Atributos

    public Cilindro(int id) {
        this.id = id;
        this.armazenado = 0;
    } // Contrutor

    public void setId(int id) { this.id = id; }
    public void setArmazenado(int armazenado) { this.armazenado = armazenado; }
    
    public int getId() { return this.id; }
    public int getArmazenado() { return this.armazenado; } // Métodos get e set

    public int armazenarEnergia(int energia) { 
        if (this.armazenado + energia >= 100) {
            this.armazenado = 100;
            return 1;
        } 
        
        else {
            this.armazenado += energia; 
            return 0;
        }
    } // Método para armazenar energia no cilindro

    @Override
    public String toString() { 
        return "Cilindro ID: " + id + " | Energia Armazenada: " + armazenado;
    } // Sobrescrita do Método da class Object
}
