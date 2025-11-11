# Classificação de Notícias com BERT

## 🎯 Objetivo

Treinar um modelo BERT para classificar comentários de notícias (ou vídeos) em categorias de sentimento (positivo, negativo ou neutro), 
utilizando o token [CLS] como representação do texto.📂 Base de Dados

Use a planilha disponível em: <https://docs.google.com/spreadsheets/d/17aHYyRNfbmde8bVOR_HX_BmNUEdkygPuaGO4lJj26jg/edit?usp=sharing>

A planilha contém textos curtos (coluna comment_text) e rótulos (como positivo, negativo, neutro).
Você deverá escolher três classes entre: onça, caseiro, fake news, ironia e notícia.
Todos os experimentos deverão ser realizados em relação a essas três classes.

### 1. Preparação dos Dados

Ler o CSV com pandas;
Remover textos vazios ou duplicados;
Converter os rótulos para números (positivo→2, neutro→1, negativo→0);
Dividir os dados em treino (70%), validação (15%) e teste (15%).

### 2. Tokenização

Usar o tokenizer do modelo pré-treinado bert-base-uncased (ou neuralmind/bert-base-portuguese-cased para português);
Gerar tensores de input_ids e attention_mask.

### 3. Modelo

Configurar o número de classes conforme os rótulos (ex.: 3).
Adaptar o modelo para obter o token [CLS] que será utilizado para o treinamento do modelo.

### 4. Treinamento

Usar AdamW com lr=2e-5 e epochs=10;
Mostrar o loss e a acurácia de treino e de validação por época.
Após a última época, mostrar o gráfico de evolução do loss do treino e da validação.

### 5. Avaliação

Avaliar no conjunto de teste;
Utilizando o classification score do sklearn, mostrar os
valores de precision, recall e F1 para cada classe;
Mostrar exemplos de erros (textos que o modelo classificou errado).

### 6. Entregáveis

Link para github de todos os códigos
Vídeo no youtube de cinco minutos com explicação do código e mostrando a execução da classificação de textos de pelo menos três textos.

## Implementação

(ERRADO): Classificação multilabel, onde para cada categoria existe uma classificação de sentimento.
O resultado esperado do modelo é um conjunto de três rótulos (um para cada categoria), por comentário.

(CERTO): Para cada categoria treinar um modelo nas três classificações.
Usar cada modelo para sua respectiva categoria e fazer a avaliação final no teste.

Categorias escolhidas: onça, caseiro e notícia.

### Pastas necessárias

```bash
requirements.txt
README.md
0-trained_models_multilabel/
└── ...
data/
├── dataset/
│   ├── test.csv
│   ├── train.csv
│   └── valid.csv
├── dataset_token/
│   ├── test_tokenized.csv
│   ├── train_tokenized.csv
│   └── valid_tokenized.csv
├── interim/
│   └── dataset.csv
├── new/
│   └── avaliacao.txt
└── raw/
    └── oncas_comentarios.csv # (Baixado da planilha do Google Spread Sheets)
env/
src/
├── 0-ler_e_corrigir_csv.py
├── 1-separar_dataset.py
├── 2-tokenizacao.py
├── 3-treinar.py
└── 4-avaliar.py
trained_models/
├── avaliacao.txt
├── 1-model/
│   └── ...
├── 2-model/
│   └── ...
└── 3-model/
│   └── ...
```

### Configurar enviroment

```python
python -m venv env
env/Scripts/Activate.ps1
python.exe -m pip install --upgrade pip
pip install -r requirements.txt
```

### Corrigir dataset

```python
python .src/0-ler_e_corrigir_csv.py
```

### Separar dataset

```python
python .src/1-separar_dataset.py
```

### Tokenizar

```python
python .src/2-tokenizacao.py
```

### Treinar modelo

```python
python .src/3-treinar.py
```

### Avaliar modelo

```python
python .src/4-avaliar.py
```

### Resultados

O resultado da avaliação ficam salvos no arquivo avaliacao.txt dentro da pasta trained_models.
