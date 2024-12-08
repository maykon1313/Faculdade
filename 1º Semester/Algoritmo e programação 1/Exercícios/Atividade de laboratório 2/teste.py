arquivo = open("Faculdade.txt", "r")

alunos = arquivo.readline().strip().split()
aluno_cpf = arquivo.readline().strip().split()
disciplinas_alunos = arquivo.readline().strip().split()
disciplinas = arquivo.readline().strip().split()
alunos_disciplina = arquivo.readline().strip().split()

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

arquivo = open("Faculdade.txt", "w")

disciplinas_alunos = tranformadestrparacou(disciplinas_alunos)

disciplinas_alunos[0].append("AMA")

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