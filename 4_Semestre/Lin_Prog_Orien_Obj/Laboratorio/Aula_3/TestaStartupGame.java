public class TestaStartupGame{

    public static void main(String[] args){
   
        int numTentativas = 0;
        Auxiliadora aux = new Auxiliadora();

        StartupGame game = new StartupGame();

        int numAleatorio = (int)(Math.random()*5);
        
        
        int [] locations = {numAleatorio, numAleatorio+1, numAleatorio+2};
        game.setLocalizacaoCelulas(locations);
    
        boolean estaViva = true;
        while(estaViva){

            int palpite = aux.leEntrada("Entre com um número: ");
            String result = game.verificaPalpite(palpite);
            numTentativas++;

            if(result.equals("abate")){
                estaViva = false;
                System.out.println("Tentativas: " + numTentativas);
            }
        }
    }//fim da main
}