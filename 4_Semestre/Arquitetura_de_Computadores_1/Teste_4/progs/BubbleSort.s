#------------------------------------------------------------------------------
# Programa BubleSort: ordenacao pelo metodo da bolha
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
#		trocou = true
#		limite = n-1
#		while (limite > 0) AND (trocou)
#			trocou = false
#			for (i = 0 ; i < limite ; i++)
#				if vetor[i] > vetor[i+1]
#					// Troca elementos vetor[i] e vetor[i+1]
#					aux = vetor[i]
#					vetor[i] = vetor[i+1]
#					vetor[i+1] = aux
#					trocou = true
#			limite--
#		Encerra execução do programa
# Uso dos registradores:
#		s0: n
#		s1: endereço inicial de vetor na memoria
#		s2: trocou
#		s3: limite
#		s4: i
#		t0: auxiliar para comparacao
#		t1: endereco de vetor[i] na memoria
#		t2: vetor[i]
#		t3: vetor[i+1]
#		a7: parametro para chamada ao sistema

																# Inicializacao
main:					
						addi	s0, zero, 16				# n = 16
						la		s1, vetor					# s1 = endereco inicial de vetor na memoria
						addi	s2, zero, 1					# trocou = 1
						addi	s3, s0, -1					# limite = n-1
while:				slt	t0, zero, s3				# limite > 0 ?
						beq	t0, zero, fora_while		# Se limite <= 0, desvia para fora do while
						beq	s2, zero, fora_while		# Se trocou == false, desvia para fora do while
						add	s2, zero, zero				# trocou = 0
						add	s4, zero, zero				# i = 0
for:					slt	t0, s4, s3					# i < limite ?
						beq	t0, zero, fora_for		# Se i >= limite, desvia para fora do for
						add	t1, s4, s4					# t1 = i * 4
						add	t1, t1, t1
						add	t1, s1, t1					# t1 = endereco de vetor[i] na memoria
						lw		t2, 0 (t1)					# t2 = valor de vetor[i] lido da memoria
						lw		t3, 4 (t1)					# t3 = valor de vetor[i+1] lido da memoria
						slt	t0, t3, t2					# vetor[i] < vetor[i+1] ?
						beq	t0, zero, fora_if			# Se vetor[i] <= vetor[i+1], desvia para fora do if
																# Troca vetor[i] e vetor[i+1]
						sw		t3, 0 (t1)					# vetor[i] = t3
						sw		t2, 4 (t1)					# vetor[i+1] = t2
						addi	s2, zero, 1					# trocou = 1
fora_if:				addi	s4, s4, 1					# i++
						j		for							# Desvia para inicio do for
fora_for:			addi	s3, s3, -1					# limite--
						j		while							# Desvia para início do while
fora_while:			addi	a7, zero, 10				# Chamada ao sistema para encerrar programa
						ecall
#------------------------------------------------------------------------------
						.data									# Area de dados
#------------------------------------------------------------------------------
																# Variaveis e estruturas de dados do programa
vetor:				.word 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 # Vetor a ser ordenado
#------------------------------------------------------------------------------
