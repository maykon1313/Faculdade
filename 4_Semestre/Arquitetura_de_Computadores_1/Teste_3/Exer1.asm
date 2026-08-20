#---------------------------------------------
# Programa 1: Instruções sem conflitos
#---------------------------------------------
       .text              # Seção de código:
       .org 0x00000200    # Inicia no endereço 0x00000200 da memória

main:  # Inicializa registradores
       addi s2, zero, 2
       addi s3, zero, 3
       addi s5, zero, 5
       addi s6, zero, 6
       addi s7, zero, 7
       addi s9, zero, 9

       # Instruções NOP: passam pelos estágios do pipeline sem fazer nada
       # (usadas aqui para que instruções addi terminem de executar)
       nop
       nop
       nop
       nop
       nop

       # Instruções sem conflitos
       lw   s0, a (zero)
       add  s1, s2, s3
       sub  s4, s6, s5
       sw   s7, b (zero)
       and  s8, s3, s9

       # Instruções NOP: passam pelos estágios do pipeline sem fazer nada
       # (usadas aqui para que instruções terminem de executar)
       nop
       nop
       nop
       nop
       ecall
#---------------------------------------------
       .data              # Seção de dados:
       .org 0x00000000    # Inicia no endereço 0x00000000 da memória

a:     .word 15
b:     .word 0
#---------------------------------------------