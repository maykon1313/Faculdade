import matplotlib.pyplot as plt

# Lê o arquivo distribuiçao.txt e armazena os valores em uma lista
with open("distribuicao.txt") as f:
    distribuicao = [int(line.strip()) for line in f if line.strip()]

# Gera o gráfico
plt.figure(figsize=(10, 4))
plt.bar(range(len(distribuicao)), distribuicao)
plt.xlabel("Posição da Tabela Hash")
plt.ylabel("Quantidade de Elementos")
plt.title("Distribuição de Elementos nas Listas da Tabela Hash")
plt.tight_layout()
plt.savefig("grafico.png")
# plt.show()