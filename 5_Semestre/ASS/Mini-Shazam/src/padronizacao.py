import librosa
from scipy.signal import butter, sosfiltfilt

TAXA_AMOSTRAGEM = 44100
FREQ_MIN = 300
FREQ_MAX = 5000
ORDEM_FILTRO = 4

def bandpass_filter(sinal, taxa_amostragem):
	sos = butter(ORDEM_FILTRO, [FREQ_MIN, FREQ_MAX], btype="bandpass", fs=taxa_amostragem, output="sos")
	sinal_filtrado = sosfiltfilt(sos, sinal)

	return sinal_filtrado

def carregar_audio(caminho_arquivo):
	sinal, taxa_amostragem = librosa.load(caminho_arquivo, sr=TAXA_AMOSTRAGEM, mono=True)
	sinal = bandpass_filter(sinal, taxa_amostragem)

	return sinal
