# Amostra deve ser conforme a realidade que será aplicada
# Em casos como em pequenas amostras pode estar enviesado

# Hold out (ideal para grande amostras): Em um conjunto de dados com 1000000 dados, separar em treino e teste (2/3 e 1/3).

# Hold out com repetição: artificialmente aumenta o treino da IA.

# Validação cruzada (Cross validation): particiona a amostra em K-partições, separa uma das partições e treina com o resto, em seguida, 
# pega o segundo Hold, separa e treina novamente, sempre avalidando a performace com o Hold separado, até o fim das partições. 
# Idealmente, na extratificada, é mantido a proporção do caso real para cada partição.

# Leave one out: Deixa um exemplo de fora e testa com o resto para treino, muito custoso, mas muito eficiente.

#*Bootstrap
# Hold out         | I | >1000
# Cross Validation | K | 300 < x < 1000
# Leave One Out    | N | <300

# ||X|| >= 30, para amostras é muito usado o valor de 30, converge para uma gaussiana.
# 300/10 = 30

# OBS.: Não deixa vazar casos do treino no teste!!! 

# Fine Tuning: Treino, validação (Simulado) e teste. Dentro do treino fazer um Hold Out ou Cross validation, e na validação também.
# Nested Cross Validation (Validação Cruzada Aninhada):


#Este é o conceito principal por trás do esquema `| TREINO | VALIDAÇÃO | TESTE |`. É uma técnica poderosa para evitar o que chamamos de "otimismo" na avaliação do modelo.
#Funciona com dois "loops" de validação cruzada, um dentro do outro:
#   Loop Externo (Avaliação do Modelo):
#    1.  Primeiro, ele separa uma parte dos dados para ser o conjunto de Teste final (ex: 20% do total).
#    2.  O restante dos dados (80%) é usado para o processo de treino e validação.
#    3.  Este passo é repetido várias vezes (K vezes), a cada vez separando uma porção diferente para ser o conjunto de Teste.

#   Loop Interno (Ajuste de Hiperparâmetros):
#    1.  Para cada conjunto de "Treino + Validação" criado pelo loop externo, um segundo processo de validação cruzada é executado.
#    2.  Esses dados são divididos novamente em K partes. O modelo é treinado em K-1 partes e validado na parte restante para encontrar os melhores hiperparâmetros.
#    3.  Ao final do loop interno, você tem um modelo "otimizado".

#Finalmente, o modelo otimizado no loop interno é avaliado no conjunto de Teste que foi separado pelo loop externo.
#A validação cruzada aninhada garante que a escolha dos melhores hiperparâmetros (o *fine tuning*) não "veja" os dados de teste final. Isso resulta em uma estimativa muito mais realista e confiável de como seu modelo se comportará no mundo real.

# |                                 | TESTE |
# | TREINO              | VALIDAÇÃO | TESTE |




