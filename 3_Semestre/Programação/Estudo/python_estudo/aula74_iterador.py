frase = "Itimaliameudeusdoceucoisalinda"
iterador = iter(frase)

while True:
    try:
        print(next(iterador))
    except:
        break
