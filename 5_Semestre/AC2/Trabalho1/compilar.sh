#!/bin/bash

# chmod +x compilar.sh

DIRS=("QuickSort" "SelectionSort")

for DIR in "${DIRS[@]}"; do
    if [ -d "$DIR" ]; then
        echo "Compilando arquivos no diretório $DIR..."

        for JAVA_FILE in "$DIR"/*.java; do
            if [ -f "$JAVA_FILE" ]; then
                echo "Compilando $JAVA_FILE..."
                javac "$JAVA_FILE"
            fi
        done

        for CPP_FILE in "$DIR"/*.cpp; do
            if [ -f "$CPP_FILE" ]; then
                echo "Compilando $CPP_FILE..."
                g++ "$CPP_FILE" -o "${CPP_FILE%.cpp}.out"
            fi
        done

        
    else
        echo "Diretório $DIR não encontrado."
    fi

done

echo "Compilação concluída."

for DIR in "${DIRS[@]}"; do
  echo "Tornando arquivos em $DIR executáveis..."
  find "$DIR" -type f \( -name "*.out" -o -name "*.sh" -o -name "*.py" \) -exec chmod +x {} +
done