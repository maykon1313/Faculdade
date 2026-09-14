from pathlib import Path
import subprocess

for test_file in sorted(Path("tests").glob("*.mc")):
    print(f"Executando: {test_file}")
    subprocess.run(["./lexer", str(test_file)])
    print("-" * 30)

input("\nExecução concluída!")