#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, i, j, _;
    string s;
    bool da;
    
    cin >> t;

    while (t--) {
        cin >> _;
        cin >> s;

        da = true;

        for (i = 1; i <= s.length()-1; i++) {
            if (s[i] == '0') {
                if (s[i-1] == '1' && s[i+1] == '1') {

                    if (i-2 >= 0 && i+2 <= s.length()-1) {
                        if (s[i-2] == '1' && s[i+2] == '1') {
                            da = false;
                        }

                        continue;
                    }
                    
                    else if (i-2 >= 0) {
                        if (s[i-2] == '1') {
                            da = false;
                        }

                        continue;
                    }

                    else if(i+2 <= s.length()) {
                        if (s[i+2] == '1') {
                            da = false;
                        }

                        continue;
                    }
                }
                
            }
        }

        if(da) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }

    return 0;
}

/*

1 1 0 1 1 0 1 1


1 0 1 0 1 0 1

0 0 0 0 0 0 0 0 1 1 1 1 1  1 0 0 0 0 0 0 0 1 1 1 1 1 1 0 1 

*/