def leitura_de_dados_vetores(entrada):
    entrada = entrada.split(";")
    i = 0
    while i < len(entrada):
        if entrada[i] == '':
            entrada[i] = []
        else:
            entrada[i] = entrada[i].split(",")
        i += 1
    
    return entrada

arquivo = open("matricula.txt", "r")

nome_dos_alunos = (arquivo.readline()).strip().split(";")
cpf_dos_alunos = (arquivo.readline()).strip().split(";")
disciplinas_dos_alunos = leitura_de_dados_vetores(arquivo.readline().strip())
disciplinas = (arquivo.readline()).strip().split(";")
alunos_nas_disciplinas = leitura_de_dados_vetores(arquivo.readline().strip())

def procurar(busca, lista):
    i = 0
    while i < len(lista):
        if busca == lista[i]:
            return i
        i += 1
    return -1

def menu():
    print("Qual ação você deseja fazer?")
    print("1 - Alunos.")
    print("2 - Disciplinas.")
    print("3 - Matricular.")
    print("4 - Cancelar matricula.")
    print("5 - Relatório.")
    print("6 - Sair.")

    escolha = int(input())

    return escolha

def menu_alunos():
    print("Qual ação você deseja fazer?")
    print("1 - Cadastrar aluno.")
    print("2 - Editar aluno.")
    print("3 - Remover aluno.")
    print("4 - Listar.")
    print("5 - Voltar.")

    escolha = int(input())

    return escolha

def menu_disciplina():
    print("1 - Cadastrar disciplina.")
    print("2 - Editar disciplina.")
    print("3 - Remover disciplina.")
    print("4 - Listar.")
    print("5 - Voltar.")

    escolha = int(input())

    return escolha

def cadastrar_aluno(nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos):
    print("Qual o CPF dele?")
    cpf = input()

    ja_esta = procurar(cpf, cpf_dos_alunos)

    if ja_esta == -1:
        print("Qual o nome dele?")
        nome = input()

        nome_dos_alunos.append(nome)
        cpf_dos_alunos.append(cpf)
        disciplinas_dos_alunos.append([])

    else:
        print("CPF já cadastrado.")
    
    return nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos

def editar_aluno(nome_dos_alunos, cpf_dos_alunos):
    print("Editar nome ou CPF?")
    print("1 - Nome.")
    print("2 - CPF.")
    print("3 - Voltar.")

    escolha = int(input())

    if escolha == 1:
        print("Qual o CPF dele?")
        cpf = input()

        index_aluno = procurar(cpf, cpf_dos_alunos)

        if index_aluno == -1:
            print("CPF não está cadastrado.")
        else:
            print("Qual o novo nome dele?")
            novo_nome = input()

            nome_dos_alunos[index_aluno] = novo_nome
            print("Nome alterado.")

    elif escolha == 2:
        print("Qual o CPF dele?")
        cpf = input()

        index_aluno = procurar(cpf, cpf_dos_alunos)

        if index_aluno == -1:
            print("CPF não está cadastrado.")
        else:
            print("Qual o novo CPF dele?")
            novo_cpf = input()

            ja_cadastrado = procurar(novo_cpf, cpf_dos_alunos)

            if ja_cadastrado == -1:
                cpf_dos_alunos[index_aluno] = novo_cpf
                print("CPF alterado.")
            
            else:
                print("Esse CPF já foi cadastrado.")

    elif escolha == 3:
        print("Voltando.")
    
    else:
        print("Ação inválida.")

    return nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos

