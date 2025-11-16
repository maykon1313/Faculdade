#------------------------------------------------------------------------------
# Programa ProdutoEscalar: calcula produto escalar de 2 vetores
#------------------------------------------------------------------------------
# Para visualizacao correta do programa fonte, configure editor no MARS:
#		Ir em Settings -> Editor
#		Selecionar Tab Size = 3 (dar Apply and Close)
#------------------------------------------------------------------------------
# Para executar programa no MARS:
#		Ir em Settings -> Memory Configuration
#		Selecionar Default (dar Apply and Close)
#		Montar programa
#------------------------------------------------------------------------------
						.text										# Area de codigo
#------------------------------------------------------------------------------
# PROGRAMA PRINCIPAL
# Algoritmo:
#		prod = 0
#		for (i = 0 ; i < n ; i++)
#			prod = prod + vetorA[i] * vetorB[i]
#		Encerra execucao do programa
# Uso dos registradores:
#		s0: n
#		s1: endereço de vetorA[i] na memoria
#		s2: endereço de vetorB[i] na memoria
#		s3: prod
#		s4: i
#		t0: auxiliar para comparacao
#		t1: vetorA[i]
#		t2: vetorB[i]
#		t3: produto vetorA[i] * vetorB[i]
#		a7: parametro para chamada ao sistema

																# Inicializacao
main:					addi	s0, zero, 16				# n = 16
						la		s1, vetorA					# s1 = endereco de vetorA[0] na memoria
						la		s2, vetorB					# s2 = endereco de vetorB[0] na memoria
						add	s3, zero, zero				# prod = 0
						add	s4, zero, zero				# i = 0
for:					slt	t0, s4, s0					# i < n ?
						beq	t0, zero, fora_for		# Se i >= n, desvia para fora do for
						lw		t1, 0 (s1)					# t1 = valor de vetorA[i] lido da memoria
						lw		t2, 0 (s2)					# t2 = valor de vetorB[i] lido da memoria
						mul	t3, t1, t2							# t3 = vetorA[i] * vetorB[i]
						add	s3, s3, t3					# prod = prod + vetorA[i] * vetorB[i]
						addi	s4, s4, 1					# i++
						addi	s1, s1, 4					# s1 = endereco do proximo elemento de vetorA
						addi	s2, s2, 4					# s2 = endereco do proximo elemento de vetorB
						j		for							# Desvia para inicio do for
fora_for:			addi	a7, zero, 10				# Chamada ao sistema para encerrar programa
						ecall
#------------------------------------------------------------------------------
						.data									# Area de dados
#------------------------------------------------------------------------------
																# Variaveis e estruturas de dados do programa
vetorA:				.word 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
vetorB:				.word 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
#------------------------------------------------------------------------------
