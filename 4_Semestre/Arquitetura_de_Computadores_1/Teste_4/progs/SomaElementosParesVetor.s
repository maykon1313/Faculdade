#------------------------------------------------------------------------------
# Programa SomaElementosParesVetor: soma elementos de índice par de um vetor
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
#		soma = 0
#		for (i = 0 ; i < n ; i=i+2)
#			soma = soma + vetor[i]
#		Encerra execucao do programa
# Uso dos registradores:
#		s0: n
#		s1: endereço inicial de vetor[i] na memoria
#		s2: soma
#		s3: i
#		t0: auxiliar para comparacao
#		t1: vetor[i]
#		a7: parametro para chamada ao sistema

																# Inicializacao
main:					addi	x8, zero, 16				# n = 16
						la		s1, vetor					# s1 = endereco de vetor[0] na memoria
						add	s2, zero, zero				# soma = 0
						add	s3, zero, zero				# i = 0
for:					slt	t0, s3, s0					# i < n ?
						beq	t0, zero, fora_for		# Se i >= n, desvia para fora do for
						lw		t1, 0 (s1)					# t1 = valor de vetor[i] lido da memoria
						add	s2, s2, t1					# soma = soma + vetor[i]
						addi	s3, s3, 2					# i = i + 2
						addi	s1, s1, 8					# s1 = endereco do proximo elemento de índice par de vetor
						j		for							# Desvia para inicio do for
fora_for:			addi	a7, zero, 10				# Chamada ao sistema para encerrar programa
						ecall
#------------------------------------------------------------------------------
						.data									# Area de dados
#------------------------------------------------------------------------------
																# Variaveis e estruturas de dados do programa
vetor:				.word 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2
#------------------------------------------------------------------------------
