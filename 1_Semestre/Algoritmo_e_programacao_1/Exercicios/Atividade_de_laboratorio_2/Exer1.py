def tranformadestrparacou(vetor):
    result = []

    # Initialize the index for the while loop
    index = 0

    # Process each split string to convert to a list
    while index < len(vetor):
        item = vetor[index]

        # Convert the string representation to a list
        if item == '[]':
            # If it's an empty list, append an empty list
            result.append([])
        else:
            # Otherwise, we assume it's a list with content
            try:
                # Use eval to convert the string representation to a list
                result.append(eval(item))
            except (SyntaxError, NameError):
                # In case of an invalid string, we could skip or handle the error
                result.append(None)

        # Increment the index
        index += 1
    return result

arquivo = open("Faculdade.txt", "r")

alunos = arquivo.readline().strip().split()                                     #NOMES
aluno_cpf = arquivo.readline().strip().split()                                  #CPF
disciplinas_alunos = tranformadestrparacou(arquivo.readline().strip().split())  #DISCIPLINAS DE CADA ALUNOS
disciplinas = arquivo.readline().strip().split()                                #DISCIPLINAS
alunos_disciplina = tranformadestrparacou(arquivo.readline().strip().split())   #ALUNOS EM CADA DISCIPLINA

def procura(busca, lista):
    i = 0
    while i < len(lista):
        if busca == lista[i]:
            return i
        i += 1
    return -1

def remover(index_aluno, alunos, aluno_cpf, disciplinas_alunos, alunos_disciplina):
    materias = disciplinas_alunos[index_aluno]  #Disciplinas que o aluno está matriculado

    j = 0
    while j < len(materias):
        materiazinha = materias[j] #Para cada disciplina matriculada
        index_dici = procura(materiazinha, disciplinas)
        alunos_disciplina = remover_alunos_disciplina(index_dici, index_aluno, alunos_disciplina) #Remove o aluno da disciplina
        j += 1
    
    disciplinas_alunos = remover_disciplinas_alunos(index_aluno, disciplinas_alunos) #Remove o aluno junto com as disciplinas matriculada

    alunos_novo = []
    aluno_cpf_nova = []

    i = 0
    while (i < len(alunos)) and (i != index_aluno):
        alunos_novo.append(alunos[i])
        aluno_cpf_nova.append(aluno_cpf[i])
        i += 1
    
    return alunos_novo, aluno_cpf_nova, disciplinas_alunos, alunos_disciplina

def remover_disciplinas_alunos(index_aluno, disciplinas_alunos):
    disciplinas_alunos_novo = []
    i = 0
    while (i < len(disciplinas_alunos)) and (i != index_aluno):
        disciplinas_alunos_novo.append(disciplinas_alunos[i])
        i += 1
    
    return disciplinas_alunos_novo

def remover_alunos_disciplina(index_dici, index, alunos_disciplina):
    materia_nova = []
    materia = alunos_disciplina[index_dici]
    i = 0
    while (i < len(materia)) and (i != index):
        materia_nova.append(materia[i])
        i += 1
    
    alunos_disciplina[index_dici] = materia_nova

    return alunos_disciplina

def cancelar_maticula(index_dici, index, disciplinas_alunos, alunos_disciplina):
    #disciplinas_alunos:
    matriculado = []
    aluno_dici = disciplinas_alunos[index]
    i = 0
    while (i < len(aluno_dici)) and (i != index):
        matriculado.append(aluno_dici[i])
        i += 1
    
    disciplinas_alunos[index] = matriculado

    #alunos_disciplina:
    materia_nova = []
    materia = alunos_disciplina[index_dici]
    i = 0
    while (i < len(materia)) and (i != index):
        materia_nova.append(materia[i])
        i += 1
    
    alunos_disciplina[index] = materia_nova

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

def escrever_o_arquivo_para_salvar(vetor):
    i = 0
    resu = ""
    while i < len(vetor):
        if i == 0:
            resu = str(vetor[0])
        else:
            resu = resu + " " + str(vetor[i])
        i += 1
    
    return resu
        

isso_tem_que_ser_levado_a_serio_e_to_falando_serio = True

