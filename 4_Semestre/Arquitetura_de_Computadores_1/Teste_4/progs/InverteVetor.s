#------------------------------------------------------------------------------
# Programa InverteVetor: Inverte ordem dos elementos de um vetor
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
#		for (i = 0 ; i < n/2 ; i++)
#			aux1 = vetor[i]
#			aux2 = vetor[n-i-1]
#			vetor[i] = aux2
#			vetor[n-i-1] = aux1
#		Encerra execucao do programa
# Uso dos registradores:
#		s0: n
#		s1: endereço de vetor[i] na memoria
#		s2: endereço de vetor[n-i-1] na memoria
#		t0: auxiliar para comparacao
#		t1: vetor[i]
#		t2: vetor[n-i-1]
#		a7: parametro para chamada ao sistema

																# Inicializacao
main:					addi	s0, zero, 9					# n = 9
						la		s1, vetor					# s1 = endereco de vetor[0] na memoria
						add	s2, s0, s0					# s2 = n * 4
						add	s2, s2, s2
						add	s2, s1, s2					# 
						addi	s2, s2, -4					# s2 = endereco de vetor[n-1] na memoria
for:					slt	t0, s1, s2					# s1 < s2 ?
						beq	t0, zero, fora_for		# Se i >= n, desvia para fora do for
						lw		t1, 0 (s1)					# t1 = valor de vetor[i] lido da memoria
						lw		t2, 0 (s2)					# t2 = valor de vetor[n-i-1] lido da memoria
						sw		t2, 0 (s1)					# vetor[i] = t2
						sw		t1, 0 (s2)					# vetor[n-i-1] = t1
						addi	s1, s1, 4					# s1 = endereco do proximo elemento de vetor
						addi	s2, s2, -4					# s2 = endereco do elemento anterior de vetor
						j		for							# Desvia para inicio do for
fora_for:			addi	a7, zero, 10				# Chamada ao sistema para encerrar programa
						ecall
#------------------------------------------------------------------------------
						.data									# Area de dados
#------------------------------------------------------------------------------
																# Variaveis e estruturas de dados do programa
vetor:				.word 1 2 3 4 5 6 7 8 9
#------------------------------------------------------------------------------
