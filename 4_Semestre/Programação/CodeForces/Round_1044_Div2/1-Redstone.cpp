#include <iostream>
#include <vector>
#include <unordered_set>
 
using namespace std;
 
typedef long long ll;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste, n;
 
    cin >> teste;
    while(teste--) {
        cin >> n;
 
        vector<int> v(n);
 
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
 
        unordered_set<int> dup(v.begin(), v.end());
 
        if (v.size() != dup.size()) {
            cout << "YES" << '\n';
        } 
        else {
            cout << "NO" << '\n';
        }
    }
    
    return 0;
}