#######especiais#######
def ler_disciplinas_dos_alunos_e_alunos_das_disciplinas(entrada): # mat,port ; ing ; mat, ing
    saida = []
    entrada = entrada.split(";")
    alunos = 0
    while alunos < len(entrada):
        aluno = entrada[alunos].split(",")
        if aluno[0] != '':
            saida.append(aluno)
        elif len(aluno) != 1:
            aluno_novo = []
            i = 1
            while i < len(aluno):
                aluno_novo.append(aluno[i])
                i += 1
            saida.append(aluno_novo)
        else:
            saida.append([])
        alunos += 1
    
    return saida

def procura(busca, lista):
    i = 0
    while i < len(lista):
        if busca == lista[i]:
            return i
        i += 1
    return -1

def remover(index_aluno, alunos, aluno_cpf, disciplinas_alunos, alunos_disciplina, cpf):
    materias = disciplinas_alunos[index_aluno]  #Disciplinas que o aluno está matriculado

    j = 0
    while j < len(materias):
        materiazinha = materias[j] #Para cada disciplina matriculada
        index_dici = procura(materiazinha, disciplinas)
        alunos_disciplina = remover_alunos_disciplina(index_dici, index_aluno, alunos_disciplina, cpf) #Remove o aluno da disciplina
        j += 1
    
    disciplinas_alunos = remover_disciplinas_alunos(index_aluno, disciplinas_alunos) #Remove o aluno junto com as disciplinas matriculada

    alunos_novo = []
    aluno_cpf_nova = []

    i = 0
    while (i < len(alunos)):
        if (i != index_aluno):
            alunos_novo.append(alunos[i])
            aluno_cpf_nova.append(aluno_cpf[i])
        i += 1
    
    return alunos_novo, aluno_cpf_nova, disciplinas_alunos, alunos_disciplina

def remover_das_disciplina(nome_da_disciplina, index_da_diciplina, disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos):
    disciplinas_novas = []
    alunos_das_disciplinas_novas = []

    i = 0
    while i < len(disciplinas):
        if i != index_da_diciplina:
            disciplinas_novas.append(disciplinas[i])
            alunos_das_disciplinas_novas.append(alunos_das_disciplinas[i])
        i += 1
    
    j = 0
    while j < len(disciplinas_dos_alunos):
        aluno = disciplinas_dos_alunos[j]
        aluno_novo = []
        z = 0
        while z < len(aluno):
            if aluno[z] != nome_da_disciplina:
                aluno_novo.append(aluno[z])
            z += 1
        disciplinas_dos_alunos[j] = aluno_novo
        j += 1
    
    return disciplinas_novas, alunos_das_disciplinas_novas, disciplinas_dos_alunos

def remover_disciplinas_alunos(index_aluno, disciplinas_alunos):
    disciplinas_alunos_novo = []
    i = 0
    while (i < len(disciplinas_alunos)):
        if (i != index_aluno):
            disciplinas_alunos_novo.append(disciplinas_alunos[i])
        i += 1
    
    return disciplinas_alunos_novo

def remover_alunos_disciplina(index_dici, index, alunos_disciplina, cpf):
    materia_nova = []
    materia = alunos_disciplina[index_dici]
    index_do_aluno = procura(cpf, materia)
    i = 0
    while (i < len(materia)):
        if (i != index_do_aluno):
            materia_nova.append(materia[i])
        i += 1
    
    alunos_disciplina[index_dici] = materia_nova

    return alunos_disciplina

def cancelar_maticula(index_dici, index, disciplinas_alunos, alunos_disciplina, dici, cpf):
    #disciplinas_alunos:
    index_da_dici_no_disciplinas_dos_alunos = procura(dici, disciplinas_dos_alunos[index])
    matriculado = []
    aluno_dici = disciplinas_alunos[index]
    i = 0
    while (i < len(aluno_dici)):
        if (i != index_da_dici_no_disciplinas_dos_alunos):
            matriculado.append(aluno_dici[i])
        i += 1
    
    disciplinas_alunos[index] = matriculado

    #alunos_das_disciplinas:
    materia = alunos_das_disciplinas[index_dici]
    index_do_cpf_na_alunos_das_disciplinas = procura(cpf, materia)
    materia_nova = []
    
    i = 0
    while (i < len(materia)):
        if (i != index_do_cpf_na_alunos_das_disciplinas):
            materia_nova.append(materia[i])
        i += 1
    
    alunos_disciplina[index_dici] = materia_nova

    return disciplinas_alunos, alunos_disciplina

