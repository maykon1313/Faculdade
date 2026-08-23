#!/bin/bash

# chmod +x compilar.sh

INPUT_DIRS=("QuickSort" "SelectionSort")
OUTPUT_DIRS=("QuickSort_cpp" "SelectionSort_cpp")

OPT_FLAGS=("-O0" "-O1" "-O2" "-O3" "-Os" "-Ofast")

COMPILER="g++"

compile_files() {
  local input_dir=$1
  local output_dir=$2

  mkdir -p "$output_dir"

  for file in "$input_dir"/*.cpp; do
    if [[ -f $file ]]; then
      filename=$(basename -- "$file")
      base_name="${filename%.*}"

      for flag in "${OPT_FLAGS[@]}"; do
        output_file="$output_dir/${base_name}${flag}.out"
        echo "Compilando $file com flag $flag -> $output_file"
        $COMPILER $flag "$file" -o "$output_file"
      done
    fi
  done
}

for i in "${!INPUT_DIRS[@]}"; do
  compile_files "${INPUT_DIRS[$i]}" "${OUTPUT_DIRS[$i]}"
done

echo "Compilação concluída!"

for DIR in "${OUTPUT_DIRS[@]}"; do
  echo "Tornando arquivos em $DIR executáveis..."
  chmod +x "$DIR"/*
done