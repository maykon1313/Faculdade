package src;

import java.util.*;

public final class Agencia {
    private static ArrayList<Monstro> monstrosPrincipal;
    private static ArrayList<Monstro> monstrosAuxiliares;
    private static ArrayList<Porta> portas;
    private static ArrayList<Gabinete> gabinetes;
    private static ArrayList<Crianca> criancas;
    private static ArrayList<Cilindro> cilindros;

    static {
        monstrosPrincipal = new ArrayList<Monstro>();
        monstrosAuxiliares = new ArrayList<Monstro>();
        portas = new ArrayList<Porta>();
        gabinetes = new ArrayList<Gabinete>();
        criancas = new ArrayList<Crianca>();
        cilindros = new ArrayList<Cilindro>();
    }

    public static void addMonstroPrincipal(Monstro m) { monstrosPrincipal.add(m); }
    public static void addMonstroAuxiliar(Monstro m) { monstrosAuxiliares.add(m); }
    public static void addPorta(Porta p) { portas.add(p); }
    public static void addGabinete(Gabinete g) { gabinetes.add(g); }
    public static void addCrianca(Crianca c) { criancas.add(c); }
    public static void addCilindro(Cilindro ce) { cilindros.add(ce); }

    private static int mostrarLista(List<?> lista) {
        if (lista == null || lista.isEmpty()) { System.out.println("A lista está vazia."); return -1; }
        int i = 0; for (Object item : lista) { System.out.println(i + " - " + item); i++; }
        return 0;
    }

    public static int mostrarMonstros() {
        try {
            System.out.println("\nMonstros Principais:");
            mostrarLista(monstrosPrincipal);
            System.out.println("\nMonstros Auxiliares:");
            mostrarLista(monstrosAuxiliares);
            return 0;
        }

        catch (Exception e) {
            System.out.println("Erro ao mostrar monstros: " + e.getMessage());
            return -1;
        }
    }

    public static int mostrarMonstrosPrincipal() { return mostrarLista(monstrosPrincipal); }
    public static int mostrarMonstrosAuxiliar() { return mostrarLista(monstrosAuxiliares); }

    public static int mostrarPortas() { return mostrarLista(portas); }
    public static int mostrarGabinetes() { return mostrarLista(gabinetes); }
    public static int mostrarCriancas() { return mostrarLista(criancas); }
    public static int mostrarCilindros() { return mostrarLista(cilindros); }
    
    public static int mostrarEntidadesCadastradas() {
        System.out.println("\n--- Entidades Cadastradas ---");
        mostrarMonstros();

        System.out.println("\nPortas Cadastradas");
        mostrarPortas();

        System.out.println("\nGabinetes Cadastrados");
        mostrarGabinetes();

        System.out.println("\nCrianças Cadastradas");
        mostrarCriancas();

        System.out.println("\nCilindros Cadastrados");
        mostrarCilindros();

        System.out.println("-----------------------------\n");
        return 0;
    }

    private static <T> T encontrarPorIndex(List<T> lista, int index) {
        if (lista == null || index < 0 || index >= lista.size()) return null;
        return lista.get(index);
    }

    public static Monstro getMonstroPrincipal(int index) { return encontrarPorIndex(monstrosPrincipal, index); }
    public static Monstro getMonstroAuxiliar(int index) { return encontrarPorIndex(monstrosAuxiliares, index); }
    public static Porta getPorta(int index) { return encontrarPorIndex(portas, index); }
    public static Gabinete getGabinete(int index) { return encontrarPorIndex(gabinetes, index); }
    public static Crianca getCrianca(int index) { return encontrarPorIndex(criancas, index); }
    public static Cilindro getCilindro(int index) { return encontrarPorIndex(cilindros, index); }

    public static ArrayList<Monstro> getMonstrosPrincipal() { return monstrosPrincipal; }
    public static ArrayList<Monstro> getMonstrosAuxiliares() { return monstrosAuxiliares; }
    public static ArrayList<Porta> getPortas() { return portas; }
    public static ArrayList<Gabinete> getGabinetes() { return gabinetes; }
    public static ArrayList<Crianca> getCriancas() { return criancas; }
    public static ArrayList<Cilindro> getCilindros() { return cilindros; }

    public static void setMonstro(String nome, String tipo) {
        Monstro monstro = null;
        
        if (tipo.equalsIgnoreCase("susto")) {
            monstro = new MonstroDoSusto(nome);
            monstrosPrincipal.add(monstro);
        } 
        else if (tipo.equalsIgnoreCase("riso")) {
            monstro = new MonstroDoRiso(nome);
            monstrosPrincipal.add(monstro);
        } 
        else if (tipo.equalsIgnoreCase("suporte")) {
            monstro = new MonstroDeSuporte(nome);
            monstrosAuxiliares.add(monstro);
        } 
        else {
            System.out.println("Tipo de monstro inválido: " + tipo);
            return;
        }
        
        System.out.println("Monstro " + nome + " (" + tipo + ") adicionado com sucesso.");
    }

    public static void setPorta(int id, Crianca crianca, boolean change) {
        if (!change) {
            Porta porta = new Porta(id, crianca);
            portas.add(porta);
        } // Criança sem porta associada

        else {
            Porta porta = new Porta(id);
            porta.changeCrianca(crianca);
            portas.add(porta);
        } // Criança com porta associada
    } // Específica para porta

    public static void setPorta(Porta porta, Crianca crianca) {
        porta.changeCrianca(crianca);
    } // Específica para criança

    public static void setGabinete(int id, Porta porta, Monstro m_principal, MonstroDeSuporte m_auxiliar, Cilindro cilindro) {
        Gabinete g = new Gabinete(id, porta, m_principal, m_auxiliar, cilindro);
        gabinetes.add(g);
    }
    
    public static void setCrianca(String nome) {
        Crianca crianca = new Crianca(nome);
        criancas.add(crianca);
    }

    public static void setCilindro(int id) {
        Cilindro cilindro = new Cilindro(id);
        cilindros.add(cilindro);
    }

    public static void processarGabinete(int indexGabinete) {
        Gabinete g = getGabinete(indexGabinete);
        if (g == null) {
            throw new IllegalArgumentException("Gabinete inválido.");
        }
        Cilindro c = g.getCilindro();
        Porta p = g.getPorta();
        Monstro m_principal = g.getMonstroPrincipal();
        MonstroDeSuporte m_auxiliar = g.getMonstroAuxiliar();

        Gabinete.processarEnergia(c, p, m_principal, m_auxiliar);
    } // Função inicial/principal para gerar energia
}