def alterar_CPF_do_aluno_nas_disciplinas(CPF, novo_CPF, alunos_disciplina):
    i = 0
    while i < len(alunos_disciplina):
        disciplina = alunos_disciplina[i]
        index = procura(CPF, disciplina)

        if index != -1:
            disciplina[index] = novo_CPF
        
        alunos_disciplina[i] = disciplina

        i += 1
    
    return alunos_disciplina

def alterar_nome_das_disciplinas_nos_aluno_matriculados(dici, novo_nome, disciplinas_alunos):
    i = 0
    while i < len(disciplinas_alunos):
        disciplina = disciplinas_alunos[i]
        index = procura(dici, disciplina)

        if index != -1:
            disciplina[index] = novo_nome
        
        disciplinas_alunos[i] = disciplina

        i += 1
    
    return disciplinas_alunos

def escrever_o_arquivo_para_salvar_normal(vetor):
    i = 0
    resu = ''
    while i < len(vetor):
        resu += vetor[i] + " "
        i += 1
    return resu

def escrever_o_arquivo_para_salvar_bizarro(vetor_de_vetores):
    resu = ''
    i = 0
    while i < len(vetor_de_vetores):
        vetor = vetor_de_vetores[i]
        j = 0
        while j < len(vetor):
            if j < len(vetor)-1:
                resu += vetor[j] + ","
            else:
                resu += vetor[j]
            j += 1
        if i < len(vetor_de_vetores)-1:
            resu += ";"
        i += 1
    
    return resu

#######especiais#######

arquivo = open("Matriculas.txt", "r")

nomes_dos_alunos = arquivo.readline().split()
cpf_dos_alunos = arquivo.readline().split()
disciplinas_dos_alunos = ler_disciplinas_dos_alunos_e_alunos_das_disciplinas(arquivo.readline().strip())
disciplinas = arquivo.readline().split()
alunos_das_disciplinas = ler_disciplinas_dos_alunos_e_alunos_das_disciplinas(arquivo.readline().strip())

#######Menu#######
def menu():
    print("O que tu qué?")
    print("1 - Cadastrar, editar, remover ou listar ALUNOS")
    print("2 - Cadastrar, editar, remover e listar DISCIPLINAS")
    print("3 - Matricular ALUNO em uma DISCIPLINA")
    print("4 - Cancelar matrícula de um ESTUDANTE")
    print("5 - Relatório de matrícula por DISCIPLINA")
    print("6 - Sair")

    escolha = int(input())

    return escolha
#######Menu#######


#######Alunos#######
def cadastrar_aluno():
    print("Digite o nome e o CPF do sujeito:")
    nome, cpf = input().split()
    nomes_dos_alunos.append(nome)
    cpf_dos_alunos.append(cpf)
    disciplinas_dos_alunos.append([])
    print("Aluno cadastrado.")

def editar_alunos():
    print("Nome ou CPF?")
    print("1 - Nome")
    print("2 - CPF")
    escolha = int(input())

    if escolha == 1:
        print("Qual o CFP desse indivíduo?")
        cpf = input()
        index_do_aluno = procura(cpf, cpf_dos_alunos)

        if index_do_aluno == -1:
            print("Aluno não cadastrado.")
        else:
            print("Mudou de nome, qual é o novo?")
            novo_nome = input()
            nomes_dos_alunos[index_do_aluno] = novo_nome
            print("O nome foi alterado.")

    elif escolha == 2:
        print("Qual o CPF desse indivíduo?")
        cpf = input()
        index = procura(cpf, cpf_dos_alunos)

        if index == -1:
            print("CPF não cadastrado.")
        else:
            print("Mudou de CPF é, qual é o novo?")
            novo_cpf = input()
            alunos_disciplina = alterar_CPF_do_aluno_nas_disciplinas(cpf, novo_cpf, alunos_das_disciplinas)
            cpf_dos_alunos[index] = novo_cpf
            print("O nome CPF alterado.")

    else:
        print("Ação inválida.")

