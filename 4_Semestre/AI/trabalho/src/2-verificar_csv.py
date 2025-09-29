import csv

def check_csv_fields(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        for row_num, row in enumerate(reader, start=1):
            if len(row) != 3:
                print(f"Row {row_num} has {len(row)} fields instead of 3: {row}")
            else:
                print(f"Row {row_num}: OK ({len(row)} fields)")

check_csv_fields('data/rawfeiticos.csv')