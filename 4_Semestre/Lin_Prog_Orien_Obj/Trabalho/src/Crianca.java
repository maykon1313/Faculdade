package src;

public final class Crianca {
    private String nome;
    private int energiaSusto;
    private int energiaRiso;
    private Porta porta; // Atributos

    public Crianca(String nome) {
        this.nome = nome;
        this.energiaSusto = (int)(Math.random() * 101);
        this.energiaRiso = (int)(Math.random() * 101);
    } // Contrutor

    public void setNome(String nome) { this.nome = nome; }
    public void setPorta(Porta porta){ this.porta = porta; }
    public void setEnergiaSusto(int energia) { this.energiaSusto = energia; }
    public void setEnergiaRiso(int energia) { this.energiaRiso = energia; }

    public String getNome() { return this.nome; }
    public Porta getPorta(){ return this.porta; } // Métodos get e set

    public int getEnergia(String tipo) {
        if (tipo.equals("susto")) return this.energiaSusto;
        else if (tipo.equals("riso")) return this.energiaRiso;
        else throw new IllegalArgumentException("Tipo de energia inválido: " + tipo + ". Deve ser 'susto' ou 'riso'.");
    } // Método para pegar a eficiência de acordo com o tipo do monstro

    @Override
    public String toString() { 
        return "Criança: " + this.nome + " | Energia de Susto: " + this.energiaSusto + " | Energia de Riso: " + this.energiaRiso + " | Porta associada: " + (this.porta != null ? this.porta.getId() : "Nenhuma" + "."); 
    } // Sobrescrita do Método da class Object
}
