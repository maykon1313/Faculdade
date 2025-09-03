import java.util.ArrayList;

class StartUp {
    private String nome;
    private int acertos = 0;
    private String[] posicoes;

    public StartUp(String n) {
        nome = n;
    }

    public void setPosi(String[] posi) {
        posicoes = posi;
    }

    public int setAcertos(String posi) {
        for (String p : posicoes) {
            if (p.equals(posi)) {
                acertos += 1;

                if (acertos == 3) return 2;
                else return 1;
            }
        }
        return -1;
    }

    public String getNome() {
        return nome;
    }

    public String[] getPosicoes() {
        return posicoes;
    }
}

class Jogo {
    private StartUp[] startups = {new StartUp("Bolinha"), new StartUp("CatNip"), new StartUp("Gato")};
    
    private String[] posicoes_startup1 = {"a1","a2","a3"};
    private String[] posicoes_startup2 = {"b1","b2","b3"};
    private String[] posicoes_startup3 = {"c1","c2","c3"};

    private String palpite;
    private int acerto, abates;
    private boolean houve;
    private ArrayList<String> palpitesAnteriores = new ArrayList<>();

    public Jogo() {
        startups[0].setPosi(posicoes_startup1);
        startups[1].setPosi(posicoes_startup2);
        startups[2].setPosi(posicoes_startup3);
    }

    public void jogar() {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        abates = 0;

        try {
            while (true) {
                System.out.print("Digite seu palpite: ");
                palpite = scanner.nextLine();

                if (palpitesAnteriores.contains(palpite)) {
                    System.out.println("Você já tentou essa posição. Tente outra.");
                    continue;
                }
                
                palpitesAnteriores.add(palpite);

                acerto = 0;
                houve = false;
                
                for (StartUp s : startups) {
                    acerto = s.setAcertos(palpite);

                    if (acerto == 1) {
                        System.out.println("Acertou");
                        houve = true;
                    }
                    else if (acerto == 2) {
                        System.out.println("Abateu");
                        abates += 1;
                        houve = true;
                    }
                }

                if (!houve) System.out.println("Errou");

                if (abates == 3) {
                    System.out.println("Venceu");   
                    return;
                }
            }
        } finally {
            scanner.close();
        }
    }
}

public class Naval {
    public static void main(String[] args) {
	    Jogo game = new Jogo();

        game.jogar();
    }
}
