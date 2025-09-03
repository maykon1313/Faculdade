package Aula_Laboratório.Aula_2;

class Jogador{
    private String nome;
    private int numero;
    private int qtdAcertos = 0;

    public Jogador(String nome) {
        this.nome = nome;
    }

    public void adivinha(){
        numero = (int)(Math.random() * 10);
    }

    public void addAcerto() {
        qtdAcertos += 1;
    }

    public String getNome() {
        return nome;
    }

    public int getNumero() {
        return numero;
    }

    public int getAcertos() {
        return qtdAcertos;
    }
}

class JogoAdivinhacao{
    Jogador[] jogadores;

    public void setJogadores(String[] nomes) {
        int i = nomes.length;
        jogadores = new Jogador[i];

        for (int j = 0; j < i; j++) {
            jogadores[j] = new Jogador(nomes[j]);
        }
    } 

    public void showAcertos() {
        int i = jogadores.length;

        System.out.println("\nMostrando quantidade de acertos até o momento:");
        for (int j = 0; j < i; j++) {
            System.out.println("O jogador(a) " + jogadores[j].getNome() + " acertou " + jogadores[j].getAcertos() + " vezes.");
        }
    }

    public void jogar(){
        int i = jogadores.length;
        boolean acertos;

        int numeroAleatorio = (int)(Math.random() * 10);
        System.out.println("Estou pensando em um número entre 0 e 9...");

        while(true){
            acertos = false;

            System.out.println("\nO número a ser adivinhado é o " + numeroAleatorio + '\n');

            for (int j = 0; j < i; j++) {
                jogadores[j].adivinha();
                System.out.println("Jogador " + (j+1) + " (" + jogadores[j].getNome() +")" + " escolheu " + jogadores[j].getNumero());

                if (jogadores[j].getNumero() == numeroAleatorio) {
                    jogadores[j].addAcerto();

                    acertos = true;
                }
            }

            if (acertos) {
                System.out.println("\nO(s) jogador(es) que acertou(ram) foi(ram):");
                
                for (int j = 0; j < i; j++) {
                    if (jogadores[j].getNumero() == numeroAleatorio) {
                        System.out.println("O jogador(a) " + jogadores[j].getNome() + " acertou.");    
                    }
                }

                showAcertos();
                break;
            }
            
            else {
                System.out.println("\nOs jogadores tentarão novamente!"); 
            }
        }
    }

    public Jogador[] getVencedor() {
        int maior_qtd_acertos = 0;
        int i = jogadores.length;
        Jogador[] vencedores = new Jogador[i];

        for (int j = 0; j < i; j++) {
            if (jogadores[j].getAcertos() >= maior_qtd_acertos) {
                maior_qtd_acertos = jogadores[j].getAcertos();
            }
        }

        for (int j = 0; j < i; j++) {
            if (jogadores[j].getAcertos() == maior_qtd_acertos) {
                vencedores[j] = jogadores[j];
            }
        }

        return vencedores;
    }
}

public class TestaJogo {
    public static void main(String[] args){
        JogoAdivinhacao jogo = new JogoAdivinhacao();
        Jogador[] vencedores;

        String[] nomes = {"Maria", "João", "José"};

        jogo.setJogadores(nomes);

        for (int i = 0; i < 10; i++) {
            jogo.jogar();
        }

        vencedores = jogo.getVencedor();

        System.out.println("\nO(s) jogador(es) que venceu(ram) foi(ram): ");
        for (Jogador vencedor : vencedores) {
            if (vencedor != null) {
                System.out.println(vencedor.getNome() + " com " + vencedor.getAcertos() + " acertos.");
            }
        }
    }
}
