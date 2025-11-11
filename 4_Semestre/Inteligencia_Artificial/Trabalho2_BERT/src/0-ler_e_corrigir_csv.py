import pandas as pd

df = pd.read_csv("data/raw/oncas_comentarios.csv")

df = df[['onca', 'caseiro', 'notícia', 'comment_text']]

df = df.drop_duplicates()

not_correct = []
for index, row in df.iterrows():
    if pd.isna(row['comment_text']) or row['comment_text'].strip() == '':
        not_correct.append(index)

df = df.drop(not_correct)

df['onca'] = df['onca'].replace({'positivo': '2','neutro': '1','negativo': '0'}).astype(int)
df['caseiro'] = df['caseiro'].replace({'positivo': '2','neutro': '1','negativo': '0'}).astype(int)
df['notícia'] = df['notícia'].replace({'boa': '2','neutra': '1','ruim': '0'}).astype(int)

df.to_csv('data/interim/dataset.csv', index=False)
