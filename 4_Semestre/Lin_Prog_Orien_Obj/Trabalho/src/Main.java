package src;

import java.io.*;
import java.util.*;
import java.util.function.Function;

public final class Main {
    public static void main(String[] args) {
        try {
            carregarDados();
            menuInterativo();
            salvarDados();
        } catch (Exception e) {
            System.err.println("Erro fatal no programa: " + e.getMessage());
            e.printStackTrace();
        }
    } // Método principal da Main

    public static int mostrarOpcoes(Scanner scanner) {
        System.out.println("\n=== MENU MONSTROS S.A. ===");

        System.out.println("1 - Cadastrar nova entidade.");
        System.out.println("2 - Manipular informações das entidades cadastradas.");
        System.out.println("3 - Mostrar entidades cadastradas.");
        System.out.println("4 - Processar gabinete.");
        System.out.println("5 - Sair.");

        System.out.print("Escolha uma opção: ");

        int opcao = scanner.nextInt();
        scanner.nextLine();

        if (opcao < 1 || opcao > 5) { return -1; }
        else { return opcao; }
    } // Menu para selecionar a ação inicial

    public static int validarOpcao(Scanner scanner, int min, int max) {
        try {
            int opcao = validarInt(scanner);

            if (opcao < min || opcao > max) {
                System.out.println("Entrada inválida. Opção deve estar entre " + min + " e " + max + ".");
                return -1;
            }
            else { return opcao; }
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
            return -1;
        } catch (Exception e) {
            System.out.println("Erro inesperado: " + e.getMessage());
            return -1;
        }
    } // Método para validar um int no intervalo definido

    public static int validarInt(Scanner scanner) {
        try {
            int entrada = scanner.nextInt();
            scanner.nextLine();

            if (entrada < 0) {
                throw new IllegalArgumentException("Valor deve ser não negativo.");
            }

            return entrada;
        } catch (InputMismatchException e) {
            scanner.nextLine(); // clear invalid input
            throw new IllegalArgumentException("Entrada inválida. Esperado um número inteiro.");
        } catch (IllegalArgumentException e) {
            throw e;
        } catch (Exception e) {
            throw new RuntimeException("Erro inesperado ao validar entrada: " + e.getMessage(), e);
        }
    } // Método para validar um int não negativo

    public static String validarString(Scanner scanner) {
        try {
            String entrada = scanner.nextLine();

            if (entrada == null || entrada.trim().isEmpty()) {
                throw new IllegalArgumentException("Entrada inválida: string vazia ou nula.");
            }

            return entrada.trim();
        } catch (Exception e) {
            throw new IllegalArgumentException("Erro ao ler entrada de string: " + e.getMessage(), e);
        }
    } // Método para validar uma String

    private static int perguntarSimNao(Scanner scanner, String pergunta) {
        System.out.println(pergunta + " (s/n)");
        try {
            String resposta = validarString(scanner);
            if (resposta.equalsIgnoreCase("s")) return 1;
            if (resposta.equalsIgnoreCase("n")) return 0;
            System.out.println("Resposta inválida.");
            return -1;
        } catch (IllegalArgumentException e) {
            System.out.println("Erro na resposta: " + e.getMessage());
            return -1;
        } catch (Exception e) {
            System.out.println("Erro inesperado: " + e.getMessage());
            return -1;
        }
    } // Método para validar um pargunta de sim ou não 

    public static int cadastrarNovaEntidade(Scanner scanner) {
        System.out.println("\n=== MENU CADASTRAR NOVA ENTIDADE ===");

        System.out.println("1 - Cadastrar Cilindro.");
        System.out.println("2 - Cadastrar Criança.");
        System.out.println("3 - Cadastrar Gabinete.");
        System.out.println("4 - Cadastrar Monstro.");
        System.out.println("5 - Cadastrar Porta.");
        System.out.println("6 - Retornar.");

        System.out.print("Escolha uma opção: ");

        return validarOpcao(scanner, 1, 6);
    } // Menu para cadastrar nova entidade

