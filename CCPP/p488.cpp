#include <iostream>

typedef long long ll;

const int MOD = 1000000000;

int sum(ll a, ll b) {
    if (b < a) return 0;
    ll c = a + b, d = b - a + 1;
    if (c % 2) d /= 2; else c /= 2;
    c %= MOD;
    d %= MOD;
    return c * d % MOD;
}

int calc(ll N) {
    N--;
    int res = 0;
    for (ll p = 4; p < N; p *= 2) {
        ll q = p / 2, x = p - 1;
        ll k = (N + 1 - x) / p * p;
        res = (res + (k / 2) % MOD * sum(q - 1, x - 1) + q % MOD * sum(x, x + k - 1)) % MOD;
        ll c0 = x + k + q;
        if (c0 > N) continue;
        res = (res + (q % MOD) * ((c0 + q - 2) % MOD) % MOD * ((N - c0 + 1) % MOD)) % MOD;
        res = (res + (q % MOD) * sum(c0, N)) % MOD;
    }
    return res;
}

int main() {
    std::cout << calc(1000000000000000000LL) << std::endl;;
    return 0;
}
