# ------------------------------------------------------------------------------
# Soma elementos de vetor de tamanho n
# ------------------------------------------------------------------------------
# Algoritmo:
#    lê n do teclado
#    se n <= max então
#    |  soma = 0
#    |  for (i = 0 ; i < n ; i++)
#    |  |  soma = soma + vetor[i]
#    |  escreve soma na tela
#    senão
#    |  escreve msg de erro na tela
# ------------------------------------------------------------------------------
# Uso dos registradores:
#    a0, a7: usados para chamadas ao sistema
#    t0: soma
#    t1: i
#    t2: n
#    t3: endereço de vetor[i] na memória
#    t4: vetor[i]
#    t5: auxiliar
#    t6: max
# ------------------------------------------------------------------------------
          .text                      # Seção de código
# ------------------------------------------------------------------------------
main:                                # Lê n do teclado
          addi a7, zero, 4           # Chamada ao sistema para escrever string na tela
          la   a0, msg1              # a0 = endereço da string a ser escrita na tela
          ecall
          addi a7, zero, 5           # Chamada ao sistema para ler inteiro do teclado
          ecall                      # a0 receberá inteiro lido do teclado
          add  t2, a0, zero          # t2 = n
                                     # -----------------------------------------
          lw   t6, max               # t6 = valor de max lido da memória
                                     # -----------------------------------------
          blt  t6, t2, else          # Se max < n então desvia para else
                                     # -----------------------------------------
                                     # Laço for (i = 0 ; i < n ; i++)
          la   t3, vetor             # t3 = endereço inicial do vetor na memória
          add  t0, zero, zero        # soma = 0
          add  t1, zero, zero        # i = 0
loop:     bge  t1, t2, fimloop       # Se i >= n então desvia para fora do laço
          lw   t4, 0 (t3)            # t4 = vetor[i] lido da memória
          add  t0, t0, t4            # soma = soma + vetor[i]
          addi t3, t3, 4             # t3 = t3 + 4 (endereço de vetor[i] na memória)
          addi t1, t1, 1             # i++
          jal  zero, loop            # Desvia para início do laço
fimloop:  sw   t0, soma, t5          # Escreve t0 na memória em soma
                                     # -----------------------------------------
                                     # Escreve soma na tela
          addi a7, zero, 4           # Chamada ao sistema para escrever string na tela
          la   a0, msg3              # a0 = endereço da string a ser escrita na tela
          ecall
          addi a7, zero, 1           # Chamada ao sistema para escrever inteiro na tela (soma)
          add  a0, t0, zero          # a0 = inteiro a ser escrito na tela
          ecall
          jal  zero, fimif           # Desvia para fora do if (pula corpo do else)
else:                                # -----------------------------------------
          addi a7, zero, 4           # Escreve msg de erro na tela
          la   a0, msg2              # Chamada ao sistema para escrever string na tela
          ecall                      # a0 = endereço da string a ser escrita na tela
                                     # -----------------------------------------
fimif:    addi a7, zero,10           # Chamada ao sistema para encerrar programa
          ecall
# ------------------------------------------------------------------------------
          .data                      # Seção de dados
# ------------------------------------------------------------------------------
max:      .word 10                   # Número máximo de elementos do vetor
vetor:    .word 10 20 30 40 50 60 70 80 90 100 # Vetor de 10 elementos
soma:     .word 0
msg1:     .asciz "Entre com n: "
msg2:     .asciz "Valor de n deve ser no máximo 10"
msg3:     .asciz "Soma: "
# ------------------------------------------------------------------------------