    public static int cadastrarCilindro(Scanner scanner) {
        System.out.println("\n=== CADASTRAR CILINDRO ===");
        
        System.out.println("Digite o ID do cilindro: ");
        try {
            int id = validarInt(scanner);

            boolean idExists = false;
            for (Cilindro c : Agencia.getCilindros()) {
                if (c.getId() == id) {
                    idExists = true;
                    break;
                }
            }
            if (idExists) {
                System.out.println("Erro: ID já existe para outro cilindro.");
                return -1;
            }

            Agencia.setCilindro(id);
            System.out.println("Cilindro cadastrado com sucesso!");
            return 0;
        } catch (IllegalArgumentException e) {
            System.out.println("Erro ao cadastrar cilindro: " + e.getMessage());
            return -1;
        } catch (Exception e) {
            System.out.println("Erro inesperado ao cadastrar cilindro: " + e.getMessage());
            return -1;
        }
    }

    public static int cadastrarCrianca(Scanner scanner) {
        System.out.println("\n=== CADASTRAR CRIANÇA ===");

        System.out.print("Digite o nome da criança: ");
        try {
            String nome = validarString(scanner);
            Agencia.setCrianca(nome);
            System.out.println("Criança cadastrada com sucesso!");
            
            int resp = perguntarSimNao(scanner, "Deseja associar uma porta a esta criança?");
            if (resp == -1) { return -1; }
            if (resp == 1) {
                Agencia.mostrarPortas();
                System.out.print("Digite o ID da porta: ");
                int id = validarInt(scanner);
                
                Porta porta = Agencia.getPorta(id);

                if (porta == null) { 
                    System.out.println("Erro: Porta não encontrada.");
                    return -1;
                }

                Crianca crianca = Agencia.getCrianca(Agencia.getCriancas().size() - 1);
                
                Agencia.setPorta(porta, crianca);
                System.out.println("Porta cadastrada com sucesso!");
                return 0;
            }
            else {
                System.out.println("Cadastrar porta cancelada.");
            }
            
            return 0;
        } catch (IllegalArgumentException e) {
            System.out.println("Erro ao cadastrar criança: " + e.getMessage());
            return -1;
        } catch (Exception e) {
            System.out.println("Erro inesperado ao cadastrar criança: " + e.getMessage());
            return -1;
        }
    }

    public static int cadastrarGabinete(Scanner scanner) {
        System.out.println("\n=== CADASTRAR GABINETE ===");
        
        System.out.print("Digite o ID do gabinete: ");
        int id = validarInt(scanner);
        if (id == -1) { return -1; }

        boolean idExists = false;
        for (Gabinete g : Agencia.getGabinetes()) {
            if (g.getId() == id) {
                idExists = true;
                break;
            }
        }
        if (idExists) {
            System.out.println("Erro: ID já existe para outro gabinete.");
            return -1;
        }

        System.out.println("Selecione a porta:");
        Agencia.mostrarPortas();

        System.out.print("Digite o índice da porta: ");
        int indexPorta = validarInt(scanner);
        if (indexPorta == -1) { return -1; }

        Porta porta = Agencia.getPorta(indexPorta);
        if (porta == null) {
            System.out.println("Porta não encontrada.");
            return -1;
        }

        System.out.println("Selecione o monstro principal:");
        Agencia.mostrarMonstrosPrincipal();

        System.out.print("Digite o índice do monstro principal: ");
        int indexMonstroPrincipal = validarInt(scanner);
        if (indexMonstroPrincipal == -1) { return -1; }

        Monstro monstroPrincipal = Agencia.getMonstroPrincipal(indexMonstroPrincipal);
        if (monstroPrincipal == null) {
            System.out.println("Monstro principal não encontrado.");
            return -1;
        }

        System.out.println("Selecione o monstro auxiliar:");
        Agencia.mostrarMonstrosAuxiliar();

        System.out.print("Digite o índice do monstro auxiliar: ");
        int indexMonstroAuxiliar = validarInt(scanner);
        if (indexMonstroAuxiliar == -1) { return -1; }

        MonstroDeSuporte monstroAuxiliar = (MonstroDeSuporte) Agencia.getMonstroAuxiliar(indexMonstroAuxiliar);

        System.out.println("Selecione o cilindro:");
        Agencia.mostrarCilindros();

        System.out.print("Digite o índice do cilindro: ");
        int indexCilindro = validarInt(scanner);
        if (indexCilindro == -1) { return -1; }

        Cilindro cilindro = (Cilindro) Agencia.getCilindro(indexCilindro);

        if (cilindro == null) {
            System.out.println("Cilindro não encontrado.");
            return -1;
        }

        try {
            Agencia.setGabinete(id, porta, monstroPrincipal, monstroAuxiliar, cilindro);
            System.out.println("Gabinete cadastrado com sucesso!");
            return 0;
        }

        catch (Exception e) {
            System.out.println("Erro ao cadastrar gabinete: " + e.getMessage());
            return -1;
        }
    }

