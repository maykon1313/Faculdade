# Instale os pacotes se necessário (somente uma vez)
install.packages("readxl")
install.packages("ggplot2")
install.packages("dplyr")

# Carregar os pacotes necessários
library(readxl)  # Para leitura de arquivos Excel
library(ggplot2)  # Para visualizações gráficas
library(dplyr)  # Para manipulação de dados

# Defina o diretório onde seus arquivos estão localizados (altere conforme seu caminho)
setwd("C:/Users/maykon.kazuhiro/Documents/6 - Probabilidade e Estatística")  # Atualize para o seu diretório

# Carregar os dados do arquivo Excel (substitua pelo nome do seu arquivo)
dados_ <- read_excel("Preco_Citros.xlsx")

# Verifique a estrutura dos dados (tipos de variáveis, primeiros elementos, etc.)
str(dados_)

# Reescrevendo a estrutura dos dados para garantir que as variáveis estejam no tipo correto
dados <- transform(dados_,
                   Ano = as.factor(Ano),  # Ano como variável categórica
                   Estado = as.factor(Estado),
                   Tipo_de_Citros = as.factor(Tipo_de_Citros),
                   Tipo_de_Processamento = as.factor(Tipo_de_Processamento),
                   Preco = as.numeric(Preco))  # Preço como variável numérica

# ## Tabela de Distribuição de Frequência

# Para criar a tabela de distribuição de frequência de uma variável categórica, utilizaremos:
# - Frequência Absoluta
# - Frequência Relativa
# - Frequência Acumulada
# - Porcentagem

# Criando a tabela de frequência para a variável 'Tipo_de_Citros'
freq_absoluta <- table(dados$Tipo_de_Citros)
freq_relativa <- as.numeric(prop.table(freq_absoluta))  # Proporção dos valores
freq_acumulada <- as.numeric(cumsum(freq_absoluta))  # Frequência acumulada
porcentagem <- as.numeric(freq_relativa * 100)  # Porcentagem

# Combinando tudo em um data frame para visualização
tabela_freq <- data.frame(
  Categoria = names(freq_absoluta),
  Frequencia_Absoluta = as.vector(freq_absoluta),
  Frequencia_Relativa = round(freq_relativa, 4),
  Frequencia_Acumulada = freq_acumulada,
  Porcentagem = round(porcentagem, 2)
)

# Exibindo a tabela de frequência
print(tabela_freq)

# #### Atividade 1: Criar a tabela de distribuição de frequência para outras variáveis categóricas
# Para as demais variáveis categóricas (Estado, Tipo_de_Processamento), repita o processo acima.
# Exemplo:
# Criando a tabela de frequência para a variável 'Estado'
freq_estado <- table(dados$Estado)
freq_relativa_estado <- as.numeric(prop.table(freq_estado))
freq_acumulada_estado <- as.numeric(cumsum(freq_estado))
porcentagem_estado <- as.numeric(freq_relativa_estado * 100)

tabela_freq_estado <- data.frame(
  Categoria = names(freq_estado),
  Frequencia_Absoluta = as.vector(freq_estado),
  Frequencia_Relativa = round(freq_relativa_estado, 4),
  Frequencia_Acumulada = freq_acumulada_estado,
  Porcentagem = round(porcentagem_estado, 2)
)

# Exibindo a tabela de frequência para 'Estado'
print(tabela_freq_estado)

# #### Interpretação das tabelas de frequência:
# Com as tabelas de frequência, podemos tirar algumas conclusões:
# - A 'Frequência Absoluta' nos mostra quantas vezes cada categoria aparece.
# - A 'Frequência Relativa' mostra a proporção de cada categoria no conjunto de dados.
# - A 'Frequência Acumulada' ajuda a entender a distribuição das categorias de forma sequencial.
# - A 'Porcentagem' apresenta as proporções em termos percentuais.

##########################################################################################

## Gráficos

# #### Boxplot para o Preço de Venda de Citros por Estado
# Criar um boxplot para visualizar a distribuição do preço por estado
ggplot(dados, aes(x = Estado, y = Preco, fill = Estado)) +
  geom_boxplot() +
  labs(
    title = "Boxplot de Preço de Venda de Citros por Estado",
    x = "Estado",
    y = "Preço de Venda"
  ) +
  theme_minimal() +
  scale_fill_brewer(palette = "Set3") +  # Usando uma paleta de cores predefinida
  theme(
    plot.title = element_text(hjust = 0.5, size = 16),  # Centraliza e aumenta o título
    axis.title.x = element_text(size = 14),  # Aumenta o tamanho do texto do eixo x
    axis.title.y = element_text(size = 14),  # Aumenta o tamanho do texto do eixo y
    axis.text = element_text(size = 12),  # Aumenta o tamanho dos rótulos dos eixos
    axis.text.x = element_text(angle = 45, hjust = 1)  # Rotaciona os rótulos do eixo x em 45 graus
  )

