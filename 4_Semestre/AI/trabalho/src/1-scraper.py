import requests
from bs4 import BeautifulSoup
import time
import os
import csv

existing_spells = set()
start_page = 1
file_exists = os.path.exists("data/raw/feiticos.csv")

if file_exists:
    print("Arquivo existente encontrado. Carregando dados já coletados...")
    with open("data/raw/feiticos.csv", "r", encoding="utf-8") as existing_file:
        csv_reader = csv.reader(existing_file)
        next(csv_reader, None)
        for row in csv_reader:
            if row:
                existing_spells.add(row[0])
    print(f"Encontrados {len(existing_spells)} feitiços já coletados.")

if file_exists:
    f = open("data/raw/feiticos.csv", "a", encoding="utf-8", newline="")
else:
    f = open("data/raw/feiticos.csv", "w", encoding="utf-8", newline="")
    f.write("nome,escola,descricao\n")

def get_spell_info(spell_slug):
    url = f"https://www.dndbeyond.com/spells/{spell_slug}"

    try:
        page = requests.get(url)

        if page.status_code == 200:
            soup = BeautifulSoup(page.content, 'html.parser')
            
            description = ""
            bonus_text = ""
            
            desc_selectors = [
                'div.more-info-content p',
                'div.spell-description p', 
                'div.description p',
                '.ddb-statblock-item-description p',
                '.spell-content p'
            ]
            
            for selector in desc_selectors:
                paragraphs = soup.select(selector)

                if paragraphs:
                    description = paragraphs[0].get_text(strip=True)

                    if len(paragraphs) > 1:
                        bonus_text = paragraphs[1].get_text(strip=True)

                    break
            
            return description, bonus_text
    except:
        pass
    
    return "", ""

i = 1
while (i <= 46):
    URL = "https://www.dndbeyond.com/spells?page=" + str(i)
    page = requests.get(URL)
    soup = BeautifulSoup(page.content, 'html.parser')

    spells = soup.find_all('div', class_='info', attrs={'data-type': 'spells'})

    for spell in spells:
        # Nome do feitiço
        spell_name = spell.get('data-slug', '') 
        
        if spell_name in existing_spells:
            print(f"Pulando {spell_name} (já coletado)")
            continue
        
        # Escola do feitiço
        school_element = spell.find('div', class_='school') 
        spell_school = ''

        if school_element and hasattr(school_element, 'get'):
            classes = school_element.get('class', []) 

            for cls in classes: 
                if cls != 'school':
                    spell_school = cls
                    break
        
        # Buscar descrição na página individual
        description, bonus_text = get_spell_info(spell_name)
        
        # Resultado
        f.write(f'"{spell_name}","{spell_school}","{description} {bonus_text}"\n')
        f.flush()
        print(f"Coletado: {spell_name}")
        
        # Pausa para não sobrecarregar o servidor
        time.sleep(0.5)
    
    print(f"Página {i} concluída")
    i += 1

f.close()