    public static int cadastrarMonstro(Scanner scanner) {
        System.out.println("\n=== CADASTRAR MONSTRO ===");

        System.out.println("Digite o nome do monstro: ");
        String nome = validarString(scanner);
        if (nome == null) { return -1; }

        System.out.print("Digite o tipo do monstro (1 - Susto, 2 - Riso, 3 - Suporte): ");
        int tipo = validarInt(scanner);
        if (tipo == -1) { return -1; }

        if (tipo < 1 || tipo > 3) {
            System.out.println("Tipo de monstro inválido.");
            return -1;
        }
        
        String tipoMonstro = tipo == 1 ? "susto" : tipo == 2 ? "riso" : "suporte";

        try {
            Agencia.setMonstro(nome, tipoMonstro);
            System.out.println("Monstro cadastrado com sucesso!");
            return 0;
        }

        catch (Exception e) {
            System.out.println("Erro ao cadastrar monstro: " + e.getMessage());
            return -1;
        }
    }

    public static int cadastrarPorta(Scanner scanner) {
        System.out.println("\n=== CADASTRAR PORTA ===");

        System.out.print("Digite o ID da porta: ");
        int id = validarInt(scanner);
        if (id == -1) { return -1; }

        boolean idExists = false;
        for (Porta p : Agencia.getPortas()) {
            if (p.getId() == id) {
                idExists = true;
                break;
            }
        }
        if (idExists) {
            System.out.println("Erro: ID já existe para outra porta.");
            return -1;
        }

        System.out.println("Selecione a criança para associar à porta:");
        Agencia.mostrarCriancas();

        System.out.print("Digite o índice da criança: ");
        int indexCrianca = validarInt(scanner);
        if (indexCrianca == -1) { return -1; }

        Crianca crianca = Agencia.getCrianca(indexCrianca);
        if (crianca == null) {
            System.out.println("Criança não encontrada.");
            return -1;
        }

        try {
            if (crianca.getPorta() == null) {
                Agencia.setPorta(id, crianca, false);
            }

            else {
                Agencia.setPorta(id, crianca, true);
            }

            System.out.println("Porta cadastrada com sucesso!");
            return 0;
        }

        catch (Exception e) {
            System.out.println("Erro ao cadastrar porta: " + e.getMessage());
            return -1;
        }
    }

    public static int manipularEntidade(Scanner scanner) {
        System.out.println("\n=== MENU MANIPULAR ENTIDADE ===");

        System.out.println("1 - Manipular Cilindro.");
        System.out.println("2 - Manipular Criança.");
        System.out.println("3 - Manipular Gabinete.");
        System.out.println("4 - Manipular Monstro.");
        System.out.println("5 - Manipular Porta.");
        System.out.println("6 - Retornar.");

        System.out.print("Escolha uma opção: ");

        return validarOpcao(scanner, 1, 6);
    } // Menu para manipular as entidades já cadastradas

