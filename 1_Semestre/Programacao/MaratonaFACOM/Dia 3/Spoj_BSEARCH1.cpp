#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
	int n, q; cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }
    for(int i = 0; i < q; ++i){
        int x; cin >> x;
        int l, r, m;
        l = - 1;
        r = n - 1;
        while(r>l+1){
            m=(r+l)/2;
            if(v[m] >= x){
                r = m;
            } else{
                l = m;
            }
        } if(x == v[r]){
            cout<< r << "\n";
        }
        else{
            cout<<"-1\n";
        }
    }
	return 0;
}