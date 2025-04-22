n = int(input())
v = []
v.append(10)
v.append(15)

i = 0
while i < n:
    v.append(float(input()))
    i += 1

#Cada posição de memória ocupa 1 byte;
#O processador em questão utiliza endereços de memória de 16 bits (2bytes);
#Um valor inteiro ocupa 32 bits (4 bytes);
#Um valor float ocupa 64 bits (8 bytes).
#Todas as regiões de memória podem ser utilizadas, exceto as posições destacadas em vermelho;
#Qualquer vetor no Python recebe, inicialmente, 8 bytes de memória para armazenar valores. Assuma que o sistema operacional decidiu alocar o vetor, inicialmente, na posição 8 de memória;
#Escolha a região de memória de sua preferência para alocar a variável n na memória;
#Você pode realocar as variáveis do seu programa na memória sempre que houver necessidade de mais espaço.

#Qual será o estado da memória em dois momentos diferentes da execução:

#Logo após a execução da linha 4:

#0  (n
#1      n
#2          n
#3              n)
#4  (8
#5      8
#6          8
#7              8)
#8  (10
#9      10
#10         10
#11             10)
#12 (15
#13     15
#14         15
#15             15)
#16
#...

#Logo após a execução da linha 8:

#bytes
#0  (n
#1      n
#2          n
#3              n)
#4  (12
#5      12
#6          12
#7              12)
#8 (i+1
#9     i+1
#10         i+1
#11             i+1)]
#12  (10
#13      10
#14         10
#15             10)
#16 (15
#17     15
#18         15
#19             15)
#20 (float
#21         float
#22                 float
#23                         float
#24                                 float
#25                                         float
#26                                                 float
#27                                                         float)
#28
#...