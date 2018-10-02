#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

ld F(int N) {
    ld res = N;
    for (int t = N; t > 0; --t) {
        // expected value of the ith highest is i * exp
        ld exp = N + 1;
        exp /= t + 1;

        ld cutoff = floor(res / exp);
        
        res = ((t - cutoff) * res + (cutoff) * (cutoff + 1) / 2 * exp) / t;
    }
    return res;
}

int main() {
    cout << fixed << setprecision(10) << F(1000000) << '\n';
    return 0;
}