#####################################################################################################
def remover_aluno(nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_nas_disciplinas):
    print("Qual o CPF do aluno?")
    cpf = input()

    index_aluno = procurar(cpf, cpf_dos_alunos)

    if index_aluno == -1:
        print("CPF na cadastrado.")
    else:
        nome_dos_alunos = remover_elemento_do_vetor_por_index(index_aluno, nome_dos_alunos)
        cpf_dos_alunos = remover_elemento_do_vetor_por_index(index_aluno, cpf_dos_alunos)
        disciplinas_dos_alunos = remover_elemento_do_vetor_por_index(index_aluno, disciplinas_dos_alunos)

        i = 0
        while i < len(alunos_nas_disciplinas):
            alunos = alunos_nas_disciplinas[i]

            if len(alunos) != 0:
                index_aluno = procurar(cpf, alunos)

                if index_aluno != -1:
                    alunos_nas_disciplinas[i] = remover_elemento_do_vetor_por_index(index_aluno, alunos_nas_disciplinas[i])
            i += 1
    
    return nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_nas_disciplinas
#####################################################################################################

def listar_alunos(nome_dos_alunos, cpf_dos_alunos):
    if len(nome_dos_alunos) != 0:    
        resu = str(nome_dos_alunos[0]) + ": " + str(cpf_dos_alunos[0]) + "; "
        i = 1
        while i < len(nome_dos_alunos):
            resu = resu + str(nome_dos_alunos[i]) + ": " + str(cpf_dos_alunos[i]) + "; "
            i += 1
        
        print("Alunos: " + resu)
    else:
        print("Nenhum aluno cadastrado.")

def cadastrar_disciplina(disciplinas, alunos_nas_disciplinas):
    print("Qual o nome dessa disciplina?")
    nome_disci = input()

    index_disci = procurar(nome_disci, disciplinas)

    if index_disci == -1:
        disciplinas.append(nome_disci)
        alunos_nas_disciplinas.append([])
        print("Disciplina cadastrada.")
    else:
        print("Disciplina já cadastrada.")

    return disciplinas, alunos_nas_disciplinas

def editar_disciplina(disciplinas, disciplinas_dos_alunos):
    print("Qual o nome da disciplina?")
    nome_disci = input()

    index_disci = procurar(nome_disci, disciplinas)

    if index_disci == -1:
        print("Disciplina não cadastrada.")
    else:
        print("Qual o novo nome da disciplina?")
        novo_nome_disci = input()

        confirir = procurar(novo_nome_disci, disciplinas)

        if confirir == -1:
            disciplinas[index_disci] = novo_nome_disci
            disciplinas_dos_alunos = editar_nome_disci_para_alunos(nome_disci, novo_nome_disci, disciplinas_dos_alunos)

        else:
            print("Outra disciplina já possuí esse nome.")

    return disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos

def editar_nome_disci_para_alunos(nome_disci, novo_nome_disci, disciplinas_dos_alunos):
    i = 0
    while i < len(disciplinas_dos_alunos):
        aluno = disciplinas_dos_alunos[i]

        acho = False
        j = 0
        while j < len(aluno) and not acho:
            if nome_disci == aluno[j]:
                aluno[j] = novo_nome_disci
                acho = True
            j += 1
        
        disciplinas_dos_alunos[i] = aluno
        i += 1
    
    return disciplinas_dos_alunos

#####################################################################################################
def remover_disciplina(disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos):
    print("Qual o nome da disciplina?")
    nome_disci = input()

    index_disci = procurar(nome_disci, disciplinas)

    if index_disci == -1:
        print("Disciplina não cadastrada.")
    else:
        disciplinas = remover_elemento_do_vetor_por_index(index_disci, disciplinas)
        alunos_nas_disciplinas = remover_elemento_do_vetor_por_index(index_disci, alunos_nas_disciplinas)

        i = 0
        while i < len(disciplinas_dos_alunos):
            disciplinas_alunos = disciplinas_dos_alunos[i]

            if len(disciplinas_alunos) != 0:
                index_disci = procurar(nome_disci, disciplinas_alunos)

                if index_disci != -1:
                    disciplinas_dos_alunos[i] = remover_elemento_do_vetor_por_index(index_disci, disciplinas_dos_alunos[i])
            i += 1

    return disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos
#####################################################################################################

