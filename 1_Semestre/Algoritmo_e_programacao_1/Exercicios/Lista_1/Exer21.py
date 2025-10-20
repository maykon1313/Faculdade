print("Distância(Km):")
d = float(input())
print("Velocidade(Km/h):")
v = float(input())

media = d/v
v2 = (v * 1000)/3600

print("Tempo médio é de: " + str(media))
print("Velocidade em m/s: " + str(v2))