# #### Atividade 2: Crie gráficos para as demais variáveis categóricas
# Você pode usar gráficos de barras ou outros tipos de gráficos. Por exemplo:
# Gráfico de barras para 'Tipo_de_Citros' por 'Estado':
ggplot(dados, aes(x = Tipo_de_Citros, fill = Estado)) +
  geom_bar(position = "dodge") +
  labs(
    title = "Distribuição dos Tipos de Citros por Estado",
    x = "Tipo de Citros",
    y = "Contagem"
  ) +
  theme_minimal()

##########################################################################################

# Medidas Descritivas

# #### Medidas descritivas por categoria (Estado)
# Agora vamos calcular medidas descritivas para o preço de venda (variável numérica) por estado
df_summary <- dados %>%
  group_by(Estado) %>%  # Agrupar pelos estados
  summarise(
    Media = mean(Preco, na.rm = TRUE),  # Média
    Mediana = median(Preco, na.rm = TRUE),  # Mediana
    Desvio_Padrao = sd(Preco, na.rm = TRUE),  # Desvio padrão
    Minimo = min(Preco, na.rm = TRUE),  # Valor mínimo
    Maximo = max(Preco, na.rm = TRUE),  # Valor máximo
    Q1 = quantile(Preco, 0.25, na.rm = TRUE),  # Primeiro quartil
    Q3 = quantile(Preco, 0.75, na.rm = TRUE),  # Terceiro quartil
    N = n()  # Contagem de observações
  )

# Exibindo o resumo das medidas descritivas por Estado
print(df_summary)

# #### Atividade 3: Medidas descritivas para outras variáveis categóricas
# Você pode realizar as mesmas análises para as variáveis categóricas 'Preço de Venda' e 'Tipo_de_Processamento'.
# Isso irá te ajudar a entender como o preço varia em relação a diferentes tipos de citros e processamento.

# #### Boxplot para o Preço de Venda de Citros por Tipo_de_Processamento
# Criar um boxplot para visualizar a distribuição do preço por Tipo_de_Processamento
ggplot(dados, aes(x = Tipo_de_Processamento, y = Preco, fill = Tipo_de_Processamento)) +
  geom_boxplot() +
  labs(
    title = "Boxplot de Preço de Venda de Citros por Tipo_de_Processamento",
    x = "Tipo_de_Processamento",
    y = "Preço de Venda"
  ) +
  theme_minimal() +
  scale_fill_brewer(palette = "Set3") +  # Usando uma paleta de cores predefinida
  theme(
    plot.title = element_text(hjust = 0.5, size = 16),  # Centraliza e aumenta o título
    axis.title.x = element_text(size = 14),  # Aumenta o tamanho do texto do eixo x
    axis.title.y = element_text(size = 14),  # Aumenta o tamanho do texto do eixo y
    axis.text = element_text(size = 12),  # Aumenta o tamanho dos rótulos dos eixos
    axis.text.x = element_text(angle = 45, hjust = 1)  # Rotaciona os rótulos do eixo x em 45 graus
  )

# #### Medidas descritivas por categoria (Tipo_de_Processamento)
# Agora vamos calcular medidas descritivas para o preço de venda (variável numérica) por estado
df_summary <- dados %>%
  group_by(Tipo_de_Processamento) %>%  # Agrupar pelos Tipo_de_Processamento
  summarise(
    Media = mean(Preco, na.rm = TRUE),  # Média
    Mediana = median(Preco, na.rm = TRUE),  # Mediana
    Desvio_Padrao = sd(Preco, na.rm = TRUE),  # Desvio padrão
    Minimo = min(Preco, na.rm = TRUE),  # Valor mínimo
    Maximo = max(Preco, na.rm = TRUE),  # Valor máximo
    Q1 = quantile(Preco, 0.25, na.rm = TRUE),  # Primeiro quartil
    Q3 = quantile(Preco, 0.75, na.rm = TRUE),  # Terceiro quartil
    N = n()  # Contagem de observações
  )

# Exibindo o resumo das medidas descritivas por Tipo_de_Processamento
print(df_summary)
