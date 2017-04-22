#include <iostream>
#include <cstring>

using namespace std;

#define REP(i, a, n) for (int i = (a); i < (n); i++)
const int N = 100000000;
const int MOD = 1000000009;

typedef long long ll;

bool p[N + 1];

void getPrime(int n) {
    memset(p, true, sizeof(p));
    REP(i, 2, n) if (p[i])
        for (int j = i * 2; j < n; j += i)
            p[j] = false;
}

ll pow(ll a, int b) {
    ll t = 1;
    while (b > 0) {
        if (b & 1) t = t * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return t;
}

int get(int i, int n) {
    int res = 0;
    while (n > 0) res += (n /= i);
    return res;
}

ll cal(ll c) {
    return (c * c + 1) % MOD;
}

int main() {
    getPrime(N);
    ll ans = 1;
    REP(i, 2, N) if (p[i])
        ans = ans * cal(pow(i, get(i, N))) % MOD;
    cout << ans << endl;

    return 0;
}