def remover_alunos(nomes_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_das_disciplinas):
    print("Digite o CPF:")
    cpf = input()
    index_aluno = procura(cpf, cpf_dos_alunos)

    if index_aluno == -1:
         print("CPF não cadastrado.")
    else:
        nomes_dos_alunos_novo, cpf_dos_alunos_novo, disciplinas_dos_alunos_novo, alunos_das_disciplinas_novo = remover(index_aluno, nomes_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_das_disciplinas, cpf)
        print("Aluno eliminado da face da Terra.")
        return nomes_dos_alunos_novo, cpf_dos_alunos_novo, disciplinas_dos_alunos_novo, alunos_das_disciplinas_novo

def listar_alunos():
    print("ALUNOS:")
    i = 0
    while i < len(nomes_dos_alunos):
        print(str(i) + " - " + str(nomes_dos_alunos[i]) + ": " + str(cpf_dos_alunos[i]))
        i += 1
#######Alunos#######


#######Disciplinas#######
def cadastrar_disciplina():
    print("Nome da disciplina:")
    disciplina = input()
    disciplinas.append(disciplina)
    alunos_das_disciplinas.append([])
    print("Disciplina cadastrada.")

def editar_disciplina():
    print("Disciplina?")
    dici = input()

    index_da_diciplina = procura(dici, disciplinas)

    if index_da_diciplina == -1:
        print("Disciplina não foi achada não.")
    else:
        print("Qual o novo nome?")
        novo_nome = input()
        disciplinas_alunos = alterar_nome_das_disciplinas_nos_aluno_matriculados(dici, novo_nome, disciplinas_dos_alunos)
        disciplinas[index_da_diciplina] = novo_nome
        print("Nome foi alterado.")

def remover_disciplina(disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos):
    print("Digite o nome da Disciplina:")
    dici = input()
    index_da_diciplina = procura(dici, disciplinas)

    if index_da_diciplina == -1:
        print("Disciplina não cadastrada.")
    else:
        disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos = remover_das_disciplina(dici, index_da_diciplina, disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos)
        print("Disciplina eliminada.")

    return disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos

def listar_disciplina():
    i = 0
    while i < len(disciplinas):
        if i == 0:
            resu = str(disciplinas[i])
        elif i < len(disciplinas) - 1:
            resu = resu + ", " + str(disciplinas[i])
        else:
            resu = resu + ", " + str(disciplinas[i]) + "."
        i += 1
    print("Disciplinas: " + str(resu))
#######Disciplinas#######


#######Matrícular#######
def matricular_aluno_na_materia():
    print("Qual disciplina?")
    dici = input()

    index_dici = procura(dici, disciplinas)

    if index_dici == -1:
        print("Disciplina não cadastrada.")
    else:
        print("Qual o CPF do aluno?")
        cpf = input()

        index_aluno = procura(cpf, cpf_dos_alunos)

        if index_aluno == -1:
            print("Aluno não cadastrado.")
        else:
            disciplinas_dos_alunos[index_aluno].append(dici)
            alunos_das_disciplinas[index_dici].append(cpf)
            nome = nomes_dos_alunos[index_aluno]
            print("Aluno " + str(nome) + " foi matriculado na disciplina: " + str(dici) + ".")
#######Matrícular#######


