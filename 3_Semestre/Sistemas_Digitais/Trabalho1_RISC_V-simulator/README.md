# RISC-V Simulator

Este projeto é um simulador de instruções RISC-V desenvolvido como parte de um projeto acadêmico. Ele interpreta e executa instruções RISC-V a partir de arquivos de entrada, simulando o comportamento de registradores e memória.

## Como funciona o projeto

O simulador lê um arquivo de entrada contendo instruções RISC-V, analisa as instruções e as executa. Ele suporta diferentes formatos de instruções, como:

- **Formato R**: Instruções aritméticas e lógicas entre registradores.
- **Formato I**: Instruções com valores imediatos e operações de carga de memória.
- **Formato S**: Instruções de armazenamento na memória.
- **Formato U**: Instruções de manipulação de valores imediatos superiores.

O simulador mantém o estado dos registradores e da memória, permitindo visualizar os valores após a execução das instruções.

## Como rodar o projeto

### Pré-requisitos

- Sistema operacional Linux.
- Compilador `g++` instalado.
- Visual Studio Code (opcional, mas recomendado).

### Passos para execução

1. **Compilar o projeto**:
   - Utilize o comando abaixo para compilar o projeto manualmente:
     ```bash
     g++ -fdiagnostics-color=always -g src/main.cpp src/simulator.cpp src/instruction.cpp src/registers.cpp src/memory.cpp src/utils/parser.cpp -o a.out
     ```
   - Ou, se estiver usando o Visual Studio Code, execute a tarefa de build configurada no arquivo `tasks.json`:
     - Vá para o menu "Terminal" > "Run Task" > "C/C++: g++ build project".

2. **Executar o simulador**:
   - Após a compilação, execute o programa com o comando:
     ```bash
     ./a.out
     ```
   - Insira o nome do arquivo de entrada (ex.: `entrada1.txt` ou `entrada2.txt`) quando solicitado.

3. **Visualizar o estado**:
   - O simulador exibirá o estado dos registradores e da memória após a execução das instruções.

## Como criar entradas válidas

Os arquivos de entrada devem conter instruções RISC-V válidas, uma por linha. As instruções podem incluir comentários iniciados com `#`. Seguem algumas regras e exemplos:

### Regras gerais

- Cada linha deve conter uma instrução no formato RISC-V.
- Os registradores devem ser referenciados como `t0`, `t1`, ..., `t31`.
- O registrador `t0` deve ser mantido com o valor `0`.
- Comentários podem ser adicionados após o caractere `#`.
- Linhas em branco ou apenas com comentários serão ignoradas.

### Exemplos de instruções válidas

#### Arquivo `entrada1.txt`:
```assembly
addi t1, zero, 10      # t1 = 10
addi t2, zero, 20      # t2 = 20
add  t3, t1, t2        # t3 = t1 + t2 = 30
lui  t4, 0x10000       # t4 = 0x10000000 = 268435456
sw   t3, 0(t4)         # memória[268435456] = 30
```

#### Arquivo `entrada2.txt`:
```assembly
addi t1, zero, 5       # t1 = 5
addi t2, zero, 7       # t2 = 7

# linha comentada
add  t3, t1, t2        # soma t1 e t2

lui  t4, 0x10000       # carrega endereço base
sw   t3, 0(t4)         # salva resultado
```

### Formatos de instruções suportados

- **Formato R**: `add t3, t1, t2`
- **Formato I**: `addi t1, zero, 10`
- **Formato S**: `sw t3, 0(t4)`
- **Formato U**: `lui t4, HEXADECIMAL`

Certifique-se de que os arquivos de entrada estejam no mesmo diretório do executável ou forneça o caminho completo ao executá-lo.

---

Com essas informações, você poderá compilar, executar e criar entradas válidas para o simulador RISC-V.
