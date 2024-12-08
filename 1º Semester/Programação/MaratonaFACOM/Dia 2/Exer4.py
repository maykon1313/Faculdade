dict = {}

while True:
    try:
        x = input()       
        dict[x] = 1

    except EOFError:
        print(len(dict))
        break