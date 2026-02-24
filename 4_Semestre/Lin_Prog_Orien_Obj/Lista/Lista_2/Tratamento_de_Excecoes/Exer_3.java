package Tratamento_de_Excecoes;

import java.io.IOException;

public class Exer_3 {
    public static String lerArquivoConfiguracao(String caminho) throws IOException {
        if (caminho == null || caminho.isBlank()) {
            throw new IOException("Caminho inválido. O arquivo não pôde ser carregado.");
        }
        return "Arquivo carregado com sucesso: " + caminho;
    }

    public static void main(String[] args) {
        try {
            System.out.println(lerArquivoConfiguracao("config.txt"));
            System.out.println(lerArquivoConfiguracao(""));
        } catch (IOException e) {
            System.out.println("Erro ao carregar arquivo: " + e.getMessage());
        }
    }
}