# README do Trabalho de LPOO

## Principais funções de cada classe

1. **Agência**: Responsável por gerenciar todas as entidades do sistema (monstros, portas, gabinetes, crianças e cilindros). Permite cadastrar, listar, selecionar e manipular essas entidades, além de processar gabinetes para geração de energia.

2. **Cilindro**: Responsável por armazenar energia gerada pelos monstros. Possui um limite máximo de 100 unidades e avisa quando cheio.

3. **Criança**: Representa uma criança com nome e energias base de susto e riso (geradas aleatoriamente). Pode estar associada a uma porta.

4. **Gabinete**: Coordena o processo de geração de energia, contendo uma porta (com criança), um monstro principal (susto ou riso), um monstro de suporte e um cilindro. Possui um método estático para processar a energia.

5. **Main**: Programa principal com menu interativo para manipular a agência. Carrega dados de um arquivo CSV no início e salva ao sair.

6. **Monstro**: Classe abstrata para monstros com nome e eficiência. Subclasses coletam energia da criança baseada no tipo (susto ou riso).

7. **MonstroDeSuporte**: Subclasse de Monstro que armazena energia no cilindro, aplicando fatores aleatórios adicionais.

8. **MonstroDoRiso**: Subclasse de Monstro especializada em gerar energia de riso.

9. **MonstroDoSusto**: Subclasse de Monstro especializada em gerar energia de susto.

10. **Porta**: Representa uma porta com ID, associada a uma criança.

## O que cada classe manipula

### Agência

1. Cadastrar novas entidades: Cilindros, Crianças, Gabinetes, Monstros (principais e auxiliares) e Portas.
2. Listar e selecionar entidades já cadastradas.
3. Manipular entidades: Alterar atributos como nome, ID, associações (ex.: trocar criança de uma porta).
4. Processar gabinete: Executar o processo de geração e armazenamento de energia em um gabinete específico.

### Cilindro

1. Armazenar energia até o limite de 100 unidades.
2. Avisar quando o armazenamento está cheio.

### Criança

1. Possuir nome e energias base de susto e riso (aleatórias).
2. Associar-se a uma porta.

### Gabinete

1. Coordenar monstro principal, monstro de suporte, porta e cilindro.
2. Processar energia: Monstro principal coleta energia da criança, monstro de suporte armazena no cilindro com variações aleatórias.

### Main

1. Menu interativo para todas as operações da agência.
2. Carregar dados iniciais de `data/agencia.csv`.
3. Salvar dados ao sair em `data/agencia.csv`.

### Monstro

1. Coletar energia da criança baseada no tipo (susto ou riso) e eficiência.
2. Para monstros de suporte: Armazenar energia no cilindro com eficiência adicional.

### Porta

1. Associar uma criança.
2. Possuir um ID único.

## Funcionalidades Adicionais

- **Persistência de Dados**: O programa carrega dados iniciais de `data/agencia.csv` e salva todas as alterações ao sair, permitindo continuidade entre execuções.
- **Processamento de Energia**: O gabinete processa energia aplicando fatores aleatórios para simular variação real.
- **Validação de Entrada**: Menus interativos com validação de entradas para evitar erros.
