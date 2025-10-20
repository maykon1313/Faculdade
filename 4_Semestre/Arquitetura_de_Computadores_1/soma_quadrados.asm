# ------------------------------------------------------------------------------
# Soma dos quadrados dos elementos de um vetor de tamanho n
# ------------------------------------------------------------------------------
# Programa principal
#
# Algoritmo:
#    lê x e y do teclado
#    result = soma_quadrados(x,y)
#    escreve result na tela
# Uso dos registradores:
#    a0: parâmetro x da função soma_quadrados e usado para chamadas ao sistema
#    a1: parâmetro y da função soma_quadrados
#    a2: valor de retorno de função soma_quadrados
#    a7: usado para chamadas ao sistema
#    s0: x
#    s1: y
#    s2: result
# ------------------------------------------------------------------------------
          .text                    # Seção de código
# ------------------------------------------------------------------------------
main:                              # Lê x e y do teclado
          addi a7, zero, 4         # Chamada ao sistema para escrever string na tela
          la   a0, msg1            # a0 = endereço da string a ser escrita na tela
          ecall
          addi a7, zero, 5         # Chamada ao sistema para ler inteiro do teclado
          ecall                    # a0 receberá inteiro lido do teclado
          add  s0, a0, zero        # s0 = x
          addi a7, zero, 4         # Chamada ao sistema para escrever string na tela
          la   a0, msg2            # a0 = endereço da string a ser escrita na tela
          ecall
          addi a7, zero, 5         # Chamada ao sistema para ler inteiro do teclado
          ecall                    # a0 receberá inteiro lido do teclado
          add  s1, a0, zero        # s1 = y
                                   # -----------------------------------------
          add  a0, s0, zero        # a0 = x
          add  a1, s1, zero        # a1 = y
          jal  ra, soma_quadrados  # Chama função soma_quadrados(x,y)
          add  s2, a2, zero        # s2 = result (valor de retorno da função)
                                   # -----------------------------------------
                                   # Escreve result na tela
          addi a7, zero, 4         # Chamada ao sistema para escrever string na tela
          la   a0, msg3            # a0 = endereço da string a ser escrita na tela
          ecall
          addi a7, zero, 1         # Chamada ao sistema para escrever inteiro na tela (soma)
          add  a0, s2, zero        # a0 = inteiro a ser escrito na tela
          ecall
                                   # -----------------------------------------
          addi a7, zero,10         # Chamada ao sistema para encerrar programa
          ecall
# ------------------------------------------------------------------------------
# Função soma_quadrados(x, y)
#    Possui chamadas aninhadas de função
#
# Algoritmo:
#    s = quadrado(x) + quadrado(y)
#    retorna s
#
# Uso dos registradores:
#    a0: parâmetro x da função soma_quadrado e parâmetro n da função quadrado
#    a1: parâmetro y da função soma_quadrado
#    a2: valor de retorno da função quadrado e
#        valor de retorno s da função soma_quadrados
#    t0: x^2
#    t1: y^2
#    ra: endereço de retorno da função
#    sp: stack pointer (endereço na memória de dado no topo da pilha)
# ------------------------------------------------------------------------------
soma_quadrados:                    # Prólogo
          addi sp, sp, -4          # Aloca espaço na pilha para 1 palavra
          sw   ra, 0 (sp)          # Salva endereço de retorno na pilha
                                   # -----------------------------------------
          jal  ra, quadrado        # Chama função quadrado(x)
          add  t0, a2, zero        # t0 = valor retornado (x^2)
                                   # -----------------------------------------
          add  a0, a1, zero        # a0 = y
          jal  ra, quadrado        # Chama função quadrado(y)
          add  t1, a2, zero        # t1 = valor retornado (y^2)
                                   # -----------------------------------------
                                   # Prepara valor de retorno da função soma_quadrados
          add  a2, t0, t1          # s = x^2 + y^2
                                   # -----------------------------------------
                                   # Epílogo
          lw   ra, 0 (sp)          # Restaura endereço de retorno da pilha
          addi sp, sp, 4           # Libera espaço de 1 palavra na pilha
                                   # -----------------------------------------
          jalr zero, 0 (ra)        # Retorna da função
# ------------------------------------------------------------------------------
# Função quadrado(n)
#
# Algoritmo:
#    q = n * n
#    retorna q
#
# Uso dos registradores:
#    a0: parâmetro n da função quadrado
#    a2: valor de retorno q da função quadrado
#    ra: endereço de retorno da função
# ------------------------------------------------------------------------------
quadrado:
          mul  a2, a0, a0          # q = n * n
                                   # -----------------------------------------
          jalr zero, 0 (ra)        # Retorna da função
# ------------------------------------------------------------------------------
          .data                    # Seção de dados
# ------------------------------------------------------------------------------
msg1:     .asciz "Entre com x: "
msg2:     .asciz "Entre com y: "
msg3:     .asciz "Resultado: "
# ------------------------------------------------------------------------------
