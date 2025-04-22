#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long int l, n, area_max;
    
    cin >> l >> n;
    
    area_max = ((l - (n-1)) * (l - (n-1))) + (n-1);

    cout << area_max << endl;
    return 0;    
}

