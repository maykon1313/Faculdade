def isInVector(name, vector):
	i = 0
	while i < len(vector):
		if name == vector[i]:
			return True
		i += 1
	return False

def bubbleSort(vector):
	i = 0
	length = len(vector)
	while i < length - 1:
		j = 0
		while j < length - i - 1:
			if len(vector[j]) < len(vector[j + 1]):
				aux = vector[j]
				vector[j] = vector[j + 1]
				vector[j + 1] = aux
			j += 1
		i += 1
	return vector 

print("Bem vindo usuário, informe a opção que deseja: ")
print("1 - Cadastrar aluno")
print("2 - Cadastrar opinião sobre aluno")
print("3 - Gerar relatório sobre aluno")
print("4 - Sair do sistema")

listaAlunos = list(open("alunos.csv", "r"))
listaOpinioes = list(open("opinioes.csv", "r"))
nomes = []
i = 0
while i < len(listaAlunos):
	listaAlunos[i] = listaAlunos[i].strip("\n")
	nomes.append(listaAlunos[i].split(",")[0])
	i += 1

continua = True
while continua:
	opinioesAtual = []
	escolha = int(input())
	match escolha:
		case 1:
			print("Informe os dados do aluno a ser cadastrado:")
			dadosAluno = input()
			alunoSplit = dadosAluno.split(",")
			if isInVector(alunoSplit[0], nomes) == False:
				listaAlunos.append(dadosAluno)
				nomes.append(alunoSplit[0].strip())
				print("Aluno cadastrado com sucesso")
			else:
				print("Nome de aluno já cadastrado")
		case 2:
			print("Informe o nome, sentimento e opinião sobre determinado aluno:")
			opiniao = input()
			opiniaoSplit = opiniao.split(",")
			if isInVector(opiniaoSplit[0], nomes) == True:
				listaOpinioes.append(opiniao)
				print("Opinião cadastrada com sucesso")
			else:
				print("Nome de aluno não cadastrado")
		case 3:
			print("Informe o nome do aluno do qual deseja gerar um relatório: ")
			nomeDoAluno = input().strip()
			if isInVector(nomeDoAluno, nomes) == True:
				while i < len(listaOpinioes):
					if listaOpinioes[i].split(",")[0] == nomeDoAluno:
						opinioesAtual.append(listaOpinioes[i])
					i += 1
				print(f'Relatório gerado com nome {nomeDoAluno}.out')
			else:
				print("Nome do aluno não cadastrado")
			opinioesAtual = bubbleSort(opinioesAtual)
			relatorioAluno = open(f'{nomeDoAluno}.out', "w")
			i = 0
			while i < len(opinioesAtual):
				opinioesAtual[i] = opinioesAtual[i].strip("\n")
				relatorioAluno.write(opinioesAtual[i] + "\n")
				i += 1
			relatorioAluno.close()
		case 4:
			print("Adeus.")
			continua = False
		case _:
			print("OPÇÃO INVALIDA")

i = 0
arquivoAlunos = open("alunos.csv", "w")
arquivoOpinioes = open("opinioes.csv", "w")

while i < len(listaAlunos):
	arquivoAlunos.write(listaAlunos[i] + "\n")
	i += 1
i = 0
while i < len(listaOpinioes):
	arquivoOpinioes.write(listaOpinioes[i] + "\n")
	i += 1
arquivoAlunos.close()
arquivoOpinioes.close()