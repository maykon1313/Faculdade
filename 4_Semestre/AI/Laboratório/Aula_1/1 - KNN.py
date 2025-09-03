# Para KNN, em um gráfico com pessoas, utilizando AlturaXPeso, havendo um pessoa com melhores atributos há mais chance de ser escolhido para o time.
# Nesse caso, a distância entre os pontos é calculada em um espaço N-dimensional, utilizando métricas como a distância Euclidiana 
# ou outras métricas apropriadas. Assim, é possível determinar a proximidade entre os pontos e aplicar o conceito de vizinhos mais próximos para 
# avaliar a "qualidade" ou classificação de um ponto.Para um gráfico N-dimensional, exemplo: altura, peso, idade, sexo e etc..., ainda é possível 
# aplicar essa ideia.
import random
import turtle
import time
import math

def grafico(coordenadas_x, coordenadas_y, cores, tamananho, velocidade):
    # --- Configuração da Tela ---
    tela = turtle.Screen()
    tela.title("Gráfico de Pontos com Turtle")
    tela.setworldcoordinates(0, 0, 100 + 10, 100 + 10)

    turtle.clear()

    # --- Configuração da Tartaruga ---
    caneta = turtle.Turtle()
    caneta.speed(velocidade)  # Velocidade máxima
    caneta.hideturtle()  # Esconde a seta da tartaruga
    caneta.penup()  # Levanta a caneta para não desenhar linhas entre os pontos

    # --- Desenho dos Pontos ---
    for i in range(len(coordenadas_x)):
        x = coordenadas_x[i]
        y = coordenadas_y[i]
        caneta.goto(x, y)
        caneta.dot(tamananho, cores[i])

    turtle.update()

class Ponto:
    x = 0
    y = 0
    cor = ""

    def __init__(self, colorido):
        self.x = random.randint(0, 100)
        self.y = random.randint(0, 100)

        if colorido:
            if random.randint(0, 100) % 2 == 0:
                self.cor = "blue"
            else:
                self.cor = "red"
        
        else:
            self.cor = "grey"

def dist_eucli(ponto1, ponto2):
    dist_x = ponto2.x - ponto1.x 
    dist_y = ponto2.y - ponto1.y
    return math.sqrt(dist_x**2 + dist_y**2)

def classificar_ponto(pontos_coloridos, ponto_cinza, k):
    if not pontos_coloridos:
        return "cinza"

    # 1. Calcular a distância para todos os pontos de treino
    distancias = []
    for ponto in pontos_coloridos:
        dist = dist_eucli(ponto_cinza, ponto)
        distancias.append((dist, ponto.cor))

    # 2. Ordenar as distâncias e pegar os k vizinhos mais próximos
    distancias.sort(key=lambda item: item[0])
    vizinhos_mais_proximos = distancias[:k]

    # 3. Fazer a votação (contar a cor mais comum)
    cores_dos_vizinhos = [cor for dist, cor in vizinhos_mais_proximos]
    # Counter cria um dicionário como {'vermelho': 3, 'azul': 2}

    red = 0
    blue = 0

    for cor in cores_dos_vizinhos:
        if cor == "blue":
            blue += 1
        else:
            red += 1

    if blue > red:
        cor_mais_comum = "blue"
    else:
        cor_mais_comum = "red"

    return cor_mais_comum

def main():
    pontos1 = []

    for i in range(100):
        pontos1.append(Ponto(True))

    coordenadas_x1 = [ponto.x for ponto in pontos1]
    coordenadas_y1 = [ponto.y for ponto in pontos1]
    cores1 = [ponto.cor for ponto in pontos1]

    # Exibe o gráfico com pontos coloridos
    grafico(coordenadas_x1, coordenadas_y1, cores1, 15, 0)
    time.sleep(2)

    pontos2 = []

    for i in range(100):
        pontos2.append(Ponto(False))

    coordenadas_x2 = [ponto.x for ponto in pontos2]
    coordenadas_y2 = [ponto.y for ponto in pontos2]
    cores2 = [ponto.cor for ponto in pontos2]

    # Exibe o gráfico com pontos cinzas
    grafico(coordenadas_x2, coordenadas_y2, cores2, 15, 0.5)
    time.sleep(2)
    
    for ponto in pontos2:
        ponto.cor = classificar_ponto(pontos1, ponto, 1)

    # Atualiza a lista de cores após classificar os pontos
    cores2 = [ponto.cor for ponto in pontos2]

    grafico(coordenadas_x2, coordenadas_y2, cores2, 20, 0.5)
    turtle.done()

if __name__ == "__main__":
    main()
