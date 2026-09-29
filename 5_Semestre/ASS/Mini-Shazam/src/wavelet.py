import numpy as np
import librosa
import pywt

from src.padronizacao import TAXA_AMOSTRAGEM, FREQ_MIN, FREQ_MAX

def calcular_wavelet(sinal):
	wavelet = "cmor1.5-1.0"

	freq_max = min(FREQ_MAX, TAXA_AMOSTRAGEM / 2)
	quantidade_frequencias = 64
	frequencias_alvo = np.linspace(FREQ_MIN, freq_max, num=quantidade_frequencias)

	freq_central = pywt.central_frequency(wavelet)
	escalas = (freq_central * TAXA_AMOSTRAGEM) / frequencias_alvo

	# Processa em pedaços para reduzir uso de memoria.
	tamanho_chunk = 10 * TAXA_AMOSTRAGEM
	fator_reducao = 1024

	escalograma_total = []
	tempos_total = []

	tempos_sinal = np.arange(len(sinal)) / TAXA_AMOSTRAGEM

	for i in range(0, len(sinal), tamanho_chunk):
		sinal_chunk = sinal[i : i + tamanho_chunk]
		tempo_chunk = tempos_sinal[i : i + tamanho_chunk]

		coeficientes, frequencias = pywt.cwt(
			sinal_chunk,
			escalas,
			wavelet,
			sampling_period=1.0 / TAXA_AMOSTRAGEM,
		)

		magnitude = np.abs(coeficientes)
		escalograma_db = librosa.amplitude_to_db(magnitude, ref=np.max)

		escalograma_reduzido = escalograma_db[:, ::fator_reducao]
		tempos_reduzidos = tempo_chunk[::fator_reducao]

		escalograma_total.append(escalograma_reduzido)
		tempos_total.append(tempos_reduzidos)

	matriz_final = np.hstack(escalograma_total) if escalograma_total else np.empty((0, 0))
	tempos_finais = np.concatenate(tempos_total) if tempos_total else np.array([])

	return matriz_final, frequencias, tempos_finais
