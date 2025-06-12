setwd("C:/Users/maykon.kazuhiro/Desktop/Prob_est")
dados <- read.csv("dados.csv", sep=",")
dados%$
str(dados)

library(ggplot2)

# Gráficos:

# Gráfico de barra
ggplot(dados, aes(x = Sexo, y = Peso_kg, fill = Sexo)) + geom_bar(stat = "identity") + scale_fill_manual(values = c("Masculino"="blue", "Feminino"="red"))

# Gráfico Boxplot 
ggplot(dados, aes(x = Sexo, y = Peso_kg, fill = Sexo)) + geom_boxplot() + scale_fill_manual(values = c("Masculino"="blue", "Feminino"="red"))


# Histograma
hist(dados$Peso_kg)

# Histograma no ggplot
ggplot(dados, aes(x = Peso_kg)) + geom_histogram(fill = "red", color = "black")



# Medidas descritivas:

# Média
mean(dados$Peso_kg)

# Mediana
median(dados$Peso_kg)

# Variancia
var(dados$Peso_kg)

# Desvio padrão
sd(dados$Peso_kg)

# Minímo
min(dados$Peso_kg)

# Máximo
max(dados$Peso_kg)

# Amplitude
diff(range(dados$Peso_kg))




# Dados
dados_aux <- c(7, 12, 15, 16, 16, 17, 17, 18, 19, 20, 21, 45)

# Quantil
quantile(dados_aux)

boxplot(dados_aux)

# Quantil n = k/100 * n
# Quantil 25% = 25/100 * 12 = 3
# Quantil 50% = 50/100 * 12 = 6
# Quantil 75% = 75/100 * 12 = 9
# q1 = 15,5
# q2 = 17
# q3 = 19,5

# AIQ = q3 - q1
# AIQ = 19,5 - 15,5 = 4

# LI = q1 - 1,5 * AIQ
# LI = 15,5 - 1,5 * 4 = 9,5

# LS = q3 + 1,5 * AIQ
# LS = 19,5 + 1,5 * 4 = 25,5



