from pathlib import Path

from src.padronizacao import carregar_audio, TAXA_AMOSTRAGEM
from src.STFT import calcular_stft
from src.cqt import calcular_cqt
from src.wavelet import calcular_wavelet
from src.picos import encontrar_picos
from src.hashes import gerar_hashes
from src.imagens import plot_escalograma, plot_espectrograma, plot_histograma_offsets, plot_mapa_constelacao, plot_sinal_tempo

def _base_dir():
	return Path(__file__).resolve().parents[1]

def _caminho_imagem(base_dir, subpasta, categoria, nome_base, sufixo):
	return base_dir / "images" / subpasta / categoria / f"{nome_base}_{sufixo}.png"

def shazam(caminho_arquivo, categoria, base_dir=None, metodos=None):
	base_dir = base_dir or _base_dir()
	nome_base = Path(caminho_arquivo).stem
	metodos = metodos or {"stft": True, "cqt": True, "wavelet": True, "hibrido": True}
	gerar_stft = metodos.get("stft", False)
	gerar_cqt = metodos.get("cqt", False)
	gerar_wavelet = metodos.get("wavelet", False)
	gerar_hibrido = metodos.get("hibrido", False)
	precisa_stft = gerar_stft or gerar_hibrido
	precisa_cqt = gerar_cqt or gerar_hibrido

	sinal = carregar_audio(caminho_arquivo)

	if precisa_stft:
		stft, frequencias_stft, tempos_stft = calcular_stft(sinal)
		picos_stft = encontrar_picos(stft, frequencias_stft, tempos_stft)
	if precisa_cqt:
		cqt, frequencias_cqt, tempos_cqt = calcular_cqt(sinal)
		picos_cqt = encontrar_picos(cqt, frequencias_cqt, tempos_cqt)
	if gerar_wavelet:
		wavelet, frequencias_wavelet, tempos_wavelet = calcular_wavelet(sinal)
		picos_wavelet = encontrar_picos(wavelet, frequencias_wavelet, tempos_wavelet)

	picos = {}
	if gerar_stft:
		picos["stft"] = picos_stft
	if gerar_cqt:
		picos["cqt"] = picos_cqt
	if gerar_wavelet:
		picos["wavelet"] = picos_wavelet
	if gerar_hibrido:
		picos["hibrido"] = picos_stft + picos_cqt

	plot_sinal_tempo(
		sinal,
		TAXA_AMOSTRAGEM,
		_caminho_imagem(base_dir, "raw", categoria, nome_base, "sinal"),
		f"Sinal no tempo - {nome_base}",
	)
	if gerar_stft:
		plot_espectrograma(
			stft,
			frequencias_stft,
			tempos_stft,
			_caminho_imagem(base_dir, "espectograma", categoria, nome_base, "espectrograma_stft"),
			f"Espectrograma - {nome_base} (STFT)",
		)
		plot_mapa_constelacao(
			picos_stft,
			_caminho_imagem(base_dir, "mapa_de_constelacao", categoria, nome_base, "constelacao_stft"),
			f"Mapa de constelacao - {nome_base} (STFT)",
		)
	if gerar_cqt:
		plot_espectrograma(
			cqt,
			frequencias_cqt,
			tempos_cqt,
			_caminho_imagem(base_dir, "espectograma", categoria, nome_base, "espectrograma_cqt"),
			f"Espectrograma - {nome_base} (CQT)",
		)
		plot_mapa_constelacao(
			picos_cqt,
			_caminho_imagem(base_dir, "mapa_de_constelacao", categoria, nome_base, "constelacao_cqt"),
			f"Mapa de constelacao - {nome_base} (CQT)",
		)
	if gerar_wavelet:
		plot_escalograma(
			wavelet,
			frequencias_wavelet,
			tempos_wavelet,
			_caminho_imagem(base_dir, "escalograma", categoria, nome_base, "escalograma_wavelet"),
			f"Escalograma - {nome_base} (Wavelet)",
		)
		plot_mapa_constelacao(
			picos_wavelet,
			_caminho_imagem(base_dir, "mapa_de_constelacao", categoria, nome_base, "constelacao_wavelet"),
			f"Mapa de constelacao - {nome_base} (Wavelet)",
		)
	if gerar_hibrido:
		plot_mapa_constelacao(
			picos["hibrido"],
			_caminho_imagem(base_dir, "mapa_de_constelacao", categoria, nome_base, "constelacao_hibrido"),
			f"Mapa de constelacao - {nome_base} (Hibrido)",
		)

	return {metodo: gerar_hashes(valores) for metodo, valores in picos.items()}

def indexar_musica(caminho_arquivo, nome_musica, banco_dados, metodos=None):
	hashes_por_metodo = shazam(caminho_arquivo, "musicas", metodos=metodos)

	for metodo, hashes in hashes_por_metodo.items():
		sub_banco = banco_dados.setdefault(metodo, {})
		for chave, tempo_ancora in hashes:
			sub_banco.setdefault(chave, []).append((nome_musica, tempo_ancora))

def buscar_musica(caminho_gravacao, banco_dados, metodos=None):
	base_dir = _base_dir()
	nome_base = Path(caminho_gravacao).stem

	hashes_por_metodo = shazam(caminho_gravacao, "gravacao", base_dir=base_dir, metodos=metodos)
	rotulos = {"stft": "STFT", "cqt": "CQT", "wavelet": "Wavelet", "hibrido": "Hibrido"}

	for metodo, hashes in hashes_por_metodo.items():
		sub_banco = banco_dados.get(metodo)
		if sub_banco is None:
			continue
		contagem = {}

		for chave, tempo_gravacao in hashes:
			for nome_musica, tempo_banco in sub_banco.get(chave, []):
				offset = round(tempo_banco - tempo_gravacao, 2)
				contagem.setdefault(nome_musica, {})
				contagem[nome_musica][offset] = contagem[nome_musica].get(offset, 0) + 1

		melhor_musica = None
		melhor_contagem = 0

		for nome_musica, offsets in contagem.items():
			pico = max(offsets.values())
			if pico > melhor_contagem:
				melhor_contagem = pico
				melhor_musica = nome_musica

		if melhor_musica is None:
			print(f"Resultado {rotulos[metodo]}: Nao encontrada")
			continue

		print(f"Resultado {rotulos[metodo]}:", melhor_musica)
		plot_histograma_offsets(
			contagem.get(melhor_musica, {}),
			_caminho_imagem(base_dir, "histograma", "gravacao", nome_base, f"offsets_{metodo}"),
			f"Histograma de offsets - {melhor_musica} ({rotulos[metodo]})",
		)
