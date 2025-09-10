package Exer2;

import java.lang.Math;

public class Coordenada2D {
    private double X, Y;
    
    public double getX(){
        return X;
    }
    
    public double getY(){
        return Y;
    } 

    public void setX(double valor){
        X = valor;
    }
    
    public void setY(double valor){
        Y = valor;
    } 

    public void mover1(){
        setX(0);
        setY(0);
    }
    
    public void mover2(double kazuhiroX, double kazuhiroY){
        setX(kazuhiroX);
        setY(kazuhiroY);
    }

    public void mover3(Coordenada2D maykon){
        setX(maykon.getX());
        setY(maykon.getY());
    }

    public boolean engual(Coordenada2D farca){
        if(X == farca.getX() && Y == farca.getY()) return true;
        else return false;
    }

    public void tuString(){
        System.out.println("A posiçao X é: " + getX());
        System.out.println("A posiçao Y é: " + getY());
    }
    
    public double iwanttubreakfree(Coordenada2D mamaaauuuu){
        return Math.sqrt(Math.pow((X - mamaaauuuu.getX()), 2)+Math.pow((Y - mamaaauuuu.getY()), 2));
    }    
}

