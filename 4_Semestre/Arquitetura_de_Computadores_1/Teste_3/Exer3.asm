#---------------------------------------------
# Programa 3: Instruções com conflitos
#---------------------------------------------
       .text                        # Seção de código:
       .org 0x00000200    # Inicia no endereço 0x00000200 da memória

       lw   t1, m (zero)
       addi t2, zero, 2
       addi t3, zero, 3
       addi t4, zero, 4
       beq  t1, zero, fim
       add  t2, t2, t2
       add  t3, t3, t3
       add  t4, t4, t4
fim:   sw   t2, n (zero)
       # Instruções NOP: passam pelos estágios do pipeline sem fazer nada
       # (usadas aqui para que instruções terminem de executar)
       nop
       nop
       nop
       nop
       ecall
# -----------------------------------------------------------------
       .data                       # Seção de dados:
       .org 0x00000000    # Inicia no endereço 0x00000000 da memória

m:     .word 1
n:     .word 0
# -----------------------------------------------------------------