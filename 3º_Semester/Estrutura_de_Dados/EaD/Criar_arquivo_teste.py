import random

with open("dados_teste.txt", "w") as f:
    for _ in range(10000):
        f.write(str(random.randint(0, 99999)) + "\n")