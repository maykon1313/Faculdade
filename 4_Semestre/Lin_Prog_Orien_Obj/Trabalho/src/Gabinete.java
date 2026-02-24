package src;

public final class Gabinete {
    private int id;
    private Porta abracadabra;
    private Monstro monstroPrincipal;
    private MonstroDeSuporte monstroAuxiliar;
    private Cilindro cilindro; // Atributos

    public Gabinete(int id, Porta abracadabra, Monstro monstroPrincipal, MonstroDeSuporte monstroAuxiliar, Cilindro cilindro) {
        this.id = id;
        this.abracadabra = abracadabra;
        this.monstroPrincipal = monstroPrincipal;
        this.monstroAuxiliar = monstroAuxiliar;
        this.cilindro = cilindro;
    } // Contrutor

    public void setId(int id) { this.id = id; }
    public void setPorta(Porta abracadabra) { this.abracadabra = abracadabra; }
    public void setMonstroPrincipal(Monstro monstroPrincipal) { this.monstroPrincipal = monstroPrincipal; }
    public void setMonstroAuxiliar(MonstroDeSuporte monstroAuxiliar) { this.monstroAuxiliar = monstroAuxiliar; }
    public void setCilindro(Cilindro cilindro) { this.cilindro = cilindro; }

    public int getId() { return this.id; }
    public Porta getPorta() { return this.abracadabra; }
    public Monstro getMonstroPrincipal() { return this.monstroPrincipal; }
    public MonstroDeSuporte getMonstroAuxiliar() { return this.monstroAuxiliar; }
    public Cilindro getCilindro() { return this.cilindro; } // Métodos get e set

    @Override
    public String toString() { 
        return "Gabinete ID: " + id + ", Porta: " + abracadabra + ", Monstro Principal: " + monstroPrincipal + ", Monstro Auxiliar: " + monstroAuxiliar + ", Cilindro: " + cilindro; 
    } // Sobrescrita do Método da class Object

    public static void processarEnergia(Cilindro c, Porta p, Monstro m_principal, MonstroDeSuporte m_auxiliar) throws IllegalArgumentException, IllegalStateException {
        if (c == null) {
            throw new IllegalArgumentException("Cilindro inválido.");
        }
        if (p == null) {
            throw new IllegalArgumentException("Porta inválida.");
        }
        if (m_principal == null) {
            throw new IllegalArgumentException("Monstro principal inválido.");
        }
        if (m_auxiliar == null) {
            throw new IllegalArgumentException("Monstro auxiliar inválido.");
        }

        Crianca crianca = p.getCrianca();
        if (crianca == null) {
            throw new IllegalStateException("Não há criança na porta.");
        }

        int energia = m_principal.coletarEnergiaDaCrianca(crianca);

        int fator; // Fator de aleatoriedade
        if (Math.random() > 0.5) { fator = 1; }
        else { fator = -1; }

        int energia_real = energia + (int) (fator * (energia * Math.random()));

        int energia_processada = m_auxiliar.receberEnergia(energia_real, c);

        System.out.println("\nProcessamento concluído:");
        System.out.println("Criança: " + crianca.getNome());
        System.out.println("Monstro Principal (" + m_principal.getNome() + ")");
        System.out.println("Monstro Auxiliar (" + m_auxiliar.getNome() + ")");

        if (energia_processada == -1) {
            System.out.println("Nenhuma energia adicionada ao Cilindro, capacidade máxima atingida.");
        }
        else {
            System.out.println("Energia adicionada ao Cilindro (" + c.getId() + "): " + energia_processada);
        }
    } // Método para processar a energia
}
