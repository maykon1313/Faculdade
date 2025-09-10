package Exer1;

class ContadorDeVisitas {
    private int total = 0;

    public void reiniciar() {
        total = 0;
    }

    public void registrarVisita1(){
        total = total + 1;
    } 
    
    public int getTotal(){
        return total;
    }

    public void registrarVisita(int coisa){
        total = total + coisa;
    }
}

class ContadorDeVisitasPremium extends ContadorDeVisitas {    
    public void registrarVisitaVip(){
        registrarVisita(10);
    }
}

public class exer1 {
    public static void main(String[] args) {
        ContadorDeVisitas bolota = new ContadorDeVisitas();
        ContadorDeVisitasPremium batota = new ContadorDeVisitasPremium();

        bolota.registrarVisita(69); 
        System.out.println(bolota.getTotal());

        batota.registrarVisitaVip();
        System.out.println(batota.getTotal());
    }
}

