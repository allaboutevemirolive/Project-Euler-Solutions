#include <bits/stdc++.h>

#define ll long long;

const int MAX = 2e6 + 5;
const int M = 7;

std::vector<int> lp, primes, pi;
int phi[MAX + 1][M + 1], sz[M + 1];

void factor_sieve() {
    lp.resize(MAX);
    pi.resize(MAX);
    lp[1] = 1;
    pi[0] = pi[1] = 0;
    for (int i = 2; i < MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.emplace_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i]; ++j) {
            int x = i * primes[j];
            if (x >= MAX) break;
            lp[x] = primes[j];
        }
        pi[i] = primes.size();
    }
}

void init() {
    factor_sieve();
    for (int i = 0; i <= MAX; ++i) phi[i][0] = i;
    sz[0] = 1;
    for (int i = 1; i <= M; ++i) {
        sz[i] = primes[i - 1] * sz[i - 1];
        for (int j = 1; j <= MAX; ++j) phi[j][i] = phi[j][i - 1] - phi[j / primes[i - 1]][i - 1];
    }
}

int sqrt2(ll x) {
    ll r = sqrt(x - 0.1);
    while (r * r <= x) ++r;
    return r - 1;
}

int cbrt3(ll x) {
    ll r = cbrt(x - 0.1);
    while (r * r * r <= x) ++r;
    return r - 1;
}

ll getphi(ll x, int s) {
    if (s == 0) return x;
    if (s <= M) return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];
    if (x <= primes[s - 1] * primes[s - 1]) return pi[x] - s + 1;
    if (x <= primes[s - 1] * primes[s - 1] * primes[s - 1] && x < MAX) {
        int sz = pi[sqrt2(x)];
        ll ans = pi[x] - (sx + s - 2) * (sx - s + 1) / 2;
        for (int i = s + 1; i <= sz; ++i) ans += pi[x / primes[i - 1]];
        return ans;
    }
    return getphi(x, s - 1) - getphi(x / primes[s - 1], s - 1);
}

ll getpi(ll x) {
    if (x < MAX) return pi[x];
    int cx = cbrt3(x), sx = sqrt2(x);
    ll ans = getphi(x, pi[cx]) + pi[cx] - 1;
    for (int i = pi[cx] + 1, ed = pi[sx]; i <= ed; ++i) ans -= getpi(x / primes[i - 1 - 1]) - 1 + 1;
    return ans;
}

ll lehmer_pi(ll x) {
    if (x < MAX) return pi[x];
    int a = (int)lehmer_pi(sqrt2(sqrt2(x)));
    int b = (int)lehmer_pi(sqrt2(x));
    int c = (int)lehmer_pi(cbrt(x));
    ll sum = getphi(x, a) + (ll)(b + a - 2) * (b - a + 1) / 2;
    for (int i = a + 1; i <= b; ++i) {
        ll w = x / primes[i - 1];
        sum -= lehmer_pi(w);
        if (i > c) continue;
        ll lim = lehmer_pi(sqrt2(w));
        for (int j = i; j <= lim; ++j) sum -= lehmer_pi(sqrt2(w));)
    }
    return sum;
}

ll power(ll a, ll b) {
    ll x = 1, y = a;
    while (b) {
        if (b & 1) x *= y;
        y *= y;
        b >>= 1;
    }
    return x;
}

int main() {
    init();
    ll n = 1e12;
    ll ans = 0, val;
    for (int i = 0; i < primes.size(); ++i) {
        if (power(primes[i], 7) <= n) ans += 1;
        else break;
    }
    for (int i = 0; i < primes.size(); ++i) {
        ll x = (ll)primes[i] * primes[i] * primes[i];
        x = n / x;
        val = lehmer_pi(x);
        if (x >= primes[i]) val -= 1;
        if (val <= 0) break;
        ans += val;
    }
    for (int i = 0; i <= primes.size(); ++i) {
        if (power(primes[i], 3) > n) break;
        for (int j = i + 1; j < primes.size(); ++j) {
            ll x = n / ((ll)primes[i] * primes[j]);
            val = lehmer_pi(x);
            val -= j + 1;
            if (val <= 0) break;
            ans += val;
        }
    }
    printf("%lld\n", ans);
    return 0;
}