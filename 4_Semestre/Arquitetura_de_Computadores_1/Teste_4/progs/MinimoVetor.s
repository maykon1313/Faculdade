#------------------------------------------------------------------------------
# Programa MinimoVetor: obtem elemento de menor valor de um vetor
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
						.text									# Area de codigo
#------------------------------------------------------------------------------
# PROGRAMA PRINCIPAL
# Algoritmo:
#		min = vetor[0]
#		for (i = 1 ; i < n ; i++)
#			if vetor[i] < min
#				min = vetor[i]
#		Encerra execucao do programa
# Uso dos registradores:
#		s0: n
#		s1: endereço inicial de vetor[i] na memoria
#		s2: min
#		s3: i
#		t0: auxiliar para comparacao
#		t1: vetor[i]
#		a7: parametro para chamada ao sistema

																# Inicializacao
main:					addi	s0, zero, 16				# n = 16
						la		s1, vetor					# s1 = endereco de vetor[0] na memoria
						lw		s2, 0 (s1)					# min = vetor[0]
						addi	s1, s1, 4					# s1 = endereco do proximo elemento de vetor
						addi	s3, zero, 1					# i = 1
for:					slt	t0, s3, s0					# i < n ?
						beq	t0, zero, fora_for		# Se i >= n, desvia para fora do for
						lw		t1, 0 (s1)					# t1 = valor de vetor[i] lido da memoria
						slt	t0, t1, s2					# vetor[i] < min ?
						beq	t0, zero, fim_if			# Se vetor[i] >= min, desvia para fora do if
						add	s2, t1, zero				# min = vetor[i]
fim_if:				addi	s3, s3, 1					# i++
						addi	s1, s1, 4					# s1 = endereco do proximo elemento de vetor
						j		for							# Desvia para inicio do for
fora_for:			addi	a7, zero, 10				# Chamada ao sistema para encerrar programa
						ecall
#------------------------------------------------------------------------------
						.data									# Area de dados
#------------------------------------------------------------------------------
																# Variaveis e estruturas de dados do programa
vetor:				.word 9 10 2 6 13 15 12 5 7 14 4 3 11 8 9 10
#------------------------------------------------------------------------------
