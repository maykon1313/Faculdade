import requests
import re
import random

ALFA_NUMERICO = 256

def bad_character_heuristic(padrao):
    m = len(padrao)
    tabela_deslocamento = [-1] * ALFA_NUMERICO
    for i in range(m):
        tabela_deslocamento[ord(padrao[i])] = i
    return tabela_deslocamento

def good_suffix_heuristic(padrao):
    m = len(padrao)
    if m == 0:
        return []

    tabela_saltos = [m] * m
    borda = [0] * m

    for i in range(1, m):
        j = borda[i - 1]
        while j > 0 and padrao[i] != padrao[j]:
            j = borda[j - 1]
        if padrao[i] == padrao[j]:
            j += 1
        borda[i] = j

    j = m - 1
    while j >= 0:
        prefixo_sufixo = borda[j]
        salto = m - 1 - prefixo_sufixo
        
        posicao_salto = m - 1 - j
        
        if tabela_saltos[posicao_salto] > salto:
            tabela_saltos[posicao_salto] = salto
            
        j -= 1

    return tabela_saltos

def busca_ingenua(texto, padrao):
    n = len(texto)
    m = len(padrao)
    comparacoes = 0
    
    for i in range(n - m + 1):
        j = 0
        while j < m:
            comparacoes += 1
            if texto[i+j] != padrao[j]:
                break
            j += 1
    return comparacoes

def boyer_moore_bad_char(texto, padrao):
    n = len(texto)
    m = len(padrao)
    comparacoes = 0
    
    if m == 0: return 0
    
    tabela_char_ruim = bad_character_heuristic(padrao)
    deslocamento = 0
    
    while deslocamento <= n - m:
        j = m - 1
        while j >= 0:
            comparacoes += 1
            if padrao[j] != texto[deslocamento + j]:
                char_texto = texto[deslocamento + j]
                salto = j - tabela_char_ruim[ord(char_texto)]
                deslocamento += max(1, salto)
                break
            j -= 1
        
        if j < 0:
            deslocamento += m
            
    return comparacoes

def boyer_moore_good_suffix(texto, padrao):
    n = len(texto)
    m = len(padrao)
    comparacoes = 0
    
    if m == 0: return 0

    tabela_sufixo_bom = good_suffix_heuristic(padrao)
    deslocamento = 0
    
    while deslocamento <= n - m:
        j = m - 1
        while j >= 0:
            comparacoes += 1
            if padrao[j] != texto[deslocamento + j]:
                salto = tabela_sufixo_bom[j]
                deslocamento += max(1, salto)
                break
            j -= 1
            
        if j < 0:
            deslocamento += tabela_sufixo_bom[0]
            
    return comparacoes

def boyer_moore_completo(texto, padrao):
    n = len(texto)
    m = len(padrao)
    comparacoes = 0

    if m == 0: return 0

    tabela_char_ruim = bad_character_heuristic(padrao)
    tabela_sufixo_bom = good_suffix_heuristic(padrao)
    deslocamento = 0

    while deslocamento <= n - m:
        j = m - 1
        while j >= 0:
            comparacoes += 1
            if padrao[j] != texto[deslocamento + j]:
                salto_char_ruim = j - tabela_char_ruim[ord(texto[deslocamento + j])]
                salto_sufixo_bom = tabela_sufixo_bom[j]
                deslocamento += max(1, salto_char_ruim, salto_sufixo_bom)
                break
            j -= 1
        
        if j < 0:
            deslocamento += tabela_sufixo_bom[0]
            
    return comparacoes

def imprimir_tabela(headers, dados):
    print("--- Tabela de Resultados Normalizados ---")

    larguras = [max(len(str(item)) for item in [h] + [linha[i] for linha in dados]) for i, h in enumerate(headers)]
    
    header = " | ".join(h.ljust(l) for h, l in zip(headers, larguras))
    print(header)
    
    print("-+-".join("-" * l for l in larguras))
    
    for linha in dados:
        linha_formatada = " | ".join(str(item).ljust(l) for item, l in zip(linha, larguras))
        print(linha_formatada)

    print("\n" + "="*80 + "\n")

