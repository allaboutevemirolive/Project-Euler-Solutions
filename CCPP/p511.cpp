#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll N = 1234567898765;
const int K = 4321;
const ll MOD = 1000000000;

void convolute(ll x[K], ll y[K], ll mod) {
    ll r[K] = {};
#pragma omp parallel for
    for (int i = 0; i < K; ++i)
        for (int j = 0; j < K; ++j)
            r[i] = (r[i] + x[j] * y[(i - j + K) % K]) % mod;

    memcpy(x, r, sizeof(r));
}

void power(ll m[K], ll n, ll mod) {
    if (n == 1) return;
    ll e[K] = {};
    e[0] = 1;

    while (n) {
        cout << "n = " << n << endl;
        if (n & 1) convolute(e, m, mod);
        convolute(m, m, mod);
        n >>= 1;
    }
    memcpy(m, e, sizeof(e));
}

int main() {
    const int maxf = 1000;
    int dn = 0;
    ll div[maxf];
    for (ll i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            div[dn++] = i;
            if (i * i != N) div[dn++] = N / i;
        }
    }
    cout << "#Divisors = " << dn << endl;

    ll m[K] = {};
    for (int j = 0; j < dn; ++j) m[div[j] % K]++;
    power(m, N, MOD);
    cout << m[K - N % K] << endl;

    return 0;
}