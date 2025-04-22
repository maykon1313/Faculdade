print("Digite se é Vertebrado ou Invertebrado:")
ver_inv = str(input())
print("Digite a classe:")
classe = str(input())
print("Digite a alimentação:")
alimentação = str(input())

if ver_inv == "Vertebrado":
    if classe == "Ave":
        if alimentação == "Carnívoro":
            print("Águia.")
        else:
            print("Pomba.")
    else:
        if alimentação == "Onívoro":
            print("Homem.")
        else:
            print("vaca.")
else:
    if classe == "Iseto":
        if alimentação == "Hematófago":
            print("Pulga.")
        else:
            print("Lagarta.")
    else:
        if alimentação == "Hematófago":
            print("Sanguessuga.")
        else:
            print("Minhoca.")