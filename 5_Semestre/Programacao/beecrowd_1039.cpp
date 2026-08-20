#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int r1, x1, y1, r2, x2, y2;
	double aux;

	while (cin >> r1 >> x1 >> y1 >> r2 >> x2 >> y2) {
		aux = sqrt(pow(x2-x1,2)+pow(y2-y1,2)) + r2;

		if (aux > r1) { cout << "MORTO" << "\n"; }
		else { cout << "RICO" << "\n";}	
	}

	return 0;
}
