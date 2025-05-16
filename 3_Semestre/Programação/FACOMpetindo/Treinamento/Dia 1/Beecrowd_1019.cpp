#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int segundos, minutos, horas;
    
    cin >> segundos;

    minutos = (int)(segundos/60);
    segundos = segundos - (minutos * 60);

    horas = (int)(minutos/60);
    minutos = minutos - (horas * 60);

    cout << horas << ":" << minutos << ":" << segundos << endl;
    return 0;
}