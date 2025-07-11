def algoritmo_ingenuo(texto, padrao):
    """
    Implementa o algoritmo ingênuo para encontrar todas as ocorrências de um padrão em um texto.
    Retorna uma lista com as posições das ocorrências.
    """
    n = len(texto)
    m = len(padrao)
    posicoes = []

    if m == 0:
        return []

    # Itera sobre o texto para encontrar o padrão
    for i in range(n - m + 1):
        j = 0
        # Compara o padrão com a subseção atual do texto
        while j < m and texto[i + j] == padrao[j]:
            j += 1

        # Se todo o padrão foi encontrado
        if j == m:
            posicoes.append(i)
    
    return posicoes

def kmp(texto, padrao):
    """
    Implementa o algoritmo Knuth-Morris-Pratt (KMP) para busca de padrão.
    Utiliza uma tabela LPS (Longest Proper Prefix which is also Suffix).
    Retorna uma lista com as posições das ocorrências.
    """
    n = len(texto)
    m = len(padrao)

    if m == 0:
        return []

    # Função auxiliar para calcular a tabela LPS
    def _computar_lps(padrao_kmp):
        lps = [0] * m
        comprimento = 0
        i = 1
        while i < m:
            if padrao_kmp[i] == padrao_kmp[comprimento]:
                comprimento += 1
                lps[i] = comprimento
                i += 1
            else:
                if comprimento != 0:
                    comprimento = lps[comprimento - 1]
                else:
                    lps[i] = 0
                    i += 1
        return lps

    lps = _computar_lps(padrao)
    posicoes = []
    i = 0  # ponteiro para o texto
    j = 0  # ponteiro para o padrão

    while i < n:
        if padrao[j] == texto[i]:
            i += 1
            j += 1

        if j == m:
            posicoes.append(i - j)
            j = lps[j - 1]
        elif i < n and padrao[j] != texto[i]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    
    return posicoes

def boyer_moore(texto, padrao):
    """
    Implementa o algoritmo Boyer-Moore para busca de padrão.
    Utiliza as heurísticas do caractere ruim e do sufixo bom.
    Retorna uma lista com as posições das ocorrências.
    """
    n = len(texto)
    m = len(padrao)
    posicoes = []

    if m == 0:
        return []

    # 1. Heurística do Caractere Ruim
    def _precomputar_caractere_ruim(padrao):
        tabela = {}

        for i in range(len(padrao)):
            tabela[padrao[i]] = i

        return tabela

    # 2. Heurística do Sufixo Bom (Implementação Corrigida)
    def _precomputar_sufixo_bom(padrao):
        len_padrao = len(padrao)
        shift = [0] * (len_padrao + 1)
        border_array = [0] * (len_padrao + 1) # border_array[i] = posição inicial do maior sufixo de padrao[i:] que é também um prefixo de padrao

        i = len_padrao
        j = len_padrao + 1
        border_array[i] = j

        while i > 0:
            while j <= len_padrao and padrao[i - 1] != padrao[j - 1]:
                if shift[j] == 0:
                    shift[j] = j - i
                j = border_array[j]

            i -= 1
            j -= 1

            border_array[i] = j
        
        j = border_array[0]
        for i in range(len_padrao + 1):
            if shift[i] == 0:
                shift[i] = j

            if i == j:
                j = border_array[j]

        return shift

    tabela_char_ruim = _precomputar_caractere_ruim(padrao)
    tabela_sufixo_bom = _precomputar_sufixo_bom(padrao)
    
    shift = 0  # Deslocamento do padrão no texto
    while shift <= n - m:
        j = m - 1
        while j >= 0 and padrao[j] == texto[shift + j]:
            j -= 1

        if j < 0:
            posicoes.append(shift)
            shift += tabela_sufixo_bom[0]
        else:
            char_ruim = texto[shift + j]
            shift_char_ruim = j - tabela_char_ruim.get(char_ruim, -1)
            shift_sufixo_bom = tabela_sufixo_bom[j + 1]
            shift += max(shift_char_ruim, shift_sufixo_bom)
            
    return posicoes

def main():
    ## --- Bloco de Execução ---

    texto_principal = "ababacabacdabdaabacababaeabcababadebaababaca"
    padrao_busca = "ababac"

    # Executa e imprime os resultados de cada algoritmo
    print(f"Texto:  {texto_principal}")
    print(f"Padrão: {padrao_busca}\n")

    pos_ingenuo = algoritmo_ingenuo(texto_principal, padrao_busca)
    print(f"Algoritmo Ingênuo encontrou {len(pos_ingenuo)} ocorrência(s):")
    print(pos_ingenuo)
    print("-" * 30)

    pos_kmp = kmp(texto_principal, padrao_busca)
    print(f"Algoritmo KMP encontrou {len(pos_kmp)} ocorrência(s):")
    print(pos_kmp)
    print("-" * 30)

    pos_bm = boyer_moore(texto_principal, padrao_busca)
    print(f"Algoritmo Boyer-Moore encontrou {len(pos_bm)} ocorrência(s):")
    print(pos_bm)
    print("-" * 30)

if __name__ == '__main__':
    main()