#######Cancelar matrícula#######
def cancelar_matricula_do_aluno_na_materia(alunos_das_disciplinas, disciplinas_dos_alunos):
    print("Qual o CPF do meliante?")
    cpf = input()

    index_aluno = procura(cpf, cpf_dos_alunos)

    if index_aluno == -1:
        print("Esse CPF é inválido.")
    else:
        print("Qual a disciplina?")
        dici = input()

        index_dici = procura(dici, disciplinas)

        if index_dici == -1:
            print("A disciplina não foi cadastrada.")
        else:
            #Confirir se ele está cadastrado nessa disciplina
            alunos_nessa_disciplina = alunos_das_disciplinas[index_dici]
            ta = procura(cpf, alunos_nessa_disciplina)

            if ta == -1:
                print("Aluno não matriculado nessa matéria.")
            else:
                disciplinas_dos_alunos, alunos_das_disciplinas = cancelar_maticula(index_dici, index_aluno, disciplinas_dos_alunos, alunos_das_disciplinas, dici, cpf)
                print("Aluno eliminado da matéria.")
#######Cancelar matrícula#######


#######Relatório#######
def relatorio():
    i = 0
    while i < len(disciplinas):
        alunos = alunos_das_disciplinas[i]
        if len(alunos) == 0:
            print(str(disciplinas[i]) + ": Nenhum aluno.")

        elif alunos[0] != '' or len(alunos) != 1:
            j = 0
            while j < len(alunos):
                index_nome = procura(alunos[j], cpf_dos_alunos)

                if j == 0:
                   resu = str(nomes_dos_alunos[index_nome] + ": " + str(alunos[j]))
                elif j < (len(alunos) - 1):
                    resu = resu + ", " + str(nomes_dos_alunos[index_nome] + ": " + str(alunos[j]))
                else:
                    resu = resu + ", " + str(nomes_dos_alunos[index_nome] + ": " + str(alunos[j])) + "."
                j += 1

            if len(alunos) == 1:
                resu += "."

            print(str(disciplinas[i]) + ": " + str(resu))
        i += 1
#######Relatório#######


#######Sair#######
def sair():
    arquivo = open("Matriculas.txt", "w")

    resu = escrever_o_arquivo_para_salvar_normal(nomes_dos_alunos)
    arquivo.write(resu + "\n")

    resu = escrever_o_arquivo_para_salvar_normal(cpf_dos_alunos)
    arquivo.write(resu + "\n")

    resu = escrever_o_arquivo_para_salvar_bizarro(disciplinas_dos_alunos)
    arquivo.write(resu + "\n")

    resu = escrever_o_arquivo_para_salvar_normal(disciplinas)
    arquivo.write(resu + "\n")

    resu = escrever_o_arquivo_para_salvar_bizarro(alunos_das_disciplinas)
    arquivo.write(resu + "\n")

    print("Informações salvas.")
#######Sair#######

continua = True
while continua:
    escolha = 0
    escolha = menu()

    if escolha == 1: #Alunos
        escolha = 0
        print("O que tu qué fazer? Alunos.")
        print("1 - Cadastrar")
        print("2 - Editar")
        print("3 - Remover")
        print("4 - Listar")
        escolha = int(input())

        if escolha == 1:
            cadastrar_aluno()
        elif escolha == 2:
            editar_alunos()
        elif escolha == 3:
            nomes_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_das_disciplinas = remover_alunos(nomes_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_das_disciplinas)
            print("a")
        elif escolha == 4:
            listar_alunos()
        else:
            print("Ação inválida.")

    elif escolha == 2: #Disciplinas
        escolha = 0
        print("O que tu qué? Disciplinas.")
        print("1 - Cadastrar")
        print("2 - Editar")
        print("3 - Remover")
        print("4 - Listar")
        escolha = int(input())

        if escolha == 1:
            cadastrar_disciplina()
        elif escolha == 2:
            editar_disciplina()
        elif escolha == 3:
            disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos = remover_disciplina(disciplinas, alunos_das_disciplinas, disciplinas_dos_alunos)
            print("a")
        elif escolha == 4:
            listar_disciplina()
        else:
            print("Ação inválida.")
        
    elif escolha == 3: #Matrícular
        matricular_aluno_na_materia()

    elif escolha == 4: #Cancelar matrícula
        cancelar_matricula_do_aluno_na_materia(alunos_das_disciplinas, disciplinas_dos_alunos)

    elif escolha == 5: #Relatório
        relatorio()

    elif escolha == 6: #Sair
        continua = False
        sair()