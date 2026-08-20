palavra_secreta = "pinhamonhangaba"
letras_acertadas = ""
palavra_formada = ""
tentativas = 0

for i in range(len(palavra_secreta)):
    palavra_formada += '*'

print(f"A palavra secreta se parece com isso: {palavra_formada}")

while True:
    tentativas += 1
    print(f"\nTente adivinhar uma letra da palavra secreta (tentativa: {tentativas}):")
    letra = input()[0]
    
    if letra not in palavra_secreta:
        print("A letra não está na palavra secreta.")
        continue

    letras_acertadas += letra

    palavra_formada = ""
    print("Situação atual da palavra: ", end="")
    for letras_palavra_secreta in palavra_secreta:
        if letras_palavra_secreta in letras_acertadas:
            palavra_formada += letras_palavra_secreta
        else:
            palavra_formada += '*'
    print(palavra_formada)

    if palavra_formada == palavra_secreta:
        print("Parabéns, achastes a paralavra secreta.")
        break
