import pandas as pd
from sklearn.model_selection import train_test_split

def separate():
    # Carregar o dataset CSV
    raw = pd.read_csv('data/raw/feiticos_fixed.csv')

    # Dividir em treino (70%) e restante (30%) de forma estratificada
    train_df, temp_ds = train_test_split(raw, test_size=0.30, random_state=42, stratify=raw['escola'])

    # Dividir o restante em validação (20% do total) e teste (10% do total) de forma estratificada
    val_df, test_df = train_test_split(temp_ds, test_size=0.3333, random_state=42, stratify=temp_ds['escola'])

    # Verificar proporções (aproximadas)
    print(f"Treino: {len(train_df)} linhas ({len(train_df)/len(raw)*100:.1f}%)")
    print(f"Validação: {len(val_df)} linhas ({len(val_df)/len(raw)*100:.1f}%)")
    print(f"Teste: {len(test_df)} linhas ({len(test_df)/len(raw)*100:.1f}%)")

    # Salvar os splits em novos CSVs
    train_df.to_csv('data/separated/feiticos_train.csv', index=False)
    val_df.to_csv('data/separated/feiticos_val.csv', index=False)
    test_df.to_csv('data/separated/feiticos_test.csv', index=False)

if __name__ == "__main__":
    separate()
