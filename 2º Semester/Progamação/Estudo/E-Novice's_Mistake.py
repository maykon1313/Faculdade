#n * a - b
#Há a necessidade de testar todos os valores para "a" no intervalo da questão
#Porém, é possível limitar os valores de "b"

#n = 2
#a = 20, b = 18
#2 * 20 - 18 = 22
#"22222222222222222222" − 18
#20 - 18 = 2
#"22"

#n = 10
#a = 1262, b = 2519
#10 * 1262 - 2519 = 10101
#"1010101010..." − 2519
#2524 - 2519 = 5
#"10101"

cases = int(input())
for _ in range(cases):
    n = int(input())
    ans = []
    str_N = str(n)
    len_N = len(str_N)

    for a in range(1, 10001):
        min_B = max(1, len_N * a - 5) #Limita a diferença em 6 dígitos, pois o valor máximo é 10^6
        max_B = len_N * a #Limita o B para não passar de n*a e sobrar pelo menos de 1 dígitos (-1 já está na função range).
        for b in range(min_B, max_B):
            num_answer = n * a - b #10 * 1262 - 2519 = 10101
            str_answer = 0
            for i in range(len_N * a - b): #len: 2524 - 2519 = 5
                str_answer = str_answer * 10 + int(str_N[i % len_N]) #10101 
            
            if num_answer == str_answer:
                ans.append((a, b))
    
    print(len(ans))
    for two_num in ans:
        print(*two_num)