def listar_disciplinas(disciplinas):
    if len(disciplinas) == 0:
        print("Nenhuma disciplina cadastrada.")
    else:
        resu = str(disciplinas[0]) + "; "
        i = 1
        while i < len(disciplinas):
            resu = resu + str(disciplinas[i]) + "; "
            i += 1
        
        print("Disciplinas: " + resu)

def matricular_aluno_na_disci(cpf_dos_alunos, disciplinas_dos_alunos, disciplinas, alunos_nas_disciplinas):
    print("Qual o CPF do aluno?")
    cpf = input()

    index_aluno = procurar(cpf, cpf_dos_alunos)

    if index_aluno == -1:
        print("CPF não cadastrado.")
    else:
        print("Qual o nome da disciplina?")
        nome_disci = input()

        index_disci = procurar(nome_disci, disciplinas)

        if index_disci == -1:
            print("Disciplina não cadastrada.")
        else:
            repetido = procurar(cpf, alunos_nas_disciplinas[index_disci])

            if repetido == -1:
                disciplinas_dos_alunos[index_aluno].append(nome_disci)
                alunos_nas_disciplinas[index_disci].append(cpf)
                print("Aluno " + str(nome_dos_alunos[index_aluno]) + " foi matriculado na disciplina " + str(disciplinas[index_disci]) + ".")
            else:
                print("Esse aluno já foi matriculado nessa matéria.")

def cancelar_matricula_aluno_na_disci(cpf_dos_alunos, disciplinas_dos_alunos, disciplinas, alunos_nas_disciplinas, nome_dos_alunos):
    print("Qual o CPF do aluno?")
    cpf = input()

    index_aluno = procurar(cpf, cpf_dos_alunos)

    if index_aluno == -1:
        print("Aluno não cadastrado.")
    else:
        print("Qual o nome da disciplina?")
        nome_disci = input()

        index_disci = procurar(nome_disci, disciplinas)

        if index_disci == -1:
            print("Disciplina não cadastrada.")
        else:
            disciplinas_dos_alunos[index_aluno] = remover_elemento_do_vetor(nome_disci, disciplinas_dos_alunos[index_aluno])
            alunos_nas_disciplinas[index_disci] = remover_elemento_do_vetor(cpf, alunos_nas_disciplinas[index_disci])
            print("O aluno " + str(nome_dos_alunos[index_aluno]) + " foi desmatriculado da disciplina " + str(nome_disci) + ".")

    return disciplinas_dos_alunos, alunos_nas_disciplinas

def remover_elemento_do_vetor(remove, vetor):
    novo_vetor = []
    i = 0
    while i < len(vetor):
        if vetor[i] != remove:
            novo_vetor.append(vetor[i])
        i += 1
    
    return novo_vetor

def remover_elemento_do_vetor_por_index(index_remove, vetor):
    novo_vetor = []
    i = 0
    while i < len(vetor):
        if i != index_remove:
            novo_vetor.append(vetor[i])
        i += 1
    
    return novo_vetor

def relatorio(nome_dos_alunos, cpf_dos_alunos, disciplinas, alunos_nas_disciplinas):
    if len(disciplinas) == 0:
        print("Nenhuma disciplina cadastrada.")
    else:
        i = 0
        while i < len(disciplinas):
            resu = str(disciplinas[i] + ": ")

            alunos = alunos_nas_disciplinas[i]

            if len(alunos) == 0:
                resu += "Nenhum aluno cadastrado nessa disciplina."
            else:
                j = 0
                while j < len(alunos):
                    cpf = alunos[j]

                    index_aluno = procurar(cpf, cpf_dos_alunos)

                    resu += str(nome_dos_alunos[index_aluno]) + ": " + str(cpf) + "; "
                    j += 1
            
            print(resu)
            i += 1
                
