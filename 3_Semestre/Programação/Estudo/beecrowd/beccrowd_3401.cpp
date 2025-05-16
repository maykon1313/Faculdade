#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string A;
    int B;
    cin >> A >> B;

    long long remainder = 0;
    for (char digit : A) {
        remainder = (remainder * 10 + (digit - '0')) % B;
    }

    cout << remainder << "\n";
    return 0;
}