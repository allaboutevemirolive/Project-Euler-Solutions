#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;

int log2(ll v) {
    int res = 0;
    while (v) v /= 2, res++;
    return res - 1;
}

int log3(ll v) {
    int res = 0;
    while (v) v /= 3, res++;
    return res - 1;
}

ll pow2[100], pow3[100];

double solve(ll n) {
    int exp = 0;
    double res = 1;
    ll num = 0;
    pow2[0] = 1, pow3[0] = 1;

    for (int i = 1; i < 100; i++) {
        pow2[i] = pow2[i - 1] * 2;
        pow3[i] = pow3[i - 1] * 3;
    }

    for (int i = 0; pow2[i] <= n; i++) {
        for (int j = 0; pow3[j] <= n / pow2[i]; j++) {
            res *= ++num; // factorial
            ll v = n / pow2[i] / pow3[j];
            res /= log2(v) + log3(v) + 1; // hook length
            while (res > 10) res /= 10, exp++;
            while (res < 1) res *= 10, exp--;
        }
    }

    cout << fixed << setprecision(10);
    cout << res << 'e' << exp << endl;

    return res;
}

int main() {
    solve(1e18);

    return 0;
}