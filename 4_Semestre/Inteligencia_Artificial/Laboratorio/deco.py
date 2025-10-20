alp = [' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

def decode_line(line: str) -> str:
    spaces = len(line.rstrip('\n'))
    if spaces < len(alp):
        return alp[spaces]
    return '?'

decoded = []
with open('crip.txt', 'r') as arq:
    for line in arq:
        decoded.append(decode_line(line))

print(''.join(decoded))