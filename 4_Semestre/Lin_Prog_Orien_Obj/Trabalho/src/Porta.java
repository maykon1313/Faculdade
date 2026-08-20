package src;

public final class Porta {
    private int id;
    private Crianca cotocos; // Atributos

    public Porta(int id) {
        this.id = id;
    } // Contrutor

    public Porta(int id, Crianca cotocos) {
        this.id = id;
        this.cotocos = cotocos;
    } // Contrutor sobrecarregado

    public void setCrianca(Crianca cotocos) { this.cotocos = cotocos; }
    public void setId(int id) { this.id = id; }
    public Crianca getCrianca() { return this.cotocos; }
    public int getId() { return this.id; } // Métodos get e set

    public void changeCrianca(Crianca c) {
    if (cotocos != null) { cotocos.setPorta(null); }
    this.cotocos = c;
    if (c != null) { c.setPorta(this); }
    } // Método para mudar a criança da porta

    @Override
    public String toString() { 
        return "Porta ID: " + id + " | Criança: " + (cotocos != null ? cotocos.getNome() : "Nenhuma"); 
    } // Sobrescrita do Método da class Object
}