    public static int manipularCilindro(Scanner scanner) {
        System.out.println("\n=== MANIPULAR CILINDRO ===");

        Agencia.mostrarCilindros();
        System.out.print("Digite o índice do cilindro a ser manipulado: ");
        int indexCilindro = validarInt(scanner);
        if (indexCilindro == -1) { return -1; }

        Cilindro cilindro = Agencia.getCilindro(indexCilindro);
        if (cilindro == null) {
            System.out.println("Cilindro não encontrado.");
            return -1;
        }

        int resp = perguntarSimNao(scanner, "Mudar ID do cilindro (atual: " + cilindro.getId() + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.print("Digite o novo ID do cilindro: ");
            int novoId = validarInt(scanner);
            if (novoId == -1) { return -1; }

            boolean idExists = false;
            for (Cilindro c : Agencia.getCilindros()) {
                if (c.getId() == novoId && c != cilindro) {
                    idExists = true;
                    break;
                }
            }
            if (idExists) {
                System.out.println("Erro: ID já existe para outro cilindro.");
                return -1;
            }

            try {
                cilindro.setId(novoId);
                System.out.println("ID do cilindro alterado com sucesso!");
                return 0;
            }

            catch (Exception e) {
                System.out.println("Erro ao alterar ID do cilindro: " + e.getMessage());
                return -1;
            }
        } else {
            System.out.println("Alteração de ID cancelada.");
            return 0;
        }
    }

    public static int manipularCrianca(Scanner scanner) {
        System.out.println("\n=== MANIPULAR CRIANÇA ===");

        Agencia.mostrarCriancas();
        System.out.print("Digite o índice da criança a ser manipulada: ");
        int indexCrianca = validarInt(scanner);
        if (indexCrianca == -1) { return -1; }

        Crianca crianca = Agencia.getCrianca(indexCrianca);
        if (crianca == null) {
            System.out.println("Criança não encontrada.");
            return -1;
        }

        int resp = perguntarSimNao(scanner, "Mudar nome da criança (atual: " + crianca.getNome() + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.print("Digite o novo nome da criança: ");
            String novoNome = validarString(scanner);
            if (novoNome == null) { return -1; }

            try {
                crianca.setNome(novoNome);
                System.out.println("Nome da criança alterado com sucesso!");
                return 0;
            }

            catch (Exception e) {
                System.out.println("Erro ao alterar nome da criança: " + e.getMessage());
                return -1;
            }
        } else {
            System.out.println("Alteração de nome cancelada.");
            return 0;
        }
    }

    public static int manipularGabinete(Scanner scanner) {
        System.out.println("\n=== MANIPULAR GABINETE ===");

        System.out.println("Selecione o gabinete:");
        Agencia.mostrarGabinetes();

        System.out.print("Digite o índice do gabinete: ");
        int gabineteIndex = validarInt(scanner);

        Gabinete gabinete = Agencia.getGabinete(gabineteIndex);
        if (gabinete == null) {
            System.out.println("Gabinete não encontrado.");
            return -1;
        }

        int resp = perguntarSimNao(scanner, "Mudar ID do gabinete (atual: " + gabinete.getId() + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
        System.out.print("Digite o novo ID do gabinete: ");
        int novoId = validarInt(scanner);
        if (novoId == -1) { return -1; }

        boolean idExists = false;
        for (Gabinete g : Agencia.getGabinetes()) {
            if (g.getId() == novoId && g != gabinete) {
                idExists = true;
                break;
            }
        }
        if (idExists) {
            System.out.println("Erro: ID já existe para outro gabinete.");
            return -1;
        }

        try {
            gabinete.setId(novoId);
            System.out.println("ID do gabinete alterado com sucesso!");
        }

        catch (Exception e) {
            System.out.println("Erro ao alterar ID do gabinete: " + e.getMessage());
            return -1;
        }
        } else {
            System.out.println("Alteração de ID cancelada.");
        }        
        
        resp = perguntarSimNao(scanner, "Mudar a porta do gabinete (atual: " + (gabinete.getPorta() != null ? gabinete.getPorta().getId() : "Nenhuma") + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.println("\nÍndices das portas:");
            Agencia.mostrarPortas();

            System.out.println("Digite o índice: ");
            int index = validarInt(scanner);
            if (index == -1) { return -1; }

            Porta porta = Agencia.getPorta(index);
            if (porta == null) {
                System.out.println("Porta não encontrada.");
                return -1;
            }

            gabinete.setPorta(porta);
        }
        else {
            System.out.println("Troca de porta cancelada.");
        }

        resp = perguntarSimNao(scanner, "Mudar o monstro principal do gabinete (atual: " + (gabinete.getMonstroPrincipal() != null ? gabinete.getMonstroPrincipal().getNome() : "Nenhum") + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.println("\nÍndices dos monstros principais:");
            Agencia.mostrarMonstrosPrincipal();

            System.out.println("Digite o índice: ");
            int index = validarInt(scanner);
            if (index == -1) { return -1; }

            Monstro monstro = Agencia.getMonstroPrincipal(index);
            if (monstro == null) {
                System.out.println("Monstro não encontrado.");
                return -1;
            }

            gabinete.setMonstroPrincipal(monstro);
        }
        else {
            System.out.println("Troca de monstro cancelada.");
        }

        resp = perguntarSimNao(scanner, "Mudar o monstro de suporte do gabinete (atual: " + (gabinete.getMonstroAuxiliar() != null ? gabinete.getMonstroAuxiliar().getNome() : "Nenhum") + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.println("\nÍndices dos monstros de suporte:");
            Agencia.mostrarMonstrosAuxiliar();

            System.out.println("Digite o índice: ");
            int index = validarInt(scanner);
            if (index == -1) { return -1; }

            MonstroDeSuporte monstro = (MonstroDeSuporte) Agencia.getMonstroAuxiliar(index);
            if (monstro == null) {
                System.out.println("Monstro não encontrado.");
                return -1;
            }

            gabinete.setMonstroAuxiliar(monstro);
        }
        else {
            System.out.println("Troca de monstro cancelada.");
        }

        resp = perguntarSimNao(scanner, "Mudar o cilindro do gabinete (atual: " + (gabinete.getCilindro() != null ? gabinete.getCilindro().getId() : "Nenhum") + ")?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.println("\nÍndices dos cilindros:");
            Agencia.mostrarCilindros();

            System.out.println("Digite o índice: ");
            int index = validarInt(scanner);
            if (index == -1) { return -1; }

            Cilindro cilindro = Agencia.getCilindro(index);
            if (cilindro == null) {
                System.out.println("Cilindro não encontrado.");
                return -1;
            }

            gabinete.setCilindro(cilindro);
        }
        else {
            System.out.println("Troca de cilindro cancelada.");
        }

        return 0;
    }

