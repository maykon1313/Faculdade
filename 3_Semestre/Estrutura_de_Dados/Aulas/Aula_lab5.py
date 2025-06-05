import re
import requests
from bs4 import BeautifulSoup

url = 'https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/dfs.html'
resposta = requests.get(url)
soup = BeautifulSoup(resposta.text, 'html.parser')

texto = soup.get_text()

frases = re.split(r'(?<=[.!?])\s+', texto)
padrao = r'\bvértice\b.*?\bcinza\b'

resultado = []
for frase in frases:
    if re.search(padrao, frase, re.IGNORECASE):
        frase = re.sub("\n", " ", frase)
        resultado.append(frase)

for frase in resultado:
    print(frase)
    print()

#######

import re

nomes = open('nomes.txt','r').read()

nomes = re.split(r'\n', nomes)

padrao = r'\bKaio\b.*?\bAlmeida\b|\bAlmeida\b.*?\bKaio\b'

nomes = [nome for nome in nomes if re.search(padrao, nome)]

for nome in nomes:
    print(nome)

########

import re

medicamentos = open('medicamentos.txt','r').read()

padrao = r'\b(\w*mina)\s*\(([^()]+)\)'

medicamentos = re.findall(padrao, medicamentos)

for nome, formula in medicamentos:
    print("Nome: ", nome)
    print("Fórmula: ", formula)
    print()
