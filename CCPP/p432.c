#include <cstdio>
#include <cmath>

typedef long long ll;

const ll M = 100000000000LL;
const int K = 510510;
const int MOD = 1000000000;
const int N = 50000000;
int p[7] = {2, 3, 5, 7, 11, 13, 17};
int a[N];
int phi[N];
int sphi[N];
int f[M/N + 1];

int F(ll k) {
    if (k <= M/N) 
        return f[k];
    return sphi[M/k];
}

int ans;

void rec(ll pr, int i) {
    if (i == 7) {
        ans += F(pr);
        if (ans >= MOD)
            ans -= MOD;
        return;
    }
    for ( ; pr <= M; pr *= p[i] )
        rec(pr, i + 1);
}

int main() {
    for (int i = 1; i < N; i++)
        phi[i] = i;
    for (int i = 2; i < N; i++)
        if (!a[i])
            for (int j = 1; j < N; j += i) {
                a[j] = 1;
                phi[j] = phi[j] / i * (i - 1);
            }
    for (int i = 1; i < N; i++) {
        sphi[i] = sphi[i - 1] + phi[i];
        if (sphi[i] >= MOD)
            sphi[i] - MOD;
    }

    for (int k = M/N; k >= 1; k--) {
        ll n = M/k;
        ll a[2] = {n, n + 1};
        if (a[0] % 2)
            a[1] /= 2;
        else
            a[0] /= 2;
        a[0] %= MOD, a[1] %= MOD;
        int res = a[0] * a[1] % MOD;
        int v = sqrt(n + 0.5);
        for (int j = 2; j <= n/(v+1); j++) {
            res -= F(ll(j) * k);
            if (res < 0)
                res += MOD;
        }
        for (int x = 1; x <= v; x++) {
            res -= (n/x - n/(x+1)) % MOD * sphi[x] % MOD;
            if (res < 0)
                res += MOD;
        }
        f[k] = res;
    }
    ans = 0;
    #pragma omp parallel for schedule(dynamic) reduction(+:ans)
    rec(1, 0);
    for (int i = 0; i < 7; i++) 
        ans = ll(ans) * (p[i] - 1) % MOD;
    printf("%d\n", ans);

    return 0;
}