    public static int manipularMonstro(Scanner scanner) {
        System.out.println("\n=== MANIPULAR MONSTRO ===");

        System.out.println("Selecione o tipo de monstro:");
        System.out.println("0 - Monstro de Susto/Riso.");
        System.out.println("1 - Monstro auxiliar.");

        int opcao = validarInt(scanner);
        if (opcao == -1) { return -1; }
        
        if (opcao == 0 || opcao == 1) {
            System.out.println("Selecione o índice do monstro:");
            
            if (opcao == 0) {
                Agencia.mostrarMonstrosPrincipal();
                
                int indexMonstro = validarInt(scanner);
                if (indexMonstro == -1) { return -1; }
                
                Monstro monstro = Agencia.getMonstroPrincipal(indexMonstro);
                if (monstro == null) {
                    System.out.println("Monstro não encontrado.");
                    return -1;
                }

                System.out.println("Mudar o nome do Monstro para:");
                String nome = validarString(scanner);
                if (nome == null) { return -1;}

                monstro.setNome(nome);
                
                System.out.println("O nome do monstro foi mudado para: " + monstro.getNome());
            }

            else if (opcao == 1) {
                Agencia.mostrarMonstrosAuxiliar();

                int indexMonstro = validarInt(scanner);
                if (indexMonstro == -1) { return -1; }
                
                Monstro monstro = Agencia.getMonstroAuxiliar(indexMonstro);
                if (monstro == null) {
                    System.out.println("Monstro não encontrado.");
                    return -1;
                }

                System.out.println("Mudar o nome do Monstro para:");
                String nome = validarString(scanner);
                if (nome == null) { return -1;}

                monstro.setNome(nome);

                System.out.println("O nome do monstro foi mudado para: " + monstro.getNome());
            }      
        }
        else {
            System.out.println("Opção inválida.");
        }

        return 0;
    }

