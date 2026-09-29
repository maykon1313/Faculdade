#!/bin/bash

#Configuração
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
NOME_PASTA="resultados" 

ALVOS=()
APENAS_GRAFICOS=false
MEDIR_CACHE=false
MEDIR_BRANCHES=false
MEDIR_TUDO=false

while [[ "$#" -gt 0 ]]; do #if "$#" > 0 ->gt=greater than
    case $1 in
        --cache) MEDIR_CACHE=true ;;
        --branches) MEDIR_BRANCHES=true ;;
        --all) MEDIR_TUDO=true ;;
        --plot-only) APENAS_GRAFICOS=true ;;
        -h|--help)
            echo "Uso: ./benchmark.sh [OPÇÕES] [DIRETÓRIOS...]"
            echo "Opções:"
            echo "  --cache      Mede eventos de L1 e LLC Cache"
            echo "  --branches   Mede predições e falhas de Branch"
            echo "  --all        Mede todos os eventos disponíveis"
            echo "  --plot-only  Apenas gera gráficos a partir de arquivos .txt existentes na pasta"
            echo ""
            echo "Exemplos:"
            echo "  Rodar testes: ./benchmark.sh --all Bubble"
            echo "  Apenas plotar: ./benchmark.sh --plot-only resultados_20260226_125343"
            echo "Caso seu processador tenha núcleos híbridos, experimente usar taskset."
            echo "Exemplo: taskset --cpu-list 1 ./benchmark.sh --all Bubble"
            exit 0
            ;;
        -*)
            echo "[ERRO] Flag desconhecida: $1"
            exit 1
            ;;
        *)
            ALVOS+=("$1")
            ;;
    esac
    shift 
done

#Checagem de dependencias
check_dependencies() {
    echo "=== Verificando Dependências ==="

    if [ "$APENAS_GRAFICOS" = false ]; then #-> comparação não precisa de ==
        if ! sudo -v; then # ->  -v: validando a senha para renovar o tempo de acesso do programa às permissões de sudo
            echo "[ERRO] Privilégios de superusuário (sudo) são necessários para rodar o perf."
            exit 1
        fi
        if ! command -v perf &> /dev/null; then #verifica (-v) se o comando (command) perf existe no sistema (existe um caminho?), se não existir, ele emite um erro invisível e entra no if
            echo "[ERRO] O comando 'perf' não foi encontrado."
            exit 1
        fi
    fi

    if ! command -v python3 &> /dev/null; then 
        echo "[ERRO] 'python3' não encontrado."
        exit 1
    fi
    if ! python3 -c "import matplotlib" &> /dev/null; then #-c passa todo a string pra dentro de python3, ou sejam, pede pro python executar toda a string que vem a seguir, verificando a instalação de matplotlib
        echo "[ERRO] A biblioteca 'matplotlib' não está instalada no Python."
        exit 1
    fi
    echo "  [OK] Todas as dependências foram atendidas."
    echo ""
}

check_dependencies

