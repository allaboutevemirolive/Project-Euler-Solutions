#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

#define M 64LL
#define N 10000000000000000LL

static ll f[M + 1][M + 1];

static ll gcd(ll x, ll y) {
    while (y != 0LL) {
        ll t = y;
        y = x % y;
        x = t;
    }

    return x;
}

static ll s(int *t, int tlen, ll n) {
    if ((tlen == 0) || (n == 0LL)) return 0;
    
    int e = t[0];
    int ei = 0;

    for (int i = 1; i < tlen; i++) {
        if (t[i] > e) {
            e = t[i];
            ei = i;
        }
    }

    if (e == 1) return n;

    t[ei] = t[0];
    t[0] = e;

    int newt[tlen - 1];
    
    for (int i = 1; i < tlen; i++) newt[i - 1] = f[e][t[i]];

    return s(t + 1, tlen - 1, n) + n / e - s(newt, tlen - 1, n / e);
}

static int sieve(int *t, int a) {
    char b[M + 1];

    memset(b, 0, sizeof(char)*(M + 1));

    int i = 0;
    for (int p = a; p <= M; p++) {
        if (b[p] == 0) {
            t[i] = p; i++;
            for (int q = 2 * p; q <= M; q += p) b[q] = 1;
        }
    }

    return i;
}

int main() {
    for (ll t = 1; t <= M; t++) 
        for (ll e = 1; e <= M; e++)
            f[e][t] = t / gcd(t, e);

    ll r = 0LL;

    #pragma omp parallel for schedule(static,1),reduction(+:r)
    for (int m = 1; m <= M; m++) {
        int *t = malloc(sizeof(int)*M);
        int len = sieve(t, m);
        r += s(t, len, m * N) - s(t, len, (m - 1) * N);
        free(t);
    }

    printf("%lld\n", r);

    return 0;
}