    public static int manipularPorta(Scanner scanner) {
        System.out.println("\n=== MANIPULAR PORTA ===");

        System.out.println("Índices das portas: ");
        Agencia.mostrarPortas();

        System.out.println("Digite o índice da porta a ser manipulada: ");
        int portaIndex = validarInt(scanner);

        Porta porta = Agencia.getPorta(portaIndex);
        if (porta == null) {
            System.out.println("Porta não encontrada.");
            return -1;
        }

        int resp = perguntarSimNao(scanner, "Mudar o ID da porta?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.print("Digite o novo ID da porta: ");
            int novoId = validarInt(scanner);
            if (novoId == -1) { return -1; }

            boolean idExists = false;
            for (Porta p : Agencia.getPortas()) {
                if (p.getId() == novoId && p != porta) {
                    idExists = true;
                    break;
                }
            }
            if (idExists) {
                System.out.println("Erro: ID já existe para outra porta.");
                return -1;
            }

            try {
                porta.setId(novoId);
                System.out.println("ID da porta alterado com sucesso!");
            }

            catch (Exception e) {
                System.out.println("Erro ao alterar ID da porta: " + e.getMessage());
                return -1;
            }
        } else {
            System.out.println("Alteração de ID cancelada.");
        }

        resp = perguntarSimNao(scanner, "Mudar a criança associada da porta?");
        if (resp == -1) return -1;
        if (resp == 1) {
            System.out.println("\nSelecione a nova criança para associar à porta:");
            Agencia.mostrarCriancas();

            System.out.print("Digite o índice da criança: ");
            int indexCrianca = validarInt(scanner);
            if (indexCrianca == -1) { return -1; }

            Crianca crianca = Agencia.getCrianca(indexCrianca);
            if (crianca == null) {
                System.out.println("Criança não encontrada.");
                return -1;
            }

            try {
                porta.changeCrianca(crianca);
                System.out.println("Criança associada à porta alterada com sucesso!");
                return 0;
            }

            catch (Exception e) {
                System.out.println("Erro ao alterar criança da porta: " + e.getMessage());
                return -1;
            }
        } else {
            System.out.println("Alteração de criança cancelada.");
            return 0;
        }
    }

    public static void executarGabinete(Scanner scanner) {
        System.out.println("\n=== PROCESSAR GABINETE ===");

        Agencia.mostrarGabinetes();
        
        System.out.print("Digite o índice do gabinete a processar: ");
        try {
            int indexGabinete = validarInt(scanner);
            
            Gabinete gabineteProcessar = Agencia.getGabinete(indexGabinete);
            if (gabineteProcessar == null) {
                System.out.println("Gabinete não encontrado.");
                return;
            }
            
            Agencia.processarGabinete(indexGabinete);
        } catch (IllegalArgumentException | IllegalStateException e) {
            System.out.println("Erro ao processar gabinete: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Erro inesperado ao processar gabinete: " + e.getMessage());
        }
    } // Método para chamar a função processarGabinete para o gabinete escolhido

    public static void menuInterativo() {
        Scanner scanner = new Scanner(System.in);
        int opcao;

        while (true) {
            opcao = mostrarOpcoes(scanner);

            switch (opcao) {
                case 1:
                    opcao = cadastrarNovaEntidade(scanner);

                    if (opcao == -1) { break; }

                    else {
                        if (opcao == 1) { cadastrarCilindro(scanner); }
                        else if (opcao == 2) { cadastrarCrianca(scanner); }
                        else if (opcao == 3) { cadastrarGabinete(scanner); }
                        else if (opcao == 4) { cadastrarMonstro(scanner); }
                        else if (opcao == 5) { cadastrarPorta(scanner); }
                    }

                    break;

                case 2:
                    opcao = manipularEntidade(scanner);

                    if (opcao == -1) { break; }

                    else {
                        if (opcao == 1) { manipularCilindro(scanner); }
                        else if (opcao == 2) { manipularCrianca(scanner); }
                        else if (opcao == 3) { manipularGabinete(scanner); }
                        else if (opcao == 4) { manipularMonstro(scanner); }
                        else if (opcao == 5) { manipularPorta(scanner); }
                    }
                    
                    break;

                case 3:
                    Agencia.mostrarEntidadesCadastradas();
                    break;

                case 4:
                    executarGabinete(scanner);
                    break;

                case 5:
                    scanner.close();
                    return;

                default:
                    System.out.println("Opção inválida, tente novamente!");
                    break;
            }
        }
    } // Menu interativo

