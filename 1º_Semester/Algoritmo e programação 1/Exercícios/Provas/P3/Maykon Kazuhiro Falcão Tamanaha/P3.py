alunos_info = open("alunos.csv", "r")
opinioes_info = open("opinioes.csv", "r")

dados_alunos = alunos_info.readlines()
opinioes = opinioes_info.readlines()

alunos_info.close()
opinioes_info.close()

def listar(dados_alunos):
    i = 0
    while i < len(dados_alunos):
        nome = dados_alunos[i].strip().split(",")[0]
        print(nome)
        i += 1
    nome = input()
    return nome

def opinioes_aluno_especifico(nome, opinioes):
    opinioes_aluno = []
    i = 0
    while i < len(opinioes):
        if nome == opinioes[i].split(",")[0]:
            opinioes_aluno.append(opinioes[i])
        i += 1
    opinioes_aluno = ordenar_bubble(opinioes_aluno)
    return opinioes_aluno

def ordenar_bubble(vetor):
    i = 0
    while i < len(vetor) -1:
        j = 0
        while j < len(vetor) -1:
            if len(vetor[j]) < len(vetor[j +1]):
                vetor[j], vetor[j +1] = vetor[j +1], vetor[j]
            j += 1
        i += 1
    return vetor

def escrever_relatorio(nome, opinioes_aluno):
    relatorio = open(str(nome)+".out", "w")
    i = 0
    while i < len(opinioes_aluno):
        relatorio.write(str(opinioes_aluno[i]))
        i += 1

continua = True
while continua:
    print("O que fazer?")
    print("1 - Cadastrar aluno.")
    print("2 - Cadastrar opinião.")
    print("3 - Relatório de aluno.")
    print("4 - Sair.")

    escolha = int(input())

    if escolha == 1:
        print("Nome, data e Curso? (nome,data,Curso)")
        dados_alunos.append(input())
        print("Aluno cadastrado.")

    elif escolha == 2:
        print("Qual o nome do aluno?")
        nome = listar(dados_alunos)
        print("Positiva ou negativa. Qual a opinião? (Positiva,legal ele.)")
        opinioes.append(nome + "," + input() + "\n")
        print("Opinião cadastrada.")

    elif escolha == 3:
        print("Qual o nome do aluno?")
        nome = listar(dados_alunos)
        opinioes_aluno = opinioes_aluno_especifico(nome, opinioes)
        escrever_relatorio(nome, opinioes_aluno)
        print("Relatório pronto.")

    elif escolha == 4:
        continua = False

def saida(Filepointer, vetor):
    i = 0
    while i < len(vetor):
        Filepointer.write(str(vetor[i]))
        i += 1

alunos_info = open("alunos.csv", "w")
opinioes_info = open("opinioes.csv", "w")
saida(alunos_info, dados_alunos)
saida(opinioes_info, opinioes)
alunos_info.close()
opinioes_info.close()