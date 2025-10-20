# definições básicas

def pai(i):
  return (i - 1) // 2

def dir(i):
  return 2 * i + 2

def esq(i):
  return 2 * i + 1

# obviamente quero algo eficiente
def heap_insert(s, x):
  s.append(x)
  n = len(s)
  i = n - 1
  while i > 0 and s[pai(i)] < x:
    s[i] = s[pai(i)]
    i = pai(i)
  s[i] = x

# Vamos inserir 5 elementos no intervalo de 1 a 100 em um heap inicialmente vazio.
import random

s = []
for i in range(5):
  x = random.randint(1, 100)
  print (x, end = " ")
  heap_insert(s, x)

print()
print(s)

"""# Exercício: Desenhe a árvore obtida na célula acima para verificar que ela é um heap.

# Agora vamos fazer a função $heap_delete$ que recebe o heap $s$ remove o elemento $x = s[0]$, pega o último elemento e veja onde é a posição correta para ele.
"""

def heap_delete(s):
  x = s[0]
  y = s.pop()
  n = len(s)

  i = 0
  while esq(i) < n:
    max = i
    if s[esq(i)] > y: max = esq(i)
    if dir(i) < n and s[dir(i)] > s[max]: max = dir(i)

    if max == i: break

    s[i] = s[max]
    i = max
  s[i] = y
  return x

heap_delete(s)
print (s)

# verifica se é heap
for i in range(1, len(s)):
    if i == len(s) - 1:
        print ("é heap")
        break
    
    if s[i] > s[pai(i)]:
        print ("não é heap: " + str(i))
        break