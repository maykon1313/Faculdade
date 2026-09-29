from random import randint

with open("vetor.txt", "w") as f:
    for i in range(1, 8000):
        num = randint(1, 10000)
        f.write(str(num) + ", ")
