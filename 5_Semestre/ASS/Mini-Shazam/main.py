from pathlib import Path
import pickle

from src.matching import indexar_musica, buscar_musica

BASE_DIR = Path(__file__).parent

MUSICAS = BASE_DIR / "audios" / "raw"
GRAVACOES = BASE_DIR / "audios" / "gravacao"
BANCO = BASE_DIR / "data" / "banco_fingerprint.pkl"

def salvar_banco(banco, caminho_arquivo):
	with open(caminho_arquivo, "wb") as arquivo:
		pickle.dump(banco, arquivo)

def carregar_banco(caminho_arquivo):
	with open(caminho_arquivo, "rb") as arquivo:
		return pickle.load(arquivo)

def indexar(metodos=None):
	metodos = metodos or {"stft": True, "cqt": True, "wavelet": True, "hibrido": True}
	banco = {chave: {} for chave, ativo in metodos.items() if ativo}

	print("\nIndexando músicas para o banco de dados.")

	# Lista os arquivos de referencia.
	files = list(MUSICAS.glob("*.mp3"))
	if not files:
		print("Nenhuma musica encontrada em:", MUSICAS)
		return
	# Ordena pelo nome numerico do arquivo.
	files.sort(key=_ordem_nome)
	
	for caminho in files:
		nome = caminho.stem
		print("Indexando:", nome)
		indexar_musica(str(caminho), nome, banco, metodos=metodos)

	salvar_banco(banco, BANCO)
	print("Banco salvo em:", BANCO)

def buscar(metodos=None):
	metodos = metodos or {"stft": True, "cqt": True, "wavelet": True, "hibrido": True}
	banco = carregar_banco(BANCO)

	print("\nBuscando correspondencia para os áudios.")

	# Lista as gravacoes a serem reconhecidas.
	files = list(GRAVACOES.glob("*.mp3"))
	if not files:
		print("Nenhuma gravacao encontrada em:", GRAVACOES)
		return
	# Ordena pelo nome numerico do arquivo.
	files.sort(key=_ordem_nome)

	for caminho in files:
		nome = caminho.stem
		print("\nBuscando:", nome)
		buscar_musica(str(caminho), banco, metodos=metodos)

def main():
	ind = True
	bus = True

	stft = True
	cqt = True
	wavelet = True
	hibrido = True

	metodos = {"stft": stft, "cqt": cqt, "wavelet": wavelet, "hibrido": hibrido}

	if ind:
		indexar(metodos)
		
	if bus:
		buscar(metodos)

def _ordem_nome(caminho):
	try:
		return int(caminho.stem.split("-")[0])
	except (ValueError, IndexError):
		return caminho.stem

if __name__ == "__main__":
	main()
