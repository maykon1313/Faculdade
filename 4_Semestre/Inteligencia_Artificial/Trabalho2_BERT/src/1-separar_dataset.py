import pandas as pd
from sklearn.model_selection import train_test_split

raw = pd.read_csv('data/interim/dataset.csv')

train_df, temp_ds = train_test_split(raw, test_size=0.3, random_state=42)

val_df, test_df = train_test_split(temp_ds, test_size=0.5, random_state=42)

train_df.to_csv('data/dataset/train.csv', index=False)
val_df.to_csv('data/dataset/valid.csv', index=False)
test_df.to_csv('data/dataset/test.csv', index=False)
