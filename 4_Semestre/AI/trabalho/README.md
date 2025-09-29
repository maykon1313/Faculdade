Usando scraper.py é coletado os dados brutos direto do site, em seguida o varificar_csv.py verifica a quantidade de colunas de cada linha.

O arquivo csv pode ter mais de 3 colunas caso a descrição do feitiço use aspas duplas.

Depois, o separar_dataset.py, separa os dados para treino, validação e teste (70%, 20% e 10% respectivamente).

Por fim o embedding.py faz o processo de embedding e salva no formato .npz da biblioteca numpy (numpy.savez_compressed). 