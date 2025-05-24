#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

long long get_smallest_prime_factor(long long n) {
    if (n % 2 == 0) return 2;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return i;
    }
    return n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long y_charge, k_processes;
    cin >> y_charge >> k_processes;

    long long current_x = 1;

    while (k_processes > 0) {
        long long common_divisor = gcd(current_x, y_charge);

        if (common_divisor == y_charge) {
            current_x += k_processes * y_charge;
            k_processes = 0;
        } else {
            long long y_div_g = y_charge / common_divisor;
            long long x_div_g = current_x / common_divisor;

            long long psf_y_div_g = get_smallest_prime_factor(y_div_g);
            
            long long remainder_x_mod_psf = x_div_g % psf_y_div_g;
            long long steps_with_stable_gcd = psf_y_div_g - remainder_x_mod_psf;

            if (k_processes <= steps_with_stable_gcd) {
                current_x += k_processes * common_divisor;
                k_processes = 0;
            } else {
                current_x += steps_with_stable_gcd * common_divisor;
                k_processes -= steps_with_stable_gcd;
            }
        }
    }

    cout << current_x << endl;

    return 0;
}