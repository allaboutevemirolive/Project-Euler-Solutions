#include <stdio.h>
#include <iostream>

#define M 1000000009
#define SZ 10000000

typedef long long ll;

ll mulmod(ll x, ll y, ll m) {
    return (x * y) % m;
}

ll mulmod(ll x, ll y, ll z, ll m) {
    return (((x * y) % m) * z) % m;
}

ll powmod(ll x, ll y, ll m) {
    if (y < 0) y += m-1;
    x %= m;
    ll r = 1;
    for (; y; y >>= 1) {
        if (y & 1) r = mulmod(r, x, m);
        x = mulmod(x, x, m);
    }
    return r;
}

ll fact[SZ];  // k!
ll facti[SZ]; // k!^-1
ll en[SZ];    // n^k
ll eni1[SZ];  // (n^-1 - 1) ^ k

ll bin(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return mulmod(fact[n], facti[n-k], facti[k], M);
}

ll hs(int i, int m) {
    ll r = 0;
    int q = i / m;
    for (int k = 0; k <= q; k++) {
        int d = i - k * m;
        r = (r + mulmod(bin(d, k), en[d], eni1[k], M)) % M;
    }
    return r;
}

ll calc(int n) {
    ll ni1 = powmod(n, -1, M) - 1;
    ll n1i = powmod(n - 1, -1, M);
    fact[0] = 1;
    facti[0] = 1;
    en[0] = 1;
    eni1[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = mulmod(fact[i-1], i, M);
        facti[i] = powmod(fact[i], -1, M);
        en[i] = mulmod(en[i-1], n, M);
        eni1[i] = mulmod(eni1[i-1], ni1, M);
    }
    ll r = mulmod(n+1, hs(n, n) - hs(n - 1, n), M);
    for (int m = 1; m <= n; m++) {
        r = (r - hs(n, m) + hs(n - 1, m)) % M;
    }
    r = mulmod(r, n, n1i, M);
    return (r < 0 ? r + M : r);
}

int main() {
    ll r = calc(7500000);
    printf("%lld\n", r);
    return 0;
}