while isso_tem_que_ser_levado_a_serio_e_to_falando_serio:
    print("O que tu qué?")
    print("1 - Cadastrar, editar, remover ou listar ALUNOS")
    print("2 - Cadastrar, editar, remover e listar DISCIPLINAS")
    print("3 - Matricular ALUNO em uma DISCIPLINA")
    print("4 - Cancelar matrícula de um ESTUDANTE")
    print("5 - Relatório de matrícula por DISCIPLINA")
    print("6 - Sair")

    escolha = int(input())

    if escolha == 1: #Alunos
        print("O que tu qué? Alunos.")
        print("1 - Cadastrar")
        print("2 - editar")
        print("3 - remover")        #TO DO: REMOVER DO disciplinas_alunos E alunos_disciplina
        print("4 - listar")
        escolha = int(input())

        if escolha == 1:
            print("Digite o nome e o CPF de sujeito:")
            nome, cpf = input().split()
            alunos.append(nome)
            aluno_cpf.append(cpf)
            disciplinas_alunos.append([])
            print("Aluno cadastrado.")

        elif escolha == 2:
            print("Nome ou CPF?")
            print("1 - Nome")
            print("2 - CPF")
            escolha = int(input())

            if escolha == 1:
                qual = input("Qual o CFP desse indivíduo?")
                index = procura(qual, aluno_cpf)

                if index == -1:
                    print("Aluno não cadastrado.")
                else:
                    novo_nome = input("Mudou de nome é?")
                    alunos[index] = novo_nome
                    print("O nome foi alterado.")

            elif escolha == 2:
                print("Qual o CPF desse indivíduo?")
                CPF = input()
                index = procura(CPF, aluno_cpf)

                if index == -1:
                    print("CPF não cadastrado.")
                else:
                    print("Mudou de CPF é, qual é?")
                    novo_CPF = input()
                    alunos_disciplina = alterar_CPF_do_aluno_nas_disciplinas(CPF, novo_CPF, alunos_disciplina)
                    aluno_cpf[index] = novo_CPF
                    print("O nome CPF alterado.")

            else:
                print("Valor digitado inválido.")

        elif escolha == 3:
            cpf = input("Digite o CPF:")
            index_aluno = procura(cpf, aluno_cpf)

            if index_aluno == -1:
                print("CPF não cadastrado.")
            else:
                alunos, aluno_cpf, disciplinas_alunos, alunos_disciplina = remover(index_aluno, alunos, aluno_cpf, disciplinas_alunos, alunos_disciplina)
                print("Aluno eliminado da face da Terra.")

        elif escolha == 4:
            i = 0
            while i < len(alunos):
                print(str(alunos[i]) + ": " + str(aluno_cpf[i]))
                i += 1

        else:
            print("Ação inválida.")

    elif escolha == 2: #Disciplinas
        print("O que tu qué? Disciplinas.")
        print("1 - Cadastrar")
        print("2 - editar")         #TO DO: Alterar o nome para todos
        print("3 - remover")        
        print("4 - listar")
        escolha = int(input())

        if escolha == 1:
            print("Nome da disciplina:")
            disciplina = input()
            disciplinas.append(disciplina)
            alunos_disciplina.append([])
            print("Disciplina cadastrada.")

        elif escolha == 2:
            print("Disciplina?")
            dici = input()

            index = procura(dici, disciplinas)

            if index == -1:
                print("Disciplina não foi achada não.")
            else:
                print("Qual o novo nome?")
                novo_nome = input()
                disciplinas_alunos = alterar_nome_das_disciplinas_nos_aluno_matriculados(dici, novo_nome, disciplinas_alunos)
                disciplinas[index] = novo_nome
                print("Nome foi alterado.")

        elif escolha == 3:
            dici = input("Digite o nome da Disciplina:")
            index = procura(dici, disciplinas)

            if index == -1:
                print("Disciplina não cadastrada.")
            else:
                disciplinas, alunos_disciplina = remover(index, disciplinas, alunos_disciplina)
                print("Disciplina eliminada.")

        elif escolha == 4:
            i = 0
            while i < len(disciplinas):
                if i == 0:
                    resu = str(disciplinas[i])
                elif i < len(disciplinas) - 1:
                    resu = resu + ", " + str(disciplinas[i])
                else:
                    resu = resu + ", " + str(disciplinas[i]) + "."
            print("Disciplinas: " + str(resu))

        else:
            print("Ação inválida.")   

    elif escolha == 3: #Matricular
        print("Qual disciplina?")
        dici = input()

        index_dici = procura(dici, disciplinas)

        if index_dici == -1:
            print("Disciplina não cadastrada.")
        else:
            print("Qual o CPF do aluno?")
            aluno = input()

            index_aluno = procura(aluno, aluno_cpf)

            if index_aluno == -1:
                print("Aluno não cadastrado.")
            else:
                disciplinas_alunos[index_aluno].append(dici)
                alunos_disciplina[index_dici].append(aluno)
                nome = alunos[index_aluno]
                print("Aluno " + str(nome) + " foi matriculado na disciplina: " + str(dici) + ".")

    elif escolha == 4: #Cancelar matricula
        print("Qual o CPF do meliante?")
        cpf = input()

        index_aluno = procura(cpf, aluno_cpf)

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
                alunos_nessa_disciplina = alunos_disciplina[index_dici]
                ta = procura(cpf, alunos_nessa_disciplina)

                if ta == -1:
                    print("Aluno não matriculado nessa matéria.")
                else:
                    disciplinas_alunos, alunos_disciplina = cancelar_maticula(index_dici, index_aluno, disciplinas_alunos, alunos_disciplina)
                    print("ALuno eliminado da matéria.")

    elif escolha == 5: #Relatório
        i = 0
        while i < len(disciplinas):
            alunos = alunos_disciplina[i]
            j = 0
            while j < len(alunos):
                if j == 0:
                    resu = str(alunos[0])
                elif j < (len(alunos) - 1):
                    resu = resu + ", " + str(alunos[j])
                else:
                    resu = resu + ", " + str(alunos[j]) + "."
                j += 1

            print(str(disciplinas[i]) + ": " + str(resu))
            i += 1

    elif escolha == 6: #Sair
        arquivo = open("Faculdade.txt", "w")

        resu = escrever_o_arquivo_para_salvar(alunos)
        arquivo.write(resu + "\n")

        resu = escrever_o_arquivo_para_salvar(aluno_cpf)
        arquivo.write(resu + "\n")

        resu = escrever_o_arquivo_para_salvar(disciplinas_alunos)
        arquivo.write(resu + "\n")

        resu = escrever_o_arquivo_para_salvar(disciplinas)
        arquivo.write(resu + "\n")

        resu = escrever_o_arquivo_para_salvar(alunos_disciplina)
        arquivo.write(resu + "\n")

        print("Informações salvas.")

        isso_tem_que_ser_levado_a_serio_e_to_falando_serio = False