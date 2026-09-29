import numpy as np
import librosa

from src.padronizacao import TAXA_AMOSTRAGEM, FREQ_MIN, FREQ_MAX

def calcular_cqt(sinal):
	bins_per_octave = 24
	hop_length = 1024
	n_bins = int(np.ceil(bins_per_octave * np.log2(FREQ_MAX / FREQ_MIN)))

	coeficientes = librosa.cqt(
		sinal,
		sr=TAXA_AMOSTRAGEM,
		fmin=FREQ_MIN,
		n_bins=n_bins,
		bins_per_octave=bins_per_octave,
		hop_length=hop_length,
	)

	magnitude = np.abs(coeficientes)
	cqt_db = librosa.amplitude_to_db(magnitude, ref=np.max)
	frequencias = librosa.cqt_frequencies(n_bins=n_bins, fmin=FREQ_MIN, bins_per_octave=bins_per_octave)
	tempos = np.arange(coeficientes.shape[1]) * hop_length / TAXA_AMOSTRAGEM

	return cqt_db, frequencias, tempos