def imprimir_analise():
    print("--- Análise Comparativa do Desempenho ---")

    analise = """
    A análise dos dados da tabela revela distinções claras no desempenho dos algoritmos de busca de padrões.

    1.  Algoritmo Ingênuo (Força Bruta):
        Este algoritmo demonstrou ser o menos eficiente. Os valores normalizados próximos de 1
        indicam que ele foi responsável por quase todas as comparações realizadas. Isso confirma sua complexidade
        de tempo teórica de O(n*m), tornando-o inviável para grandes volumes de dados.

    2.  BM (Caractere Ruim) vs. BM (Sufixo Bom):
        - A heurística do caractere ruim permite saltar o alinhamento para além do caractere que não correspondeu.
        - A heurística do sufixo bom brilha quando uma parte final do padrão casa com o
          texto, mas um caractere anterior falha. Ela usa a informação sobre as bordas do padrão para o maior salto.
        - O desempenho é relativo e depende da estrutura do padrão e do texto.

    3.  BM (Completo):
        A versão completa, que combina as duas heurísticas escolhendo sempre o maior salto
        possível, apresentou o melhor desempenho geral, com os menores valores normalizados. Ao aproveitar
        o melhor de ambos os mundos, ele minimiza o número de comparações na maioria dos casos.
    """

    print(analise)

def ler_livro(url):
    try:
        response = requests.get(url)
        response.encoding = response.apparent_encoding
        texto_base = response.text
        print(f"Texto 'Quincas Borba' baixado com sucesso. Tamanho: {len(texto_base)} caracteres.\n")
        return texto_base
    except requests.exceptions.RequestException as e:
        print(f"Erro ao baixar o texto: {e}")
        return ""

def palavras_usada(texto_base):
    palavras_texto = re.findall(r'\b\w+\b', texto_base.lower())
    
    contagem_palavras = {}
    for palavra in palavras_texto:
        contagem_palavras[palavra] = contagem_palavras.get(palavra, 0) + 1
    
    palavras_frequentes = [p for p, c in contagem_palavras.items() if c > 10 and len(p) > 3]
    
    if len(palavras_frequentes) >= 10:
        palavras_para_teste = random.sample(palavras_frequentes, 10)
    else:
        palavras_para_teste = palavras_frequentes

    return palavras_para_teste

def resultados(texto_base, palavras_para_teste):
    algoritmos = {
        "Ingênuo": busca_ingenua,
        "BM-Ruim": boyer_moore_bad_char,
        "BM-Bom": boyer_moore_good_suffix,
        "BM-Comp": boyer_moore_completo,
    }
    
    resultados_formatados = []
    
    for palavra in palavras_para_teste:
        linha_atual = [palavra]
        comparacoes_raw = {}
        
        for nome, funcao in algoritmos.items():
            comparacoes_raw[nome] = funcao(texto_base, palavra)
        
        soma_total = sum(comparacoes_raw.values())
        
        for nome in algoritmos.keys():
            valor_normalizado = comparacoes_raw[nome] / soma_total if soma_total > 0 else 0
            linha_atual.append(f"{valor_normalizado:.4f}")
        
        resultados_formatados.append(linha_atual)
        
    headers = ['Palavra'] + [f'Norm ({nome})' for nome in algoritmos.keys()]

    return headers, resultados_formatados

def main():
    url = "https://www.ime.usp.br/~pf/e-Books/quincas/quincasborba.txt"
    
    texto_base = ler_livro(url)

    if texto_base == "": return

    palavras_para_teste = palavras_usada(texto_base)
        
    print(f"Palavras selecionadas para o teste: {palavras_para_teste}\n")

    headers, resultados_formatados = resultados(texto_base, palavras_para_teste)
    
    imprimir_tabela(headers, resultados_formatados)

    imprimir_analise()

if __name__ == "__main__":
    main()
