#Eu recebo o comprimento e a quantidade de tapetes
#O comprimento é a soma dos comprimentos dos tapetes
#A área é a soma dos quadradros dos comprimentos dos tapetes
#Áreas possiveis: 1, 4, 9, 16, 25, 36...
#Comprimentos:    1, 2, 3,  4,  5,  6...

#Exemplo: L = 20 e N = 4
#5+5+5+5 = 20 ; 25+25+25+25 = 100
#1+1+1+17= 20 ; 01+01+01+289= 292

l, n = input().split()
l = int(l)
n = int(n)

area = ((l - (n -1))**2) + (n-1)

print(area)