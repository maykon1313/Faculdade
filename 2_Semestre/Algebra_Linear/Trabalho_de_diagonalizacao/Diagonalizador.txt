import numpy as np

class Matriz2x2:
    def __init__(self, matriz):
        self.matriz = matriz

    def descobrir_determinante(self):
        a, b = self.matriz[0][0], self.matriz[0][1]
        c, d = self.matriz[1][0], self.matriz[1][1]
        return a * d - b * c

    def descobrir_autovalores(self):
        determinante = self.descobrir_determinante()
        a, d = self.matriz[0][0], self.matriz[1][1]
        trace = a + d
        discriminant = trace**2 - 4 * determinante
        if discriminant < 0:
            return "A matriz possui autovalores complexos e não pode ser diagonalizada com valores reais."
        sqrt_discriminant = discriminant**0.5
        lambda1 = (trace - sqrt_discriminant) / 2
        lambda2 = (trace + sqrt_discriminant) / 2
        return [lambda1, lambda2]

    def descobrir_autovetores(self, autovalores):
        autovetores = []
        for autovalor in autovalores:
            a, b = self.matriz[0][0] - autovalor, self.matriz[0][1]
            c, d = self.matriz[1][0], self.matriz[1][1] - autovalor
            if b != 0:
                y = -a / b
                autovetores.append([1, y])
            elif d != 0:
                y = -c / d
                autovetores.append([y, 1])
            else:
                autovetores.append([1, 0])
        return autovetores

    @staticmethod
    def inverter(matriz):
        a, b = matriz[0][0], matriz[0][1]
        c, d = matriz[1][0], matriz[1][1]

        determinante = a * d - b * c
        if determinante == 0:
            return None
        
        P_inv = [[d / determinante, -b / determinante], [-c / determinante, a / determinante]]
        return P_inv

    def diagonalizar(self, autovalores, autovetores):
        if isinstance(autovalores, str):
            return autovalores

        P = [[autovetores[0][0], autovetores[1][0]], [autovetores[0][1], autovetores[1][1]]]
        D = [[autovalores[0], 0], [0, autovalores[1]]]
        
        P_inv = Matriz2x2.inverter(P)
        if P_inv is None:
            return "A matriz P não é inversível, logo a matriz não é diagonalizável."
        
        return P, D, P_inv

class Matriz3x3:
    def __init__(self, matriz):
        self.matriz = matriz

    def descobrir_determinante(self):
        ordem = len(self.matriz)
        if ordem == 2:
            return (self.matriz[0][0] * self.matriz[1][1]) - (self.matriz[0][1] * self.matriz[1][0])
        
        determinante = 0
        for i in range(ordem):
            matriz_menor = self.criar_matriz_menor(i)
            determinante += ((-1) ** i) * self.matriz[0][i] * self.descobrir_determinante_aux(matriz_menor)
        return determinante

    def criar_matriz_menor(self, i):
        matriz_aux = []
        for aux in range(1, len(self.matriz)):
            linha = [self.matriz[aux][j] for j in range(len(self.matriz[aux])) if j != i]
            matriz_aux.append(linha)
        return matriz_aux

    def descobrir_determinante_aux(self, matriz):
        if len(matriz) == 2:
            return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0])
        
        determinante = 0
        for i in range(len(matriz)):
            matriz_menor = self.criar_matriz_menor(i)
            determinante += ((-1) ** i) * matriz[0][i] * self.descobrir_determinante_aux(matriz_menor)
        return determinante

    def descobrir_autovalores(self):
        autovalores = np.linalg.eigvals(np.array(self.matriz))
        autovalores = np.round(autovalores, decimals=5)
        autovalores_reais = [int(val.real) if np.isclose(val.imag, 0) else val for val in autovalores]
        return autovalores_reais

    def escalar_autovetor(self, autovetor):
        if np.all(autovetor == 0):
            return autovetor
        fator = np.min(np.abs(autovetor[autovetor != 0]))
        autovetor_escalado = np.round(autovetor / fator).astype(int)
        if autovetor_escalado[0] < 0:
            autovetor_escalado *= -1
        return autovetor_escalado

    def descobrir_autovetores(self):
        _, autovetores = np.linalg.eig(np.array(self.matriz))
        autovetores = np.round(autovetores, decimals=5)
        return [self.escalar_autovetor(vetor) for vetor in autovetores.T]

    def diagonalizar(self):
        autovalores = self.descobrir_autovalores()
        if isinstance(autovalores, str):
            return autovalores
        
        autovetores = self.descobrir_autovetores()
        
        D = np.diag(autovalores)
        P = np.array(autovetores).T
        try:
            P_inv = np.linalg.inv(P)
        except np.linalg.LinAlgError:
            return "A matriz P não é inversível, logo a matriz não é diagonalizável."
        return P, D, P_inv

