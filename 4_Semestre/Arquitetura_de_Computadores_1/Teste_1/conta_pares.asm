# --------------------------------------------------------------------------------------
# Conta, para um vetor de inteiros, o número de pares de elementos consecutivos iguais
# --------------------------------------------------------------------------------------
# Algoritmo:
#	c = 0
#	for (i = 0 ; i < n - 1 ; i++)
#	  if (vetor[i] == vetor[i+1])
#	   c++
#	escreve c na tela
# --------------------------------------------------------------------------------------
# Uso dos registradores:
#	a0 :	usado para chamadas ao sistema
#	a7 :	usado para chamadas ao sistema
#	t0 :	n-1
#	t1 :	c (contagem de pares de elementos consecutivos iguais)
#	t2:	i
#	t3 :	endereço de vetor[i] na memória
#	t4 :	vetor[i]
#	t5 :	vetor[i+1]
#	t6 :	auxiliar
# --------------------------------------------------------------------------------------

	.text
main:
	lw   t0, n              # t0 = valor de n lido da memória
	addi t0, t0, -1         # t0 = n-1 (limite do laço)
	add  t1, zero, zero     # t1 (c) = 0
	la   t3, vetor          # t3 = endereço inicial do vetor
	add  t2, zero, zero     # t2 (i) = 0

loop:
	bge  t2, t0, fimloop    # Se (i >= n-1), sai do laço
	lw   t4, 0(t3)          # t4 = vetor[i]
	lw   t5, 4(t3)          # t5 = vetor[i+1]
	bne  t4, t5, fimif      # Se vetor[i] != vetor[i+1], pula o incremento
	addi t1, t1, 1          # c++

fimif:
	addi t2, t2, 1          # i++
	addi t3, t3, 4          # Avança o ponteiro para o próximo elemento
	jal  zero, loop         # Volta ao início do laço

fimloop:
	addi a7, zero, 4        # Código para escrever string
	la   a0, msg            # a0 = endereço da string "Contagem: "
	ecall
	addi a7, zero, 1        # Código para escrever inteiro
	add  a0, t1, zero       # a0 = valor de c (t1)
	ecall
	
	addi a7, zero, 10       # Código para encerrar o programa
	ecall

# --------------------------------------------------------------------------------------
# Seção de Dados
# --------------------------------------------------------------------------------------
	.data
n:      .word 13
vetor:  .word 1, 3, 3, 5, 8, 4, 4, 2, 5, 2, 2, 2, 5
msg:    .asciz "Contagem: "