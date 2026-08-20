# Trabalho1_IA

## Descrição do Projeto

Este projeto tem como objetivo realizar a coleta, processamento e análise de dados, com o tema de feitiços de D&D, utilizando técnicas de aprendizado de máquina como KNN, Regressão Logística e SVM. O fluxo do projeto inclui desde a coleta de dados até a aplicação de modelos de machine learning para classificação e análise.

## Estrutura do Repositório

- **data/**
  - `feiticos_embeddings.npz`: Arquivo contendo os embeddings gerados.
  - **raw/**
    - `feiticos.csv`: Dados brutos coletados.
    - `feiticos_fixed.csv`: Dados corrigidos.
  - **separated/**
    - `feiticos_train.csv`: Conjunto de treino.
    - `feiticos_val.csv`: Conjunto de validação.
    - `feiticos_test.csv`: Conjunto de teste.
- **src/**
  - `1-scraper.py`: Script para coleta de dados dos feitiços.
  - `2-corrigir_csv.py`: Script para corrigir inconsistências nos dados brutos.
  - `3-separar_dataset.py`: Script para dividir os dados em conjuntos de treino, validação e teste.
  - `4-embedding.py`: Script para gerar embeddings dos dados.
  - `5-KNN.py`: Implementação do modelo KNN.
  - `6-Logistic_Regression.py`: Implementação do modelo de Regressão Logística.
  - `7-SVM.py`: Implementação do modelo SVM.
  - `base.py`: Possuí os códigos bases para todos os modelos, carregamento de dados e realização das previsões.
- `requirements.txt`: Lista de dependências do projeto.
- `setup.py`: Script para configuração do ambiente e instalação de dependências.

## Pré-requisitos

- Python 3.8 ou superior
- Ambiente virtual configurado

## Configuração do Ambiente

1. Crie e ative um ambiente virtual:

   ```powershell
   python setup.py
   .\.venv\Scripts\Activate.ps1
   ```

## Uso

1. **Coleta de Dados:**

   Execute o script `1-scraper.py` para coletar os dados de feitiços:

   ```powershell
   python .\src\1-scraper.py
   ```

2. **Correção de Dados:**

   Corrija os dados brutos com o script `2-corrigir_csv.py`:

   ```powershell
   python .\src\2-corrigir_csv.py
   ```

3. **Separação do Dataset:**

   Divida os dados em conjuntos de treino, validação e teste:

   ```powershell
   python .\src\3-separar_dataset.py
   ```

4. **Geração de Embeddings:**

   Gere os embeddings com o script `4-embedding.py`:

   ```powershell
   python .\src\4-embedding.py
   ```

5. **Treinamento e Avaliação de Modelos:**

   - KNN:

     ```powershell
     python .\src\5-KNN.py
     ```

   - Regressão Logística:

     ```powershell
     python .\src\6-Logistic_Regression.py
     ```

   - SVM:

     ```powershell
     python .\src\7-SVM.py
     ```
