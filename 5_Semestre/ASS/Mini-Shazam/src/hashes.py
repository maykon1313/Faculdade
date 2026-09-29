FANOUT = 10
MAX_DELTA_S = 3.0

def gerar_hashes(lista_picos):
	if not lista_picos:
		return []

	lista_ordenada = sorted(lista_picos, key=lambda item: item[0])
	hashes = []

	for i, (tempo_ancora, freq_ancora) in enumerate(lista_ordenada):
		for tempo_futuro, freq_futuro in lista_ordenada[i + 1 : i + 1 + FANOUT]:
			delta_tempo = tempo_futuro - tempo_ancora
			if delta_tempo > MAX_DELTA_S:
				continue
			f1 = int(round(freq_ancora))
			f2 = int(round(freq_futuro))
			dt_ms = int(round(delta_tempo * 1000))
			hashes.append((f"{f1}|{f2}|{dt_ms}", tempo_ancora))

	return hashes
