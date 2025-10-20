class StartupGame{

    int [] localizacaoCelulas;
    int numAcertos;

    String verificaPalpite(int palpite){
    String resultado = "erro";    
    
    for (int celula : localizacaoCelulas){
        if(palpite == celula){
            resultado = "acerto";
            numAcertos++;
            break;
        }//Fim do if
    }//Fim do loop for
    if (numAcertos == localizacaoCelulas.length){
        resultado = "abate";
    }//Fim do if
    System.out.println(resultado);
        return resultado;
    }
    void setLocalizacaoCelulas(int[] loc){
        localizacaoCelulas = loc;
    }
}

  