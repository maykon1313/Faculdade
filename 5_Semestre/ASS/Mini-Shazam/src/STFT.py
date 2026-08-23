import numpy as np
import librosa
from scipy.signal import stft

from src.padronizacao import TAXA_AMOSTRAGEM, FREQ_MIN, FREQ_MAX

def calcular_stft(sinal):
	frequencias, tempos, espectro_complexo = stft(sinal, fs=TAXA_AMOSTRAGEM, window="hann", nperseg=2048, noverlap=1024)
	magnitude = np.abs(espectro_complexo)
	espectrograma_db = librosa.amplitude_to_db(magnitude, ref=np.max)

	mascara_freq = (frequencias >= FREQ_MIN) & (frequencias <= FREQ_MAX)
	return espectrograma_db[mascara_freq, :], frequencias[mascara_freq], tempos

	#return espectrograma_db, frequencias, tempos


