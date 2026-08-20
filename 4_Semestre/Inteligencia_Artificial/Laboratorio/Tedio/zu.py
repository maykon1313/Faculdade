import random

alp = [
    ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', '|', '\\', ':', ';', '"', '\'', '<', '>', ',', '.', '?', '/', '*', '∗', '·', '×',
    'σ', '−', '±', 'τ', 'δ', '’', '–',
    'á', 'à', 'â', 'ã', 'ä', 'é', 'è', 'ê', 'ë', 'í', 'ì', 'î', 'ï', 'ó', 'ò', 'ô', 'õ', 'ö', 'ú', 'ù', 'û', 'ü', 'ç',
    'Á', 'À', 'Â', 'Ã', 'Ä', 'É', 'È', 'Ê', 'Ë', 'Í', 'Ì', 'Î', 'Ï', 'Ó', 'Ò', 'Ô', 'Õ', 'Ö', 'Ú', 'Ù', 'Û', 'Ü', 'Ç'
]

def crip():
    nuns = []

    while (len(nuns) < len(alp)):
        aux = random.randint(0, len(alp))

        try:
            nuns.index(aux)
        except:
            nuns.append(aux)

    return nuns

def esp(c, nuns):
    f = ""
    posi = alp.index(c)
    posi = nuns[posi]
    if posi:
        for j in range(posi): f += " "
    f += '\n'
    return f

def main():
    arq = open('crip.txt', 'w')
    nuns = crip()


    arq.write(str(nuns[0]))
    for i in range(1,len(nuns)):
        arq.write(',' + str(nuns[i]))
    arq.write('\n')

    s = input()

    for c in s:
        arq.write(esp(c, nuns))

if __name__ == "__main__":
    main()