# --- FUNÇÃO GERADORA DE GRÁFICOS (PYTHON) ---
graph_gen() {
python3 - << 'EOF'
import matplotlib.pyplot as plt
import glob
import re
import os
import datetime

print("  [Python] Iniciando processamento de dados...")
arquivos = glob.glob("*.txt")

if not arquivos:
    print("  [Python] Nenhum arquivo .txt encontrado para gerar gráficos.")
    exit()

NOMES_METRICAS = {
    "ipc": "Instruções por Ciclo (IPC)",
    "task-clock:u": "Tempo de Execução (ms)",
    "page-faults": "Page Faults",
    "cycles": "Ciclos de CPU",
    "instructions": "Instruções Executadas",
    "cache-misses": "Cache Misses (Geral)",
    "branches": "Branches (Total)",
    "branch-misses": "Branch Misses",
    "L1-dcache-loads": "L1 Cache Loads",
    "L1-dcache-load-misses": "L1 Cache Misses",
    "LLC-loads": "LLC Loads",
    "LLC-load-misses": "LLC Misses"
}

for arquivo in arquivos:
    # Extrai o nome do algoritmo do nome do arquivo, que está entre 'resultado_' e o timestamp
    match_algoritmo = re.search(r'resultado_(.+)_(\d{8}_\d{6})\.txt', arquivo)
    if match_algoritmo:
        algoritmo = match_algoritmo.group(1)
    else:
        # Fallback para o método antigo se o padrão não corresponder
        partes = arquivo.split('_')
        algoritmo = partes[1].capitalize() if len(partes) > 1 else "Geral"
    
    with open(arquivo, 'r', encoding='latin-1') as f:
        linhas = f.readlines()

    dados = {}  
    erros = {}  
    metricas_encontradas = set()
    otimizacao_atual = None
    alvo_customizado = None # Guarda o nome extraído do run.sh

    for linha in linhas:
        # Lê a injeção feita pelo Bash
        match_alvo = re.search(r"^### ALVO_BARRA: (.+) ###", linha)
        if match_alvo:
            alvo_customizado = match_alvo.group(1)
            continue

        match_app = re.search(r"Performance counter stats for '([^']+)'", linha)
        if match_app:
            arquivo_exec = match_app.group(1)
            nome_limpo = arquivo_exec.split('/')[-1]

            if alvo_customizado:
                otimizacao_atual = alvo_customizado
                alvo_customizado = None # reseta para os próximos
            elif "_" in nome_limpo:
                otimizacao_atual = "-" + nome_limpo.split("_")[-1]
            else:
                otimizacao_atual = nome_limpo
                
            if otimizacao_atual not in dados:
                dados[otimizacao_atual] = {}
                erros[otimizacao_atual] = {}
            continue
        
        if not otimizacao_atual:
            continue

        match_metrica = re.search(r"^\s*([\d\.,]+)(?:\s+msec)?\s+([a-zA-Z0-9_/\-:]+)(?:.*?\(\s*\+-\s*([\d\.,]+)%\s*\))?", linha)
        
        if match_metrica:
            valor_str = match_metrica.group(1).replace('.', '').replace(',', '.')
            try:
                valor = float(valor_str)
            except ValueError:
                continue
                
            nome_bruto = match_metrica.group(2)
            
            if "cpu_core" in nome_bruto:
                tipo_nucleo = "P-Core"
                metrica_base = nome_bruto.replace("cpu_core/", "").strip("/")
            elif "cpu_atom" in nome_bruto:
                tipo_nucleo = "E-Core"
                metrica_base = nome_bruto.replace("cpu_atom/", "").strip("/")
            else:
                tipo_nucleo = "Total"
                metrica_base = nome_bruto.strip("/")
            
            desvio_absoluto = 0.0
            if match_metrica.group(3):
                erro_pct_str = match_metrica.group(3).replace(',', '.')
                erro_pct = float(erro_pct_str)
                desvio_absoluto = valor * (erro_pct / 100.0)

            if metrica_base in NOMES_METRICAS:
                if metrica_base not in dados[otimizacao_atual]:
                    dados[otimizacao_atual][metrica_base] = {}
                    erros[otimizacao_atual][metrica_base] = {}
                
                dados[otimizacao_atual][metrica_base][tipo_nucleo] = valor
                erros[otimizacao_atual][metrica_base][tipo_nucleo] = desvio_absoluto
                metricas_encontradas.add(metrica_base)

    for opt in dados:
        if "instructions" in dados[opt] and "cycles" in dados[opt]:
            for nucleo in ["Total", "P-Core", "E-Core"]:
                if nucleo in dados[opt]["instructions"] and nucleo in dados[opt]["cycles"]:
                    inst = dados[opt]["instructions"][nucleo]
                    cyc = dados[opt]["cycles"][nucleo]
                    if cyc > 0:
                        if "ipc" not in dados[opt]:
                            dados[opt]["ipc"] = {}
                            erros[opt]["ipc"] = {}
                        
                        ipc = inst / cyc
                        dados[opt]["ipc"][nucleo] = ipc
                        
                        err_inst_pct = (erros[opt]["instructions"][nucleo] / inst) if inst > 0 else 0
                        err_cyc_pct = (erros[opt]["cycles"][nucleo] / cyc) if cyc > 0 else 0
                        erros[opt]["ipc"][nucleo] = ipc * (err_inst_pct + err_cyc_pct)
                        
                        metricas_encontradas.add("ipc")

    if not dados:
        continue

    # ORDENAÇÃO DINÂMICA
    def chave_ordenacao(x):
        ordem_c = {'-O0': 0, 
        '-O1': 1, 
        '-O2': 2, 
        '-O3': 3, 
        '-Os': 4, 
        '-Ofast': 5}
        if x in ordem_c:
            return (0, ordem_c[x])
        return (1, x)
        
    opts_encontradas = sorted(dados.keys(), key=chave_ordenacao)
    metricas_lista = sorted(list(metricas_encontradas))
    num_metricas = len(metricas_lista)
    
    cols = 2 if num_metricas > 1 else 1
    rows = (num_metricas + cols - 1) // cols
    
    fig, axs = plt.subplots(rows, cols, figsize=(8 * cols, 5 * rows))
    fig.suptitle(f'{algoritmo} (Média e SD - 100 Runs)', fontsize=16, fontweight='bold', y=0.98)
    
    if num_metricas == 1:
        axs = [axs]
    else:
        axs = axs.flatten()

    cores_grafico = {"Total": "#2ca02c", "P-Core": "#1f77b4", "E-Core": "#ff7f0e"}
    posicoes_x = list(range(len(opts_encontradas)))

    for i, metrica in enumerate(metricas_lista):
        ax = axs[i]
        
        nucleos_presentes = set()
        for opt in opts_encontradas:
            if metrica in dados[opt]:
                nucleos_presentes.update(dados[opt][metrica].keys())
        
        nucleos_ordenados = [n for n in ["Total", "P-Core", "E-Core"] if n in nucleos_presentes]
        qtd_nucleos = len(nucleos_ordenados)
        largura_barra = 0.8 / qtd_nucleos if qtd_nucleos > 0 else 0.8

        teto_maximo = 1

        for idx, nucleo in enumerate(nucleos_ordenados):
            deslocamento = (idx - (qtd_nucleos - 1) / 2.0) * largura_barra
            x_barras = [pos + deslocamento for pos in posicoes_x]
            
            valores = [dados[opt][metrica].get(nucleo, 0) if metrica in dados[opt] else 0 for opt in opts_encontradas]
            erros_val = [erros[opt][metrica].get(nucleo, 0) if metrica in erros[opt] else 0 for opt in opts_encontradas]
            
            bars = ax.bar(x_barras, valores, largura_barra, yerr=erros_val, capsize=4, 
                          color=cores_grafico.get(nucleo), edgecolor='black', alpha=0.8, 
                          ecolor='red', error_kw={'linewidth': 1.2}, label=nucleo)
            
            teto_maximo = max(teto_maximo, max([v + e for v, e in zip(valores, erros_val)]) if valores else 1)
            
            for bar, erro_atual in zip(bars, erros_val):
                yval = bar.get_height()
                if yval > 0:
                    erro_pct = (erro_atual / yval) * 100 if yval > 0 else 0
                    texto_valor = f"{yval:.2f}" if metrica == "ipc" else f"{int(yval):,}"
                    tamanho_fonte = 7 if qtd_nucleos > 1 else 8
                    ax.text(bar.get_x() + bar.get_width()/2, yval + erro_atual + (teto_maximo * 0.02), 
                            f"{texto_valor}\n(±{erro_pct:.1f}%)", ha='center', va='bottom', 
                            fontsize=tamanho_fonte, fontweight='bold', color='#222222')

        ax.set_title(NOMES_METRICAS.get(metrica, metrica), fontsize=13, pad=15)
        ax.set_xticks(posicoes_x)
        ax.set_xticklabels(opts_encontradas, rotation=45, ha='right', rotation_mode='anchor', fontsize=10)
        ax.grid(axis='y', linestyle='--', alpha=0.6)
        ax.set_ylim(0, teto_maximo * 1.25)
        
        # LEGENDA SEMPRE ATIVA
        ax.legend(loc="upper right", fontsize=9)

    for j in range(num_metricas, len(axs)):
        fig.delaxes(axs[j])

    plt.tight_layout(rect=[0, 0.02, 1, 0.95])
    
    agora = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    nome_img = f"Grafico_{algoritmo}_{agora}.pdf"
    
    plt.savefig(nome_img, format='pdf', bbox_inches='tight')
    plt.close()
    
    print(f"  [OK] Gráfico PDF gerado: {nome_img}")

EOF
}

