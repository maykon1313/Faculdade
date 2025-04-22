n_alien, n_mensagem = map(int, input().split())
impossivel_alien = False

alf_alien = input()
mensagem = input()

for letra in mensagem:
    if letra not in alf_alien:
        impossivel_alien = True
        break

if not impossivel_alien:
    print("S")
else:
    print("N")