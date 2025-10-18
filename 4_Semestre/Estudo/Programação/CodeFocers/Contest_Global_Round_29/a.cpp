#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    
    cin >> n;

    while(n--) {
        cin >> x >> y;

        if (x < y) {cout << 2 << '\n';}

        else if (x == y) {cout << -1 << '\n';}

        else if (x-y == 1) {cout << -1 << '\n';}

        else if (y == 1) {cout << -1 << '\n';}

        else {cout << 3 << '\n';}
    }

    return 0;
}

/*
4 2

x 3,2 (1, 0) 1
y 3,0 (1, 2) 2
x 0,0 (4, 2) 3


5 3

x 4,2 (1, 0) 1
y 4,0 (1, 2) 2
x 0,0 (5, 3) 4


5 4

x 4,4 (1, 0) 1
y



*/