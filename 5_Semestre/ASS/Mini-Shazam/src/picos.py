import numpy as np
from scipy.ndimage import maximum_filter

def encontrar_picos(espectrograma, frequencias, tempos):
	maximos_locais = maximum_filter(espectrograma, size=(15, 15))
	mascara_picos = espectrograma == maximos_locais
	limiar_global = np.percentile(espectrograma, 75)
	linhas, colunas = np.where(mascara_picos & (espectrograma >= limiar_global))
	picos = []
	tempo_maximo = tempos[-1]
	margem = 0.5
	for linha, coluna in zip(linhas, colunas):
		freq_hz = frequencias[linha]
		tempo_s = tempos[coluna]
		# Ignore edge transients at the start and end of the audio.
		if margem <= tempo_s <= (tempo_maximo - margem):
			picos.append((tempo_s, freq_hz))
	picos.sort(key=lambda item: item[0])
	return picos
