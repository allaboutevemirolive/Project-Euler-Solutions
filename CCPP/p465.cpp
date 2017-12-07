#include <cstdio>
#include <cmath>

#define N 20000000
#define K 100000

typedef long long ll;

const int MOD = 1000000007;

inline int powmod(int a, int n) {
    int p = 1;
    for ( ; n; ) {
        if (n % 2) p = ll(p) * a % MOD;
        if (n /= 2) a = ll(a) * a % MOD;
    }

    return p;
}

int a[N], phi[N], f[K];
ll sphi[N];

int T(ll n, int MOD) {
    if (n % 2) return n % MOD * ((n + 1) / 2 % MOD) % MOD;
    return (n / 2 % MOD) * ((n + 1) % MOD) % MOD;
}

int F(ll n, ll k, int MOD) {
    ll m = n / k;
    if (m < N) return sphi[m] % MOD;
    
    int& res = f[k];
    if (res >= 0) return res;

    int q = sqrt(m + 0.5);
    int dd = m / (q + 1);

    res = 0;
    
    for (int d = 2; d <= dd; ++d) res = (res + F(n, k * d, MOD)) % MOD;
    for (int d = 1; d <= q; ++d) res = (res + sphi[d] % MOD * ((m / d - m / (d + 1)) % MOD)) % MOD;

    if (res < 0) res += MOD;

    res = T(m, MOD) - res;
    
    if (res < 0) res += MOD;

    return res;
}

int smart(ll n) {
    int nmod = n % MOD;
    int q = sqrt(n + 0.5);
    int dd = n / (q + 1);
    int M = 1;
    
    for (int d = 1; d <= dd; ++d) M = ll(M) * powmod(n / d % MOD + 1, phi[d]) % MOD;
    for (int k = 0; k < K; ++k) f[k] = -1;

    int M1 = MOD - 1;
    
    for (int k = 1; k <= q; ++k) {
        int deg = F(n, k, M1) - F(n, k + 1, M1);
        if (deg < 0) deg += M1;
        M = ll(M) * powmod(k + 1, deg) % MOD;
    }

    M = ll(M) * M % MOD;
    M = ll(M) * M % MOD;

    int tmp = 0;
    for (int d = 1; d <= dd; ++d) {
        int q = n / d % MOD;
        tmp = (tmp + ll(phi[d]) * q % MOD * q) % MOD;
    }

    for (int k = 0; k < K; ++k) f[k] = -1;
    for (int k = 1; k <= q; ++k) tmp = (tmp + ll(k) * k % MOD * (F(n, k, MOD) - F(n, k + 1, MOD))) % MOD;

    int res = ((M - nmod * 4LL * (nmod + 1) % MOD) * M - 1 + 4LL * tmp) % MOD;
    if (res < 0) res += MOD;

    return res;
}

int main() {
    for (int n = 1; n < N; ++n) phi[n] = n;
    for (int p = 2; p < N; ++p) if (!a[p])
        for (int n = p; n < N; n += p) {
            a[n] = 1;
            phi[n] = phi[n] / p * (p - 1);
        }

    for (int n = 1; n < N; ++n) sphi[n] = sphi[n - 1] + phi[n];

    ll pw = 1;
    for (int k = 13; k--; ) pw *= 7;

    int res = smart(pw);

    printf("%d\n", res);
    
    return 0;
}