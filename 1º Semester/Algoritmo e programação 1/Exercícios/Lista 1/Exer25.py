print("Tempo em horas:")
t = int(input())
print("Velocidade média em Km/h:")
v = float(input())

import math

dista = v * t
gaso = math.ceil(dista/12)

print("Distância: " + str(dista) + ", Litros nescessários: " + str(gaso))