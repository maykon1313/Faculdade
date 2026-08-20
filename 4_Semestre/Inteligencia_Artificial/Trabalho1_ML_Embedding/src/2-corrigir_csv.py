import csv

def check_and_fix_csv_fields(file_path, output_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        reader = csv.reader(file, quotechar='"')
        rows = list(reader)

    with open(output_path, 'w', encoding='utf-8', newline='') as file:
        file.write(','.join(rows[0]) + '\n')  # Header sem aspas

        writer = csv.writer(file, quotechar='"', quoting=csv.QUOTE_ALL)
        for row_num, row in enumerate(rows[1:], start=2):  # Começa dos dados
            if len(row) != 3:
                print(f"[ERROR] Row {row_num} has {len(row)} fields instead of 3. Fixing...")
                fixed_row = [row[0], row[1], ','.join(row[2:])]
                if fixed_row[2].strip():  # Verifica se a descrição não está vazia
                    writer.writerow(fixed_row)
            else:
                if row[2].strip():  # Verifica se a descrição não está vazia
                    print(f"[OK] Row {row_num}.")
                    writer.writerow(row)

if __name__ == "__main__":
    check_and_fix_csv_fields('data/raw/feiticos.csv', 'data/raw/feiticos_fixed.csv')
