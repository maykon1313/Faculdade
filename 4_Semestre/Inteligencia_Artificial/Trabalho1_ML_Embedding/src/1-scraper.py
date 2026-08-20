import requests
from bs4 import BeautifulSoup
import time
import os
import csv

# Constantes
DATA_PATH = "data/raw/feiticos.csv"
BASE_URL = "https://www.dndbeyond.com/spells"
PAGE_URL = f"{BASE_URL}?page="
DESC_SELECTORS = [
    'div.more-info-content p',
    'div.spell-description p', 
    'div.description p',
    '.ddb-statblock-item-description p',
    '.spell-content p'
]

def carregar_feiticos_existentes(filepath):
    """Carrega os feitiços já coletados de um arquivo CSV."""
    if not os.path.exists(filepath):
        return set()

    print("Arquivo existente encontrado. Carregando dados já coletados...")
    existing_spells = set()

    with open(filepath, "r", encoding="utf-8") as existing_file:
        csv_reader = csv.reader(existing_file)
        next(csv_reader, None)  # Pular cabeçalho

        for row in csv_reader:
            if row:
                existing_spells.add(row[0])

    print(f"Encontrados {len(existing_spells)} feitiços já coletados.")
    return existing_spells

def inicializar_arquivo(filepath):
    """Inicializa o arquivo CSV para escrita."""
    if os.path.exists(filepath):
        return open(filepath, "a", encoding="utf-8", newline="")

    f = open(filepath, "w", encoding="utf-8", newline="")
    f.write("nome,escola,descricao\n")
    return f

def get_spell_info(spell_slug):
    """Obtém a descrição de um feitiço a partir de sua página individual."""
    url = f"{BASE_URL}/{spell_slug}"
    try:
        page = requests.get(url)
        if page.status_code == 200:
            soup = BeautifulSoup(page.content, 'html.parser')
            for selector in DESC_SELECTORS:
                paragraphs = soup.select(selector)
                if paragraphs:
                    description = paragraphs[0].get_text(strip=True)
                    bonus_text = paragraphs[1].get_text(strip=True) if len(paragraphs) > 1 else ""
                    return description, bonus_text
    except requests.RequestException as e:
        print(f"Erro ao buscar descrição para {spell_slug}: {e}")
    return "", ""

def processar_pagina(pagina, existing_spells, file):
    """Processa uma página de feitiços e salva os dados no arquivo."""
    url = f"{PAGE_URL}{pagina}"
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    spells = soup.find_all('div', class_='info', attrs={'data-type': 'spells'})

    for spell in spells:
        spell_name = spell.get('data-slug', '')

        if spell_name in existing_spells:
            print(f"Pulando {spell_name} (já coletado)")
            continue

        school_element = spell.find('div', class_='school')
        spell_school = ''

        if school_element and hasattr(school_element, 'get'):
            classes = school_element.get('class')
            if classes and isinstance(classes, list):
                spell_school = next((cls for cls in classes if cls != 'school'), '')

        description, bonus_text = get_spell_info(spell_name)
        file.write(f'"{spell_name}","{spell_school}","{description} {bonus_text}"\n')
        file.flush()

        print(f"Coletado: {spell_name}")
        time.sleep(0.1)

def scraper():
    """Função principal para executar o scraper."""
    existing_spells = carregar_feiticos_existentes(DATA_PATH)
    with inicializar_arquivo(DATA_PATH) as file:
        for i in range(1, 47):
            print(f"Processando página {i}...")
            processar_pagina(i, existing_spells, file)
            print(f"Página {i} concluída")

if __name__ == "__main__":
    scraper()