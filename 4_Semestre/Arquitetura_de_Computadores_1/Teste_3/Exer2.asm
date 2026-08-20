#---------------------------------------------
# Programa 2: Instruções com conflitos
#---------------------------------------------
       .text              # Seção de código:
       .org 0x00000200    # Inicia no endereço 0x00000200 da memória

main:  # Instruções com conflitos
       addi t1, zero, 1
       addi t5, zero, 5
       lw   t0, a (zero)
       add  t2, t1, t0
       sub  t3, t5, t1
       or   t4, t3, t2
       sw   t3, b (zero)
       and  t6, t5, zero

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

a:     .word 9
b:     .word 12
#---------------------------------------------