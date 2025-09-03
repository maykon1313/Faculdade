s = input()

alp = [' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

arq = open('crip.txt', 'w')

def esp(c):
    f = ""
    for j in range(alp.index(c)): f += " "
    f += '\n'
    return f

for c in s:
    arq.write(esp(c))