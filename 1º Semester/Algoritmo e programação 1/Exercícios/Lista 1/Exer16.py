print("MB:")
mb = float(input())
print("Mbps:")
mbps = float(input())

tempo = (mb/mbps)/60

print("Demorará: " + str(tempo) + "minutos.")