#include <stdio.h>
#include <string.h>

#define L 1000000000000LL
#define LSQRT 1000000

typedef long long ll;

// sum_{x=start}^{end} floor(n/x)
ll sum(ll n, int start, int end) {
    ll result = 0;
    int x;
    
    if (end > n) end = n;

    for (x = start; x <= end && (ll) x * x <= n; x++) {
        result += n / x;
    }

    if (x > end) return result;
    x--;
    
    ll xprev = x;
    x = n / x;

    ll xnext;
    for ( ; ; x--) {
        xnext = n / x;
        if (xnext > end) xnext = end;
        result += x * (xnext - xprev);
        xprev = xnext;
        if (xnext == end) break;
    }
    
    return result;
}

static char mu[LSQRT + 1];
static char primes[LSQRT + 1];

int main() {
    int d, a, b;
    memset(primes, 1, sizeof(primes));

    for (a = 2; a * a <= LSQRT; a++) 
        if (primes[a])
            for (b = a * a; b <= LSQRT; b += a)
                primes[b] = 0;
    
    memset(mu, 1, sizeof(mu));
    for (a = 2; a * a <= LSQRT; a++)
        if (primes[a]) {
            for (b = a; b <= LSQRT; b += a) 
                mu[b] = -mu[b];
            for (b = a * a; b <= LSQRT; b += a * a)
                mu[b] = 0;
        }

    for ( ; a <= LSQRT; a++)
        if (primes[a])
            for (b = a; b <= LSQRT; b += a)
                mu[b] = -mu[b];
    
    int y;
    ll z = 0;
    for (d = 1; (ll) d * d < L; d++) {
        if (!mu[d]) continue;
        ll l = L / d / d;
        ll z2 = 0;
        for (y = 1; (ll) y * y < l; y++)
            z2 += sum(l / y, y + 1, 2 * y - 1);
        
        z += z2 * mu[d];
    }
    printf("%lld\n", z);

    return 0;
}