    public static void salvarDados() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("data/agencia.csv"))) {
            // Salvar Criancas
            writer.println("Criancas");
            writer.println("nome,energiaSusto,energiaRiso,portaId");
            for (Crianca c : Agencia.getCriancas()) {
                try {
                    writer.println(c.getNome() + "," + c.getEnergia("susto") + "," + c.getEnergia("riso") + "," + (c.getPorta() != null ? c.getPorta().getId() : ""));
                } catch (Exception e) {
                    System.err.println("Erro ao salvar criança " + c.getNome() + ": " + e.getMessage());
                }
            }
            writer.println();

            // Salvar Monstros Principais
            writer.println("MonstrosPrincipais");
            writer.println("nome,eficiencia,tipo");
            for (Monstro m : Agencia.getMonstrosPrincipal()) {
                try {
                    writer.println(m.getNome() + "," + m.getRawEficiencia() + "," + m.getTipoMonstro());
                } catch (Exception e) {
                    System.err.println("Erro ao salvar monstro principal " + m.getNome() + ": " + e.getMessage());
                }
            }
            writer.println();

            // Salvar Monstros Auxiliares
            writer.println("MonstrosAuxiliares");
            writer.println("nome,eficiencia,tipo");
            for (Monstro m : Agencia.getMonstrosAuxiliares()) {
                try {
                    writer.println(m.getNome() + "," + m.getRawEficiencia() + "," + m.getTipoMonstro());
                } catch (Exception e) {
                    System.err.println("Erro ao salvar monstro auxiliar " + m.getNome() + ": " + e.getMessage());
                }
            }
            writer.println();

            // Salvar Portas
            writer.println("Portas");
            writer.println("id,criancaNome");
            for (Porta p : Agencia.getPortas()) {
                try {
                    writer.println(p.getId() + "," + (p.getCrianca() != null ? p.getCrianca().getNome() : ""));
                } catch (Exception e) {
                    System.err.println("Erro ao salvar porta " + p.getId() + ": " + e.getMessage());
                }
            }
            writer.println();

            // Salvar Cilindros
            writer.println("Cilindros");
            writer.println("id,armazenado");
            for (Cilindro c : Agencia.getCilindros()) {
                try {
                    writer.println(c.getId() + "," + c.getArmazenado());
                } catch (Exception e) {
                    System.err.println("Erro ao salvar cilindro " + c.getId() + ": " + e.getMessage());
                }
            }
            writer.println();

            // Salvar Gabinetes
            writer.println("Gabinetes");
            writer.println("id,portaId,monstroPrincipalNome,monstroAuxiliarNome,cilindroId");
            for (Gabinete g : Agencia.getGabinetes()) {
                try {
                    String portaId = g.getPorta() != null ? String.valueOf(g.getPorta().getId()) : "";
                    String mpNome = g.getMonstroPrincipal() != null ? g.getMonstroPrincipal().getNome() : "";
                    String maNome = g.getMonstroAuxiliar() != null ? g.getMonstroAuxiliar().getNome() : "";
                    String cilindroId = g.getCilindro() != null ? String.valueOf(g.getCilindro().getId()) : "";
                    writer.println(g.getId() + "," + portaId + "," + mpNome + "," + maNome + "," + cilindroId);
                } catch (Exception e) {
                    System.err.println("Erro ao salvar gabinete " + g.getId() + ": " + e.getMessage());
                }
            }

            System.out.println("Dados salvos com sucesso em data/agencia.csv");
        } catch (IOException e) {
            System.err.println("Erro ao salvar dados: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Erro inesperado ao salvar dados: " + e.getMessage());
        }
    } // Método para salvar os dados

    public static void carregarDados() {
        try (BufferedReader reader = new BufferedReader(new FileReader("data/agencia.csv"))) {
            String line;
            Map<String, Crianca> criancasMap = new HashMap<>();
            Map<String, Monstro> monstrosMap = new HashMap<>();
            Map<Integer, Porta> portasMap = new HashMap<>();
            Map<Integer, Cilindro> cilindrosMap = new HashMap<>();
            Map<String, Function<String, Monstro>> monstroFactory = Map.of(
                "susto", MonstroDoSusto::new,
                "riso", MonstroDoRiso::new,
                "suporte", MonstroDeSuporte::new
            );

            while ((line = reader.readLine()) != null) {
                if (line.equals("Criancas")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        if (parts.length == 4) {
                            try {
                                Crianca c = new Crianca(parts[0]);
                                c.setEnergiaSusto(Integer.parseInt(parts[1]));
                                c.setEnergiaRiso(Integer.parseInt(parts[2]));
                                Agencia.addCrianca(c);
                                criancasMap.put(c.getNome(), c);
                            } catch (NumberFormatException e) {
                                System.err.println("Erro ao parsear energia da criança: " + e.getMessage());
                            }
                        }
                    }
                } else if (line.equals("MonstrosPrincipais")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        try {
                            Monstro m = monstroFactory.getOrDefault(parts[2], n -> null).apply(parts[0]); // Lambda para criação de monstro
                            if (m != null) {
                                m.setEficiencia(Double.parseDouble(parts[1]));
                                Agencia.addMonstroPrincipal(m);
                                monstrosMap.put(m.getNome(), m);
                            }
                        } catch (NumberFormatException e) {
                            System.err.println("Erro ao parsear eficiência do monstro principal: " + e.getMessage());
                        }
                    }
                } else if (line.equals("MonstrosAuxiliares")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        if (parts.length == 3) {
                            try {
                                Monstro m = monstroFactory.getOrDefault(parts[2], n -> null).apply(parts[0]); // Lambda para criação de monstro
                                if (m != null) {
                                    m.setEficiencia(Double.parseDouble(parts[1]));
                                    Agencia.addMonstroAuxiliar(m);
                                    monstrosMap.put(m.getNome(), m);
                                }
                            } catch (NumberFormatException e) {
                                System.err.println("Erro ao parsear eficiência do monstro auxiliar: " + e.getMessage());
                            }
                        }
                    }
                } else if (line.equals("Portas")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        if (parts.length == 2) {
                            try {
                                int id = Integer.parseInt(parts[0]);
                                Crianca c = criancasMap.get(parts[1]);
                                Porta p = new Porta(id);
                                p.setCrianca(c);
                                if (c != null) c.setPorta(p);
                                Agencia.addPorta(p);
                                portasMap.put(id, p);
                            } catch (NumberFormatException e) {
                                System.err.println("Erro ao parsear ID da porta: " + e.getMessage());
                            }
                        }
                    }
                } else if (line.equals("Gabinetes")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        if (parts.length == 5) {
                            try {
                                int id = Integer.parseInt(parts[0]);
                                Porta porta = portasMap.get(Integer.parseInt(parts[1]));
                                Monstro mp = monstrosMap.get(parts[2]);
                                MonstroDeSuporte ma = (MonstroDeSuporte) monstrosMap.get(parts[3]);
                                Cilindro c = cilindrosMap.get(Integer.parseInt(parts[4]));
                                Gabinete g = new Gabinete(id, porta, mp, ma, c);
                                Agencia.addGabinete(g);
                            } catch (NumberFormatException e) {
                                System.err.println("Erro ao parsear dados do gabinete: " + e.getMessage());
                            } catch (ClassCastException e) {
                                System.err.println("Erro: Monstro auxiliar não é do tipo suporte: " + e.getMessage());
                            }
                        }
                    }
                } else if (line.equals("Cilindros")) {
                    reader.readLine(); // skip header
                    while ((line = reader.readLine()) != null && !line.trim().isEmpty()) {
                        String[] parts = line.split(",");
                        if (parts.length == 2) {
                            try {
                                int id = Integer.parseInt(parts[0]);
                                Cilindro c = new Cilindro(id);
                                c.setArmazenado(Integer.parseInt(parts[1]));
                                Agencia.addCilindro(c);
                                cilindrosMap.put(id, c);
                            } catch (NumberFormatException e) {
                                System.err.println("Erro ao parsear dados do cilindro: " + e.getMessage());
                            }
                        }
                    }
                }
            }
            System.out.println("Dados carregados com sucesso de data/agencia.csv");
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo de dados não encontrado: " + e.getMessage() + ". Iniciando com dados vazios.");
        } catch (IOException e) {
            System.err.println("Erro ao carregar dados: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Erro inesperado ao carregar dados: " + e.getMessage());
        }
    } // Método para carregar os dados
}
