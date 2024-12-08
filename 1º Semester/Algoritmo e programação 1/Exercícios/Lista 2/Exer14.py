print("Digite a temperatura do dia 1:")
temp1 = float(input())
print("Digite a temperatura do dia 2:")
temp2 = float(input())
print("Digite a temperatura do dia 3:")
temp3 = float(input())

if temp1 > temp2 and temp2 <= temp3:
    print("Feliz.")
elif temp1 < temp2 and temp2 >= temp3:
    print("Triste.")
elif temp1 < temp2 and temp2 < temp3 and (temp3-temp2) < (temp2-temp1):
    print("Triste.")
elif temp1 < temp2 and temp2 < temp3 and (temp3-temp2) >= (temp2-temp1):
    print("Feliz.")
elif temp1 > temp2 and temp2 > temp3 and (temp3-temp2) > (temp2-temp1):
    print("Feliz.")
elif temp1 > temp2 and temp2 > temp3 and (temp3-temp2) <= (temp2-temp1):
    print("triste.")
elif temp1 == temp2 and temp2 < temp3:
    print("Feliz.")
else:
    print("Triste.")