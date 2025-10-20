print("Digite as horas de início do jogo:")
hi = int(input())
print("Digite os minutos de início do jogo:")
mi = int(input())
print("Digite as horas de fim do jogo:")
hf = int(input())
print("Digite os minutos de fim do jogo:")
mf = int(input())

if hf < hi:
    hf = hf + 24

horas = hf - hi
minutos = mf - mi

if minutos < 0:
    horas = horas - 1
    minutos = minutos + 60

print("A duração do jogo foi de " + str(horas) + " horas e " + str(minutos) + " minutos.")