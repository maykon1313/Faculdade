#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define os grupos de coordenadas conforme a lógica original.
const vector<vector<pair<int, int>>> grupos = {
    { {0,0}, {1,1}, {2,2} },
    { {0,0}, {2,1}, {1,2} },
    { {0,1}, {1,2}, {2,0} },
    { {0,1}, {2,2}, {1,0} },
    { {0,2}, {1,0}, {2,1} },
    { {0,2}, {2,0}, {1,1} },
    { {0,0}, {1,0}, {2,0} },
    { {0,1}, {1,1}, {2,1} },
    { {0,2}, {1,2}, {2,2} },
    { {0,0}, {0,1}, {0,2} },
    { {1,0}, {1,1}, {1,2} },
    { {2,0}, {2,1}, {2,2} },
    { {0,0}, {0,0}, {0,0} },
    { {0,1}, {0,1}, {0,1} },
    { {0,2}, {0,2}, {0,2} },
    { {1,0}, {1,0}, {1,0} },
    { {1,1}, {1,1}, {1,1} },
    { {1,2}, {1,2}, {1,2} },
    { {2,0}, {2,0}, {2,0} },
    { {2,1}, {2,1}, {2,1} },
    { {2,2}, {2,2}, {2,2} }
};

// Função que retorna o grupo com a maior soma e o valor a ser retirado.
pair<vector<pair<int,int>>, int> maior_soma_grupo(vector<vector<int>>& matriz) {
    vector<pair<int,int>> maior_grupo;
    int maior_soma = 0;
    int segundo_maior_soma = 0;

    for (const auto &grupo : grupos) {
        int i1 = grupo[0].first, j1 = grupo[0].second;
        int i2 = grupo[1].first, j2 = grupo[1].second;
        int i3 = grupo[2].first, j3 = grupo[2].second;

        int elem1 = matriz[i1][j1];
        int elem2 = matriz[i2][j2];
        int elem3 = matriz[i3][j3];

        // Se qualquer elemento for zero, desconsidera o grupo.
        if (elem1 == 0 || elem2 == 0 || elem3 == 0)
            continue;

        int soma_do_grupo = 0;
        // Se os índices forem todos iguais, a soma é o valor único.
        if (i1 == i2 && i1 == i3 && j1 == j2 && j1 == j3)
            soma_do_grupo = elem1;
        else
            soma_do_grupo = elem1 + elem2 + elem3;

        // Atualiza o maior grupo se as condições forem atendidas.
        if (soma_do_grupo > maior_soma && soma_do_grupo >= 3) {
            segundo_maior_soma = maior_soma;
            maior_soma = soma_do_grupo;
            maior_grupo = grupo;
        } else if (soma_do_grupo > segundo_maior_soma) {
            segundo_maior_soma = soma_do_grupo;
        }
    }
    
    if (!maior_grupo.empty()) {
        int retirar = (maior_soma - segundo_maior_soma) / 3;
        int i1 = maior_grupo[0].first, j1 = maior_grupo[0].second;
        int i2 = maior_grupo[1].first, j2 = maior_grupo[1].second;
        int i3 = maior_grupo[2].first, j3 = maior_grupo[2].second;
        // Garante que retirar seja, no mínimo, 1 e não exceda os valores existentes na matriz.
        retirar = max(1, min({retirar, matriz[i1][j1], matriz[i2][j2], matriz[i3][j3]}));
        return {maior_grupo, retirar};
    }
    return {vector<pair<int,int>>(), 0};
}

// Função que aplica as operações na matriz enquanto houver grupos possíveis.
int grupos_possiveis(vector<vector<int>>& matriz) {
    int cont = 0;
    while (true) {
        auto [grupo, retirar] = maior_soma_grupo(matriz);
        if (grupo.empty())
            break;
        
        int i1 = grupo[0].first, j1 = grupo[0].second;
        int i2 = grupo[1].first, j2 = grupo[1].second;
        int i3 = grupo[2].first, j3 = grupo[2].second;
        
        matriz[i1][j1] -= retirar;
        matriz[i2][j2] -= retirar;
        matriz[i3][j3] -= retirar;
        cont += retirar;
    }
    return cont;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int cartas;
        cin >> cartas;
        if (cartas == 0)
            break;

        // Inicializa a matriz 3x3 com zeros.
        vector<vector<int>> matriz(3, vector<int>(3, 0));
        
        for (int i = 0; i < cartas; i++) {
            string num, sim;
            cin >> num >> sim;
            int linha, coluna;
            
            // Mapeia o símbolo para a linha da matriz.
            if (sim == "circulo" || sim == "circulos")
                linha = 0;
            else if (sim == "triangulo" || sim == "triangulos")
                linha = 1;
            else
                linha = 2;
            
            // Mapeia o número para a coluna da matriz.
            if (num == "um")
                coluna = 0;
            else if (num == "dois")
                coluna = 1;
            else
                coluna = 2;
            
            matriz[linha][coluna]++;
        }
        
        int resultado = grupos_possiveis(matriz);
        cout << resultado << "\n";
    }
    
    return 0;
}
