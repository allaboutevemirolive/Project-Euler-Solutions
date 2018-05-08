#include <bits/stdc++.h>

#define FOR(i, n) for (int i = 0; i < (int)(n); ++i)
#define ROF(i, n) for (int i = (int)(n) - 1; i >= 0; --i)

using namespace std;

typedef long long ll;

const int mod = 999999937;

int mul(int x, int y) { return x * 1LL * y % mod; }
int add(int x, int y) { if ((x += y) >= mod) x -= mod; return x; }
int sub(int x, int y) { if ((x -= y) < 0) x += mod; return x; }
int power(int x, ll n) {
    int r = 1; while (n) {
        if (n & 1) r = mul(r, x); if (n /= 2) x = mul(x, x);
    }
    return r;
}
int inv(int x) { return power(x, mod - 1); }

int fact(ll n) {
    int r = 1;
    if (!n) return r;
    for (int i = 1; i <= n % mod; ++i) r = mul(r, i);
    r = mul(r, fact(n / mod));
    return r;
}

int factmod(ll n) {
    if (n < mod) return 0;
    return n / mod + factmod(n / mod);
}

int C(ll n, ll m, int d) {
    ll s = 0, cs = 1;
    int csmod = 0;
    ll k = d;
    while (k <= m) k += mod; k -= mod;
    cs = fact(n);
    cs = mul(cs, inv(fact(n - k)));
    cs = mul(cs, inv(fact(k)));
    csmod = factmod(n) - factmod(n - k) - factmod(k);
    for ( ; k < m; ++k) {
        if (csmod == 0) {
            if (k & 1) s = add(s, cs);
            else s = sub(s, cs);
        }
        if ((n - k) % mod == 0) {
            csmod += 1;
            cs = mul(cs, (n - k) / mod);
        } else cs = mul(cs, (n - k) % mod);
        if ((k - d + 1) % mod == 0) {
            csmod -= 1;
            cs = mul(cs, inv((k - d + 1) / mod));
        } else cs = mul(cs, inv((k - d + 1) % mod));
    }
    return s % mod;
}

int main() {
    int s = C((ll)(1e13), (ll)(1e12), 10000);
    cout << s << endl;
    return 0;
}