# --- MODO APENAS GRÁFICOS (--plot-only) ---
if [ "$APENAS_GRAFICOS" = true ]; then
    echo "=== Modo Plot-Only ==="
    if [ ${#ALVOS[@]} -eq 0 ]; then #O "@" percorre o vetor individualmente, como fosse um laço for embutido verificando todos os espaços
        echo "[ERRO] Você precisa especificar a pasta que contém os arquivos .txt."
        exit 1
    fi

    for dir in "${ALVOS[@]}"; do
        dir_limpo=${dir%/}
        if [ -d "$dir_limpo" ]; then # -d verifica se dir_limpo existe e se é uma pasta de fato
            echo "-> Analisando arquivos na pasta: $dir_limpo"
            (cd "$dir_limpo" && graph_gen) # Subshell("()"): executa o código na pasta e morre sem alterar o path principal
        else
            echo "[AVISO] Pasta não encontrada: $dir_limpo"
        fi
    done
    echo "Processamento de gráficos finalizado!"
    exit 0
fi

# --- SELEÇÃO DE ALVOS E DEFINIÇÃO DINÂMICA DA PASTA ---
if [ ${#ALVOS[@]} -eq 0 ]; then
    echo "Nenhum alvo específico fornecido. Processando todas as pastas..."
    for d in */; do ALVOS+=("$d"); done
    NOME_PASTA_COMPLETO="${NOME_PASTA}_${TIMESTAMP}"
else
    echo "Alvos especificados pelo usuário: ${ALVOS[*]}"
    if [ ${#ALVOS[@]} -eq 1 ]; then
        # Se testar apenas 1 pasta, inclui o nome no diretório raiz
        ALVO_LIMPO=${ALVOS[0]%/}
        NOME_PASTA_COMPLETO="${NOME_PASTA}_${ALVO_LIMPO}_${TIMESTAMP}"
    else
        NOME_PASTA_COMPLETO="${NOME_PASTA}_${TIMESTAMP}"
    fi
fi

# --- CRIAÇÃO DO DIRETÓRIO ---
if [ ! -d "$NOME_PASTA_COMPLETO" ]; then
    echo "Criando pasta de resultados: $NOME_PASTA_COMPLETO"
    mkdir -p "$NOME_PASTA_COMPLETO"
fi

echo "=== Iniciando Bateria de Testes Global ==="

EVENTOS="task-clock:u,page-faults,cycles,instructions"
if [ "$MEDIR_TUDO" = true ]; then
    MEDIR_CACHE=true
    MEDIR_BRANCHES=true
fi
if [ "$MEDIR_CACHE" = true ]; then EVENTOS="$EVENTOS,cache-misses,L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses"; fi
if [ "$MEDIR_BRANCHES" = true ]; then EVENTOS="$EVENTOS,branches,branch-misses"; fi

echo "Eventos configurados: $EVENTOS"
echo ""

GEROU_ARQUIVOS=false

for dir in "${ALVOS[@]}"; do
    dir_limpo=${dir%/}

    if [[ "$dir_limpo" == "${NOME_PASTA}"* ]]; then continue; fi

    echo "Processando diretório: $dir_limpo"
    cd "$dir" || continue

    ARQUIVO_SAIDA="resultado_${dir_limpo}_${TIMESTAMP}.txt"
    ARQUIVO_CRIADO=false

    for app in ./*; do
        if [ -f "$app" ] && [ -x "$app" ] && [[ "$app" != *".cpp" ]] && [[ "$app" != *".c" ]]; then
            nome_exec=$(basename "$app")
            
            # --- ESPIÃO DE SCRIPT ---
            if [[ "$nome_exec" == *".sh" ]]; then
                ALVO_REAL=$(grep -v '^\s*#' "$app" | grep -v '^\s*$' | tail -n 1 | awk '{print $NF}')
                NOME_BARRA=$(basename "$ALVO_REAL")
            else
                NOME_BARRA=$nome_exec
            fi

            echo "  -> Profiling: $nome_exec (Alvo: $NOME_BARRA) ..."
            
            # Injeção de metadados para o Python
            echo "### ALVO_BARRA: $NOME_BARRA ###" >> "$ARQUIVO_SAIDA"
            
            sudo perf stat -r 100 -e "$EVENTOS" "$app" 2>> "$ARQUIVO_SAIDA"
            ARQUIVO_CRIADO=true
        fi
    done

    if [ "$ARQUIVO_CRIADO" = true ]; then
        mv "$ARQUIVO_SAIDA" "../$NOME_PASTA_COMPLETO/"
        echo "     [OK] Arquivo consolidado salvo."
        GEROU_ARQUIVOS=true
    else
        echo "     [AVISO] Nenhum executável encontrado nesta pasta."
        rm -f "$ARQUIVO_SAIDA" 2>/dev/null
    fi

    cd ..
done

echo ""
echo "Processamento finalizado."

# --- GERAÇÃO FINAL COM SISTEMA ANTI-FANTASMA ---
if [ "$GEROU_ARQUIVOS" = true ]; then
    echo "Gerando gráficos na pasta $NOME_PASTA_COMPLETO..."
    (cd "$NOME_PASTA_COMPLETO" && graph_gen)
    echo "Tudo pronto!"
else
    echo "[AVISO] Nenhuma métrica foi coletada. Gráficos não gerados."
    rmdir "$NOME_PASTA_COMPLETO" 2>/dev/null # Limpa a pasta vazia
fi
