#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, i, j;
    
    cin >> t;

    while (t--) {
        cin >> n;

        for (j = n; j >= 1; j--) cout << j << ' ';
        for (i = 1; i < n; i++) cout << i << ' ';

        cout << n << '\n';
    }

    return 0;
}

/*
1   X
2   2,4,6,8,10,...
3   3,6,9,12,...
4   



10

10 6 7 6 5 4 3 2 1 10 6

10 - x = n*x
n*x + x = 10
x(n+1) = 10

1 2 3 4 5 6
1 3 1 2 3 2

3-1 2
5-2 3
6-4 2
*/