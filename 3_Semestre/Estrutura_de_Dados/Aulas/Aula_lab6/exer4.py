ALFA_NUMERICO = 256

def bad_caracter(padrao):
   m = len(padrao)
   caracter_ruim = [-1] * ALFA_NUMERICO
   for i in range(m):
      caracter_ruim[ord(padrao[i])] = i
   return caracter_ruim

def good_sufix(padrao):
   m = len(padrao)
   sufixo = [0] * m
   sufixo_bom = [m] * m

   # Preenche o vetor de sufixos
   sufixo[m-1] = m
   g = m - 1
   f = 0
   for i in range(m-2, -1, -1):
      if i > g and sufixo[i + m - 1 - f] < i - g:
         sufixo[i] = sufixo[i + m - 1 - f]
      else:
         if i < g:
               g = i
         f = i
         while g >= 0 and padrao[g] == padrao[g + m - 1 - f]:
               g -= 1
         sufixo[i] = f - g

   # Preenche o vetor de deslocamento do sufixo bom
   for i in range(m):
      sufixo_bom[i] = m
   j = 0
   for i in range(m-1, -1, -1):
      if sufixo[i] == i + 1:
         for j in range(m-1-i):
               if sufixo_bom[j] == m:
                  sufixo_bom[j] = m-1-i
   for i in range(m-1):
      sufixo_bom[m-1-sufixo[i]] = m-1-i

   return sufixo_bom

def boyer_moore(texto, padrao):
   n = len(texto)
   m = len(padrao)
   contador = 0
   pulos = 0

   if m == 0 or n < m:
      return 0

   caracter_ruim = bad_caracter(padrao)
   sufixo_bom = good_sufix(padrao)

   while pulos <= n - m:
      j = m - 1

      while j >= 0 and padrao[j] == texto[pulos + j]:
         j -= 1

      if j < 0:
         contador += 1
         pulos += sufixo_bom[0]
      else:
         pulos_caracter_ruim = j - caracter_ruim[ord(texto[pulos + j])]
         pulos_sufixo_bom = sufixo_bom[j]
         pulos += max(1, max(pulos_caracter_ruim, pulos_sufixo_bom))

   return contador

if __name__ == "__main__":
   texto = "BEM_VINDO_AO_EXEMPLO_VISUAL"
   padrao = "EXEMPLO"

   ocorrencias = boyer_moore(texto, padrao)
   print("Número de ocorrências:", ocorrencias)
