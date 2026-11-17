# Trabalho Prático – Autoencoder Variacional (VAE) e Visualização de Dados

| | |
|---|---|
| **Modalidade** | Individual ou em dupla |
| **Valor** | 10,0 pontos |

---

## 1. Objetivo

O objetivo deste trabalho é explorar o uso de Autoencoders Variacionais (*Variational Autoencoders* – VAE) para aprendizagem de representações latentes e visualização de dados de alta dimensionalidade.

Os alunos deverão implementar e treinar um VAE utilizando o conjunto de dados empregado na Prova 1, comparando as representações obtidas com os métodos de redução de dimensionalidade **PCA**, **t-SNE** e **UMAP**.

A atividade busca investigar como diferentes técnicas organizam os dados em espaços de baixa dimensionalidade, permitindo identificar possíveis agrupamentos, padrões de similaridade e separações entre classes ou categorias.

---

## 2. Conjunto de dados

Deverá ser utilizado o conjunto de dados construído e explorado na Prova 1, considerando os seguintes requisitos:

- O conjunto de dados deverá conter **no mínimo 1.000 instâncias**.
- Os dados deverão corresponder às representações vetoriais (*features* ou *embeddings*) previamente extraídas por modelos de aprendizagem profunda, a partir de imagens, textos ou outras modalidades.
- Caso o conjunto utilizado na Prova 1 possua menos de 1.000 instâncias, os alunos deverão ampliá-lo para atender ao requisito mínimo.
- É permitido realizar ajustes no pré-processamento, como normalização ou padronização, desde que sejam descritos e justificados.

---

## 3. Etapas do trabalho

### Etapa 1 – Implementação e treinamento do VAE

Implementar um Autoencoder Variacional utilizando PyTorch, TensorFlow/Keras ou outra biblioteca equivalente.

O modelo deverá conter:

- **Encoder:** rede neural responsável por mapear os dados de entrada para os parâmetros de uma distribuição latente.
- **Espaço latente:** representação probabilística caracterizada pelos vetores de média (μ) e variância (σ²).
- **Reparametrização:** implementação do mecanismo de amostragem diferenciável.
- **Decoder:** rede neural responsável pela reconstrução dos dados a partir das representações latentes.
- **Função de perda:** combinação do erro de reconstrução e da divergência de Kullback-Leibler (KL).

Os alunos deverão definir e justificar as principais escolhas de arquitetura e treinamento, incluindo:

- dimensionalidade do espaço latente;
- número de camadas;
- funções de ativação;
- otimizador;
- taxa de aprendizagem;
- número de épocas.

> **Requisito:** utilizar um espaço latente bidimensional (3D) para permitir a visualização direta das representações aprendidas pelo VAE.

Apresentar também a evolução das perdas de **reconstrução**, **KL** e **perda total** durante o treinamento.

---

### Etapa 2 – Redução de dimensionalidade

Aplicar os seguintes métodos ao conjunto de *features* original:

1. PCA (*Principal Component Analysis*)
2. t-SNE (*t-distributed Stochastic Neighbor Embedding*)
3. UMAP (*Uniform Manifold Approximation and Projection*)
4. VAE (*Variational Autoencoder*)

Todos os métodos deverão produzir representações **bidimensionais** para visualização.

Para o VAE, utilizar os vetores de médias (μ) produzidos pelo encoder como representação determinística dos dados no espaço latente.

---

### Etapa 3 – Visualização e análise comparativa

Construir gráficos de dispersão (*scatter plots*) para os quatro métodos, utilizando, sempre que disponíveis, cores para identificar as classes ou categorias dos dados.

Os gráficos deverão permitir observar a distribuição das amostras e a possível formação de grupos no espaço bidimensional.

A análise deverá abordar as seguintes questões:

1. Os métodos produziram agrupamentos visualmente identificáveis?
2. Quando existem rótulos, as amostras da mesma classe ficaram próximas? Houve separação entre classes distintas?
3. Quais diferenças podem ser observadas entre as representações produzidas por PCA, t-SNE, UMAP e VAE?
4. O VAE conseguiu aprender uma representação latente organizada? Como ela se compara às demais técnicas?
5. Quais características dos métodos podem explicar as diferenças observadas?

> **Importante:** a formação de grupos visualmente separados não significa necessariamente que um método produziu uma representação superior. Os alunos deverão considerar também a preservação de relações de proximidade entre as amostras e as limitações de interpretação de cada técnica.

---

### Etapa 4 – Avaliação quantitativa

Além da análise visual, realizar pelo a avaliação quantitativa das representações bidimensionais.

- **Silhouette Score:** avaliar a separação e a coesão dos grupos, quando houver uma partição definida.

Os resultados deverão ser apresentados em uma **tabela comparativa** e discutidos.

É necessário utilizar **condições equivalentes de avaliação** para os quatro métodos, justificando a escolha das métricas.

---

## 4. Entregáveis

Cada aluno ou dupla deverá submeter os seguintes materiais:

### 4.1 Código-fonte

Notebook Jupyter/Google Colab contendo:

- Carregamento e pré-processamento dos dados.
- Implementação e treinamento do VAE.
- Aplicação dos métodos PCA, t-SNE e UMAP.
- Visualizações e métricas de avaliação.
- Análises e conclusões dos resultados.

O código deverá estar organizado, documentado e permitir a reprodução dos experimentos.

### 4.2 Modelo treinado

Arquivo contendo os pesos do VAE treinado (`.pth`, `.pt`, `.keras` ou equivalente), acompanhado das informações necessárias para reconstruir a arquitetura e carregar o modelo.

### 4.3 Vídeo de apresentação

Gravar um vídeo de **até 20 minutos**, apresentando:

- O conjunto de dados utilizado, incluindo quantidade de instâncias e dimensionalidade das *features*.
- A arquitetura e as configurações de treinamento do VAE.
- O comportamento das funções de perda.
- Convergência e estabilidade do treinamento.
- Os gráficos comparativos dos quatro métodos.
- A avaliação quantitativa.
- Uma discussão crítica dos resultados e as principais conclusões.

Em trabalhos realizados em dupla, ambos os integrantes deverão participar da apresentação.

O vídeo poderá ser disponibilizado por meio de um link acessível ao professor.

---

## 5. Critérios de avaliação

| Critério | Pontuação |
|---|:---:|
| Implementação correta e treinamento do VAE | 3,0 |
| Aplicação dos métodos PCA, t-SNE e UMAP | 1,5 |
| Visualizações e análise comparativa | 2,0 |
| Avaliação quantitativa e interpretação dos resultados | 1,5 |
| Organização, reprodutibilidade e entrega do código e modelo | 1,0 |
| Clareza e qualidade da apresentação em vídeo | 1,0 |
| **Total** | **10,0** |

---

## 6. Orientações gerais

- O trabalho poderá ser desenvolvido individualmente ou em dupla.
- O conjunto de dados deverá conter pelo menos 1.000 instâncias.
- Os alunos poderão utilizar bibliotecas existentes para implementar o VAE, mas deverão compreender e explicar sua arquitetura, treinamento e função de perda.
- As configurações dos métodos e as sementes aleatórias utilizadas deverão ser registradas.
- Todos os gráficos deverão conter títulos, identificação dos eixos e legendas quando aplicáveis.
- O vídeo de apresentação deverá respeitar o limite máximo de 20 minutos.
- A avaliação priorizará a correção metodológica, a capacidade de análise crítica e a interpretação dos resultados, e não apenas a obtenção de agrupamentos visualmente bem separados.
- Resultados negativos ou inesperados também são válidos, desde que analisados e discutidos adequadamente.