continua = True
while continua:
    escolha = menu()

    if escolha == 1: #Alunos

        repete = True
        while repete:

            escolha_aluno = menu_alunos()

            if escolha_aluno == 1: #Cadastrar
                nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos = cadastrar_aluno(nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos)

            elif escolha_aluno == 2: #Editar
                nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos = editar_aluno(nome_dos_alunos, cpf_dos_alunos)

            elif escolha_aluno == 3: #Remover
                nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_nas_disciplinas = remover_aluno(nome_dos_alunos, cpf_dos_alunos, disciplinas_dos_alunos, alunos_nas_disciplinas)

            elif escolha_aluno == 4: #Listar
                listar_alunos(nome_dos_alunos, cpf_dos_alunos)

            elif escolha_aluno == 5: #Voltar
                repete = False

            else:
                print("Ação inválida.")

    elif escolha == 2: #Disciplinas

        repete = True
        while repete:

            escolha_disciplina = menu_disciplina()

            if escolha_disciplina == 1: #Cadastrar
                disciplinas, alunos_nas_disciplinas = cadastrar_disciplina(disciplinas, alunos_nas_disciplinas)

            elif escolha_disciplina == 2: #Editar
                disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos = editar_disciplina(disciplinas, disciplinas_dos_alunos)

            elif escolha_disciplina == 3: #Remover
                disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos = remover_disciplina(disciplinas, alunos_nas_disciplinas, disciplinas_dos_alunos)

            elif escolha_disciplina == 4: #Listar
                listar_disciplinas(disciplinas)

            elif escolha_disciplina == 5: #Voltar
                repete = False

            else:
                print("Ação inválida.")

    elif escolha == 3: #Matricular

        repeticao = True
        while repeticao:
            print("1 - Matricular.")
            print("2 - Voltar.")

            escolha = int(input())

            if escolha == 1:
                matricular_aluno_na_disci(cpf_dos_alunos, disciplinas_dos_alunos, disciplinas, alunos_nas_disciplinas)
            elif escolha == 2:
                repeticao = False
            else:
                print("Ação inválida.")

    elif escolha == 4: #Cancelar matricula
        repeticao = True
        while repeticao:
            print("1 - Cancelar matricula.")
            print("2 - Voltar.")

            escolha = int(input())

            if escolha == 1:
                disciplinas_dos_alunos, alunos_nas_disciplinas = cancelar_matricula_aluno_na_disci(cpf_dos_alunos, disciplinas_dos_alunos, disciplinas, alunos_nas_disciplinas, nome_dos_alunos)
            elif escolha == 2:
                repeticao = False
            else:
                print("Ação inválida.")
        
    elif escolha == 5: #Relatório
        relatorio(nome_dos_alunos, cpf_dos_alunos, disciplinas, alunos_nas_disciplinas)

    elif escolha == 6: #Sair
        continua = False

    else:
        print("Ação inválida.")



def saida_de_dados_str(entrada):
    if len(entrada) == 0:
        resu = ''
    else:
        resu = str(entrada[0])
        i = 1
        while i < len(entrada):
            resu += ";" + str(entrada[i])
            i += 1
    
    return resu

def saida_de_dados_vetores(entrada):
    if len(entrada) == 0:
        resu = ''
    else:
        primeiro = True
        i = 0
        while i < len(entrada):
            if primeiro == False:
                resu += ";"
            vetor = entrada[i]

            if len(vetor) != 0:
                if primeiro:
                    resu = str(vetor[0])
                    primeiro = False
                else:
                    resu += str(vetor[0])
                j = 1
                while j < len(vetor):
                    resu += "," + str(vetor[j])
                    j += 1
            i += 1

    return resu

arquivo = open("matricula.txt", "w")

arquivo.write(saida_de_dados_str(nome_dos_alunos) + "\n")
arquivo.write(saida_de_dados_str(cpf_dos_alunos) + "\n")
arquivo.write(saida_de_dados_vetores(disciplinas_dos_alunos) + "\n")
arquivo.write(saida_de_dados_str(disciplinas) + "\n")
arquivo.write(saida_de_dados_vetores(alunos_nas_disciplinas) + "\n")

print("Informações salvas.")