class MatrizNxN:
    def __init__(self, matriz):
        self.matriz = matriz

    def descobrir_determinante(self):
        return np.linalg.det(self.matriz)

    def descobrir_autovalores(self):
        autovalores = np.linalg.eigvals(self.matriz)
        autovalores = np.round(autovalores, decimals=5)

        if any(not np.isclose(val.imag, 0) for val in autovalores):
            return "A matriz possui autovalores complexos e não pode ser diagonalizada com valores reais."
        
        return [val.real for val in autovalores]
    
    def descobrir_autovetores(self):
        _, autovetores = np.linalg.eig(self.matriz)
        autovetores = np.round(autovetores, decimals=5)
        return autovetores.T.tolist()

    def diagonalizar(self):
        autovalores = self.descobrir_autovalores()
        if isinstance(autovalores, str):
            return autovalores
        
        autovetores = self.descobrir_autovetores()
        
        D = np.diag(autovalores)
        P = np.array(autovetores).T
        
        try:
            P_inv = np.linalg.inv(P)
        except np.linalg.LinAlgError:
            return "A matriz P não é inversível, logo a matriz não é diagonalizável."
        
        return P, D, P_inv
 
def imprimir_resultados(determinante, autovalores, autovetores, resultado, ordem, matriz):
    print(f"Determinante: {determinante}.")
    if autovalores:
        autovalores_formatados = [float(autovalor) for autovalor in autovalores]
        print(f"Autovalores: {autovalores_formatados}.")
    if autovetores:
        autovetores_formatados = [v.tolist() if isinstance(v, np.ndarray) else v for v in autovetores]
        print(f"Autovetores: {autovetores_formatados}.")

    if autovalores and autovetores:
        print("Autoespaços associados aos autovalores:")
        for i, autovalor in enumerate(autovalores):
            print(f"Autoespaço associado ao autovalor {autovalor}: {autovetores[i]}")

    if resultado:
        if isinstance(resultado, str):
            print(resultado)
        else:
            P, D, P_inv = resultado

            print("Matriz P (autovetores):\n", P)
            print("Matriz D (diagonal dos autovalores):\n", D)
            print("Matriz P^-1:\n", P_inv)

            print("Matriz = P . D . P^-1:")
            for i in range(ordem):
                print(f"{np.array(matriz[i])} = {np.array(P[i])} . {np.array(D[i])} . {np.array(P_inv[i])}")

def print_matriz_info(ordem, matriz):
    if ordem == 1:
        determinante = matriz[0][0]
        autovalores = matriz[0]
        autovetores = [1]
        P, D, P_inv = [1], matriz[0], [1]
        resultado = (P, D, P_inv)

    elif ordem == 2:
        matriz_obj = Matriz2x2(matriz)
        determinante = matriz_obj.descobrir_determinante()
        autovalores = matriz_obj.descobrir_autovalores()
        autovetores = matriz_obj.descobrir_autovetores(autovalores) if autovalores else None
        resultado = matriz_obj.diagonalizar(autovalores, autovetores) if autovalores else None

    elif ordem == 3:
        matriz_obj = Matriz3x3(matriz)
        determinante = matriz_obj.descobrir_determinante()
        autovalores = matriz_obj.descobrir_autovalores()
        autovetores = matriz_obj.descobrir_autovetores()
        resultado = matriz_obj.diagonalizar()

    else:
        matriz_obj = MatrizNxN(np.array(matriz))
        determinante = matriz_obj.descobrir_determinante()
        autovalores = matriz_obj.descobrir_autovalores()
        autovetores = matriz_obj.descobrir_autovetores()
        resultado = matriz_obj.diagonalizar()

    imprimir_resultados(determinante, autovalores, autovetores, resultado, ordem, matriz)

def ler_matriz(ordem):
    matriz = []
    i = 1
    while i <= ordem:
        print(f"Digite linha {i}º (Deve conter {ordem} elementos):")
        linha = list(map(int, input().split()))
        matriz.append(linha) 
        i += 1
    return matriz

def main():
    print("Qual a ordem da matriz?")
    ordem = int(input())

    matriz = ler_matriz(ordem)

    print_matriz_info(ordem, matriz)

main()
