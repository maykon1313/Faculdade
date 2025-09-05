package Aula_1;

class Dog {
    int peso;
    String raca;
    String nome;

    public void latir() {
        System.out.println(nome + " está latindo.");
    }
}

class Movie {
    String titulo;
    String genero;
    float classificacao;
    
    public void play() {
        System.out.println("O filme de nome " + titulo + " do gênero " + genero + " que possui a classificação de " + classificacao + " estrelas está sendo exibido.");
    }
}

class GuessGame {
    Player p1;
    Player p2;
    Player p3;

    public void startGame() {
        p1 = new Player();
        p2 = new Player();
        p3 = new Player();

        int targetNumber = (int)(Math.random() * 10);

        while (true) {
            System.out.println("O número é " + targetNumber + ".");
            
            p1.guess();
            p2.guess();
            p3.guess();

            if (p1.number == targetNumber) {
                System.out.println("Player 1 acertou o número, era: " + p1.number + ".");
                break;
            } else {
                System.out.println("Player 1 errou e chuto o número: " + p1.number + ".");
            }
            
            if (p2.number == targetNumber) {
                System.out.println("Player 2 acertou o número, era: " + p2.number + ".");
                break;
            } else {
                System.out.println("Player 2 errou e chuto o número: " + p2.number + ".");
            }
            
            if (p3.number == targetNumber) {
                System.out.println("Player 3 acertou o número, era: " + p3.number + ".");
                break;
            } else {
                System.out.println("Player 3 errou e chuto o número: " + p3.number + ".");
            }

            System.out.println();
        }
    }
}

class Player {
    int number;

    public void guess() {
        number = (int)(Math.random() * 10);
    }
}

public class Aula_1 {
    public static void main(String[] args) {
        /* 
        Dog cachorro = new Dog();

        cachorro.nome = "Jorgete";
        cachorro.peso = 50;
        cachorro.raca = "Humana";

        cachorro.latir();
        */
    
        /*
        Movie filme = new Movie();

        filme.titulo = "Wall-E";
        filme.genero = "Animação";
        filme.classificacao = 8.4f;
    
        filme.play();
        */

        GuessGame jogo = new GuessGame();
        jogo.startGame();
    }    
}