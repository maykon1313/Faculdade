package Exer_5_a_9;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        List<Profissional> lista = new ArrayList<>();

        PrestadorServico ps1 = new PrestadorServico(10.0);
        PrestadorServico ps2 = new PrestadorServico("João", "CPF123", 40, 15.0);

        FuncionarioCLT clt1 = new FuncionarioCLT(100.0);
        FuncionarioCLT clt2 = new FuncionarioCLT("Ana", "RG456", 2000.0, 500.0);

        Gerente g1 = new Gerente(300.0);
        Gerente g2 = new Gerente("Pedro", "CNH789", 3000.0, 800.0);

        lista.add(ps1);
        lista.add(ps2);
        lista.add(clt1);
        lista.add(clt2);
        lista.add(g1);
        lista.add(g2);

        for (Profissional p : lista) {
            System.out.println(p);
            System.out.println(p.calcularSalarioFinal());
        }
    }
}
