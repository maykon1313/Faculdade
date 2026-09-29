from pathlib import Path
import subprocess

log_file_path = Path("resultado_testes.txt")

with open(log_file_path, "w", encoding="utf-8") as log_file:
    for test_file in sorted(Path("tests").glob("*.mc")):
        header = f"Executando: {test_file}\n"
        print(header, end="")
        log_file.write(header)
        log_file.flush()

        result = subprocess.run(
            ["./lexer", str(test_file)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True
        )

        output_formatada = result.stdout.replace("'\n'", r"'\n'")

        log_file.write(output_formatada)

        divider = "\n" + "-" * 30 + "\n"
        print(divider, end="")
        log_file.write(divider)

print("\nExecução concluída!")