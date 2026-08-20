package Tratamento_de_Excecoes;

public class Exer_1 {
    public static String buscarUsuario(String id) {
        if (id == null || id.isBlank()) {
            throw new IllegalArgumentException("ID inválido. Não pode ser nulo ou vazio.");
        }
        return "Usuário encontrado: " + id;
    }

    public static void main(String[] args) {
        try {
            System.out.println(buscarUsuario("123"));
            System.out.println(buscarUsuario(null));
        } catch (IllegalArgumentException e) {
            System.out.println("Erro ao buscar usuário: " + e.getMessage());
        }
    }
}